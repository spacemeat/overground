#!/bin/bash
#!/bin/bash

INC_DIRS="-Iinc -I../pools/inc -I../jobs/inc -I../../humon/inc -I../../../balls/vulkan/1.1.77.0/x86_64/include"
OBJ_FILES="../obj/jobs-job.o ../obj/jobs-jobManager.o ../obj/jobs-worker.o"

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
  buildcpp src/job.cpp ../obj/jobs-job.o || return $?
  buildcpp src/jobManager.cpp ../obj/jobs-jobManager.o || return $?
  buildcpp src/worker.cpp ../obj/jobs-worker.o || return $?

  if [ -f ../bin/libjobs-d.a ]; then
    rm ../bin/libjobs-d.a
  fi
  ar cr -o ../bin/libjobs-d.a $OBJ_FILES || return $?
  return 0
}

buildtest() {
  echo "Building test"
  buildcpp src/test.cpp ../obj/jobs-test.o || return $?
#  g++ --std=c++17 -Wall -g -Og -o ../bin/test-jobs -pthread ../obj/jobs-test.o $OBJ_FILES || return $?
  g++ --std=c++17 -Wall -g -Og -o ../bin/test-jobs -pthread  -L../bin/ ../obj/jobs-test.o -ljobs-d || return $?

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

