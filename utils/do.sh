#!/bin/bash

source ../buildproj.sh

main() {
  local subProject="utils"
  local deps=()
  local inc=("../../humon/inc")
  local src=("utils")
  local libDirs=("../../humon/bin")
  local libs=("utils-d")
  local packages=()

  doTheThing $1 $subProject deps inc src libDirs libs packages

  return $?
}

main $1
return $?



#!/bin/bash

GCC_ARGS="--std=c++17 -Wall -g -O0"
INC_DIRS="-Iinc"
OBJ_FILES=""
LIB_DIRS="-L../bin/"
LIBS="-lutils-d"

buildcpp() {
  dotcpp=$1
  doto=$2
  echo "$dotcpp -> $doto"
  if [ ! -e $dotcpp ]; then
    echo "Error: File does not exist: \n$dotcpp"
    return 1
  fi
  mcpp=$(stat -c %Y $dotcpp)
  if [ -e $doto ]; then
    mo=$(stat -c %Y $doto)
  else
    mo=0
  fi
  if [ $mo -lt $mcpp ]; then
    echo "Building $dotcpp:"
    g++ $GCC_ARGS -c -o $doto $dotcpp $INC_DIRS
    return $?
  else
    echo "  ... up to date."
  fi
  return 0
}

buildlib() {
  echo "Building lib"
  buildcpp src/utils.cpp ../obj/utils-utils.o || return $?

  if [ -f ../bin/libutils-d.a ]; then
    rm ../bin/libutils-d.a
  fi
  ar cr -o ../bin/libutils-d.a $OBJ_FILES || return $?
  return 0
}

buildtest() {
  echo "Building test"
  buildcpp src/test.cpp ../obj/utils-test.o || return $?
#  g++ --std=c++17 -Wall -g -Og -o ../bin/test-jobs -pthread ../obj/jobs-test.o $OBJ_FILES || return $?
  g++ $GCC_ARGS -o ../bin/test-utils -pthread  $LIB_DIRS ../obj/utils-test.o $LIBS || return $?

  return 0
}

runtest() {
  echo "Running test"
  ../bin/test-jobs
  return $?
}


if [ "$1" == "buildlib" ] ; then
  buildlib
elif [ "$1" == "buildtest" ] ; then
  buildlib; buildtest
elif [ "$1" == "runtest" ] ; then
  runtest
fi

