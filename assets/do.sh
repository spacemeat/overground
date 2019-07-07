#!/bin/bash

source ../buildproj.sh

main() {
  local subProject="assets"
  local deps=("pools" "jobs" "utils")
  local inc=("../../ansiTermCpp/inc" "../../humon/inc")
  local src=("asset" "configData" "fileReference" "resourceManager" "updateJobs")
  local libDirs=("../../humon/bin")
  local libs=("jobs-d" "utils-d" "humon-d" "vulkan" "stdc++fs")
  local packages=()

  doTheThing $1 $subProject deps inc src libDirs libs packages

  return $?
}

main $1
return $?
