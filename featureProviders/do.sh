#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="assetProviders"
  local deps=("graphics" "engine" "assets" "pools" "jobs" "utils")
  local inc=()
  local libSrc=("featureProvider")
  local exeSrc=()
  local libDirs=()
  local libs=()
  local packages=("glfw3")

  inc+=" ${defaultIncWithVk[@]}"
  libDirs+=" ${defaultLibDirsWithVk[@]}"
  libs+=" ${defaultLibsWithVk[@]}"

  doTheThing $1 $subProject deps inc libSrc exeSrc libDirs libs packages

  return $?
}

main $1
return $?
