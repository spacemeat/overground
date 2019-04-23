#!/bin/bash

INC_DIRS="-Iinc -I../pools/inc -I../jobs/inc -I../../humon/inc -I../../../balls/vulkan/1.1.77.0/x86_64/include"
OBJ_FILES="../bin/libassets-d.a ../obj/assets-loadHumonFileJob.o ../obj/assets-initFromHumonJob.o ../obj/assets-config.o ../obj/assets-mesh.o ../obj/assets-model.o"

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
    g++ --std=c++17 -c -Wall -g -Og -o $doto $dotcpp $INC_DIRS
    return $?
  else
    echo "  ... up to date."
  fi
  return 0
}

buildlib() {
  echo "Building lib"
  buildcpp src/loadHumonFileJob.cpp ../obj/assets-loadHumonFileJob.o || return $?
  buildcpp src/initFromHumonJob.cpp ../obj/assets-initFromHumonJob.o || return $?
  buildcpp src/config.cpp ../obj/assets-config.o || return $?
  buildcpp src/mesh.cpp ../obj/assets-mesh.o || return $?
  buildcpp src/model.cpp ../obj/assets-model.o || return $?

  if [ -f ../bin/libassets-d.a ]; then
    rm ../bin/libassets-d.a
  fi
  ar cr -o ../bin/libassets-d.a $OBJ_FILES || return $?
  return 0
}

buildtest() {
  echo "Building test"
  buildcpp src/test.cpp ../obj/assets-test.o || return $?
  g++ --std=c++17 -Wall -g -Og -o ../bin/test-assets -L../../humon/bin -L../bin -pthread ../obj/assets-test.o $OBJ_FILES -lhumon-d -ljobs-d || return $?
  return 0
}

runtest() {
  echo "Running test"
  ../bin/test-assets
  return $?
}

if [ "$1" == "buildlib" ]; then
  buildlib
elif [ "$1" == "buildtest" ]; then
  buildlib && buildtest
elif [ "$1" == "runtest" ]; then
  runtest
fi

return
