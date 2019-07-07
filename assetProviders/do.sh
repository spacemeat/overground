#!/bin/bash

source ../buildproj.sh

main() {
  local subProject="assetProviders"
  local deps=("graphics" "engine" "assets" "pools" "jobs" "utils")
  local inc=("../../ansiTermCpp/inc" "../../humon/inc" "../../../balls/vulkan/1.1.77.0/x86_64/include")
  local src=("config")
  local libDirs=("../../humon/bin" "../../../balls/vulkan/1.1.77.0/x86_64/lib")
  local libs=("graphics-d" "engine-d" "assets-d" "jobs-d" "utils-d" "humon-d" "vulkan" "stdc++fs")
  local packages=("glfw3")

  doTheThing $1 $subProject deps inc src libDirs libs packages

  return $?
}

main $1
return $?