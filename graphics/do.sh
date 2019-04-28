#!/bin/bash

INC_DIRS="-Iinc -I../inc -I../assets/inc -I../pools/inc -I../jobs/inc -I../../humon/inc -I../../../balls/vulkan/1.1.77.0/x86_64/include"
OBJ_FILES="../obj/graphics-graphics.o"
LIB_DIRS="-L../../../balls/vulkan/1.1.77.0/x86_64/lib -L../../humon/bin -L../bin"

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
  buildcpp src/graphics.cpp ../obj/graphics-graphics.o || return $?

  if [ -f ../bin/libgraphics-d.a ]; then
    rm ../bin/libgraphics-d.a
  fi
  ar cr -o ../bin/libgraphics-d.a $OBJ_FILES || return $?
  return 0
}

buildtest() {
  echo "Building test"
  buildcpp src/test.cpp ../obj/graphics-test.o || return $?
  g++ --std=c++17 -Wall -g -Og -o ../bin/test-graphics $LIB_DIRS -pthread ../obj/graphics-test.o $OBJ_FILES -lgraphics-d -lassets-d -ljobs-d -lhumon-d -lvulkan `pkg-config --libs glfw3 --static`|| return $?
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
