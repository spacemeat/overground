#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="graphics"
  local deps=("assets" "pools" "jobs" "utils")
  local inc=()
  local src=("graphics" "graphicsUtils" "instance" "window" "physDev" "device" "swapchain")
  local libDirs=()
  local libs=("engine-d")
  local packages=("glfw3")

  inc+=" ${defaultIncWithVk[@]}"
  libDirs+=" ${defaultLibDirsWithVk[@]}"
  libs+=" ${defaultLibsWithVk[@]}"

  doTheThing $1 $subProject deps inc src libDirs libs packages

  return $?
}

main $1
return $?
