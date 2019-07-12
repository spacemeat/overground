#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="assets"
  local deps=("pools" "jobs" "utils")
  local inc=()
  local src=("asset" "configData" "fileReference" "resourceManager" "updateJobs")
  local libDirs=()
  local libs=()
  local packages=()

  inc+=" ${defaultInc[@]}"
  libDirs+=" ${defaultLibDirs[@]}"
  libs+=" ${defaultLibs[@]}"

  doTheThing $1 $subProject deps inc src libDirs libs packages

  return $?
}

main $1
return $?
