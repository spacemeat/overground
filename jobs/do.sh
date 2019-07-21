#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="jobs"
  local deps=("pools" "utils")
  local inc=()
  local libSrc=("job" "jobManager" "worker" "jobScheduler")
  local exeSrc=()
  local libDirs=()
  local libs=()
  local packages=()

  inc+=" ${defaultInc[@]}"
  libDirs+=" ${defaultLibDirs[@]}"
  libs+=" ${defaultLibs[@]}"

  doTheThing $1 $subProject deps inc libSrc exeSrc libDirs libs packages

  return $?
}

main $1
return $?
