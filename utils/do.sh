#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="utils"
  local deps=()
  local inc=()
  local libSrc=("enumParsers" "enumParsers-gen" "graphicsUtils" "utils" "logger")
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
