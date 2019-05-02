#!/bin/bash

gccArgs="--std=c++17 -Wall -g -O0"


fg() {
  sel=""
  case $1 in
    "black" )
      sel="0;30" ;;
    "dk-red" )
      sel="0;31" ;;
    "dk-green" )
      sel="0;32" ;;
    "orange" )
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
    "yellow" )
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
#  local -n cmd=$1
#  local cmds=${cmd[@]}
  fg "dk-gray" "$1"
  eval $1
  return $?
}


buildcpp() {
  local dotcpp=$1
  local doto=$2
  local -n incDirs=$3
  local -n pack=$4
  fg "yellow" "Building $dotcpp:"

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

  fg "lt-blue" "Building $libFile"

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
buildtest() {
  local subProject=$1
  local -n subProjectDeps=$2
  local -n addInc=$3
  local -n addLibDirs=$4
  local -n addLibs=$5
  local -n packageModules=$6

  local libFile="../bin/lib${subProject}-d.a"
  local testFile="../bin/test-${subProject}"

  fg "lt-magenta" "Building $testFile"

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

  buildcpp src/test.cpp "../obj/${subProject}-test.o" allIncludes packageModules || return $?
  runCommand "g++ $gccArgs -o $testFile $finalLibDirs -pthread ../obj/${subProject}-test.o $finalLibs $packageDefs" || return $?
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
  local -n src_=$5
  local -n libDirs_=$6
  local -n libs_=$7
  local -n packages_=$8

  if [ "$1" == "buildlib" ]; then
    buildlib $subProject_ deps_ inc_ packages_ src_ || return $?
  elif [ "$1" == "buildtest" ]; then
    # NOTE: If buildlib appears to change the values of inc_ (bash bug?) so we replicate it here before the next call.
    # TODO: packages_ sufferes not the same affliction
    local inc2=${inc_[@]}
    buildlib $subProject_ deps_ inc_ packages_ src_ || return $?
    buildtest $subProject_ deps_ inc2 libDirs_ libs_ packages_ || return $?
  elif [ "$1" == "runtest" ]; then
    runtest $subProject_ || return $?
  fi
}
