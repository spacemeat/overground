#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="graphics"
  local deps=("engine" "assets" "assetProviders" "pools" "jobs" "utils")
  local inc=()
  local libSrc=("graphics" "instance" "window" "physDev" "device" "surface" "swapchain" "renderPass" "framebuffer" "commandList")
  local exeSrc=()
  local libDirs=()
  local libs=("engine-d")
  local packages=("glfw3")

  inc+=" ${defaultIncWithVk[@]}"
  libDirs+=" ${defaultLibDirsWithVk[@]}"
  libs+=" ${defaultLibsWithVk[@]}"

  doTheThing $1 $subProject deps inc libSrc exeSrc libDirs libs packages

  return $?
}

main $1
return $?
