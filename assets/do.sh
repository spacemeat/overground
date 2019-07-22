#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="assets"
  local deps=("pools" "jobs" "utils")
  local inc=()
  local libSrc=("asset" "config-gen" "fileReference" "resourceManager")
  local exeSrc=()
  local libDirs=()
  local libs=()
  local packages=()

  inc+=" ${defaultIncWithVk[@]}"
  libDirs+=" ${defaultLibDirsWithVk[@]}"
  libs+=" ${defaultLibsWithVk[@]}"

  doTheThing $1 $subProject deps inc libSrc exeSrc libDirs libs packages

  return $?
}

main $1
return $?
