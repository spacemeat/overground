#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="engine"
  local deps=("graphics" "assetProviders" "assets" "pools" "jobs" "utils")
  local inc=()
  local src=("engine")
  local libDirs=()
  local libs=()
  local packages=("glfw3")

  inc+=" ${defaultIncWithVk[@]}"
  libDirs+=" ${defaultLibDirsWithVk[@]}"
  libs+=" ${defaultLibsWithVk[@]}"

  doTheThing $1 $subProject deps inc src libDirs libs packages

  return $?
}

main $1
return $?
