#!/bin/bash

#  -Wextra
gccArgs="--std=c++2a -Wall -g -O0 -fno-stack-protector -Wno-class-memaccess"


fg() {
  sel=""
  case $1 in
    "black" )
      sel="0;30" ;;
    "dk-red" )
      sel="0;31" ;;
    "dk-green" )
      sel="0;32" ;;
    "dk-yellow" )
      sel="0;33" ;;
    "dk-blue" )
      sel="0;34" ;;
    "dk-magenta" )
      sel="0;35" ;;
    "dk-cyan" )
      sel="0;36" ;;
    "lt-gray" )
      sel="0;37" ;;
    "dk-gray" )
      sel="1;30" ;;
    "lt-red" )
      sel="1;31" ;;
    "lt-green" )
      sel="1;32" ;;
    "lt-yellow" )
      sel="1;33" ;;
    "lt-blue" )
      sel="1;34" ;;
    "lt-magenta" )
      sel="1;35" ;;
    "lt-cyan" )
      sel="1;36" ;;
    "white" )
      sel="1;37" ;;
  esac

  echo -e "\033[${sel}m$2\033[0m"
}


runCommand() {
  fg "dk-gray" "$1"
  eval $1
  return $?
}


buildcpp() {
  local dotcpp=$1
  local doto=$2
  local -n incDirs=$3
  local -n pack=$4
  fg "dk-yellow" "Compiling source $dotcpp:"

  if [ ! -e $dotcpp ]; then
    echo "Error: File does not exist: \n$dotcpp"
    return 1
  fi
  local mcpp=$(stat -c %Y $dotcpp)
  local mo=0
  if [ -e $doto ]; then
    mo=$(stat -c %Y $doto)
  fi
  if [ $mo -lt $mcpp ]; then
    local incD=${incDirs[@]}
    local packageDefs=""
    if [ ${#pack[@]} -gt 0 ]; then
      for def in ${pack[@]}; do
        packageDefs+=($def)
      done
      packageDefs="`pkg-config --cflags ${packageDefs[@]}`"
    fi
    if [ -e $doto ]; then
      rm $doto
    fi
    runCommand "g++ $gccArgs -c -o $doto $dotcpp $incD $packageDefs"
    return $?
  else
    echo "  ... already up to date."
  fi
  return 0
}


# $1 looks like "assets"
# $2 looks like ["pools jobs utils"]
# $3 looks like ["../../humon/inc ../../../balls/vulkan/1.1.77.0/x86_64/include"]
# $4 looks like ["glfw3"]
# $5 looks like ["fileRegistry" "assetPack" ...]
buildlib() {
  local subProject=$1
  local -n subProjectDeps=$2
  local -n addInc=$3
  local -n packageModules=$4
  local -n dotcppFiles=$5
  local dotoFiles=()
  local libFile="../bin/lib${subProject}-d.a"

  fg "lt-blue" "Building library $libFile"

  local allIncludes=()
  for inc in ${addInc[@]}; do
    allIncludes+=("-I$inc")
  done
  
  for subProj in ${subProjectDeps[@]}; do
    allIncludes+=("-I../${subProj}/inc")
  done
  allIncludes+=("-Iinc" "-I../inc")

  for baseFile in ${dotcppFiles[@]}; do
    local dotcpp="src/${baseFile}.cpp"
    local doto="../obj/${subProject}-${baseFile}.o"
    buildcpp $dotcpp $doto allIncludes packageModules || return $?
    dotoFiles+=($doto)
  done

  fg "dk-yellow" "Archiving objects"  
  if [ -f $libFile ]; then
    rm $libFile
  fi
  allDotoFiles=${dotoFiles[@]}
  runCommand "ar cr -o $libFile $allDotoFiles" || return $?
  return 0
}


# $1 looks like "assets"
# $2 looks like ["pools jobs utils"]
# $3 looks like ["../../humon/inc ../../../balls/vulkan/1.1.77.0/x86_64/include"]
# $4 looks like ["../../humon/bin"]
# $5 looks like ["humon-d"]
# $6 looks like ["glfw3"]
buildexe() {
  local subProject=$1
  local -n subProjectDeps=$2
  local -n addInc=$3
  local -n addLibDirs=$4
  local -n addLibs=$5
  local -n packageModules=$6
  local -n dotcppFiles=$7

  local libFile="../bin/lib${subProject}-d.a"
  local exeFile="../bin/exe-${subProject}"

  fg "lt-blue" "Building executable $exeFile"

  local allIncludes=()
  for inc in ${addInc[@]}; do
    allIncludes+=("-I$inc")
  done
  
  for subProj in ${subProjectDeps[@]}; do
    allIncludes+=("-I../${subProj}/inc")
  done
  allIncludes+=("-Iinc" "-I../inc")

  local allLibDirs=("-L../bin")
  for ld in ${addLibDirs[@]}; do
    local libDir="-L${ld}"
    allLibDirs+=($libDir)
  done

  # include self as a lib
  addLibs+=("${subProject}-d")

  # for each dep, if there's a lib, include it
  for dep in ${subProjectDeps[@]}; do
    lib="../bin/lib${dep}-d.a"
    if [ -f ${lib} ]; then
      addLibs+=("${dep}-d")
    fi
  done

  local allLibs=()
  for lib in ${addLibs[@]}; do
    allLibs+=("-l${lib}")
  done

  local packageDefs=""
  if [ ${#packageModules[@]} -gt 0 ]; then
    for def in ${packageModules[@]}; do
      packageDefs+=($def)
    done
    packageDefs="`pkg-config --libs --static ${packageDefs[@]}`"
  fi

  finalLibDirs="${allLibDirs[@]}"
  finalLibs="${allLibs[@]}"

  # build the additional src
  local dotoFiles=()
  for baseFile in ${dotcppFiles[@]}; do
    local dotcpp="src/${baseFile}.cpp"
    local doto="../obj/${subProject}-${baseFile}.o"
    buildcpp $dotcpp $doto allIncludes packageModules || return $?
    dotoFiles+=($doto)
  done

  finalDotoFiles="${dotoFiles[@]}"

  fg "dk-yellow" "Linking objects"

  runCommand "g++ $gccArgs -o $exeFile $finalLibDirs -pthread -Wl,--start-group $finalDotoFiles $finalLibs $packageDefs -Wl,--end-group" || return $?
  return 0
}


# $1 looks like "assets"
runtest() {
  local subProject=$1
  local testFile=../bin/test-${subProject}
  echo "Running $testFile"
  runCommand $testFile
  return $?
}


doTheThing() {
  local command=$1
  local subProject_=$2
  local -n deps_=$3
  local -n inc_=$4
  local -n libSrc_=$5
  local -n exeSrc_=$6
  local -n libDirs_=$7
  local -n libs_=$8
  local -n packages_=$9

  if [ "$1" == "buildlib" ]; then
    buildlib $subProject_ deps_ inc_ packages_ libSrc_ || return $?
  elif [ "$1" == "buildexe" ]; then
    # NOTE: If buildlib appears to change the values of inc_ (bash bug?) so we replicate it here before the next call.
    # TODO: packages_ sufferes not the same affliction
    local inc2=${inc_[@]}
    buildlib $subProject_ deps_ inc_ packages_ libSrc_ || return $?
    buildexe $subProject_ deps_ inc2 libDirs_ libs_ packages_ exeSrc_ || return $?
  elif [ "$1" == "runtest" ]; then
    runtest $subProject_ || return $?
  fi
}
