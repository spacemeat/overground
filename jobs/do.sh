#!/bin/bash

source ../buildproj.sh

main() {
  local subProject="jobs"
  local deps=("pools" "utils")
  local inc=("../../humon/inc" "../../../balls/vulkan/1.1.77.0/x86_64/include")
  local src=("job" "jobManager" "worker")
  local libDirs=("../../humon/bin")
  local libs=("jobs-d" "utils-d" "humon-d")
  local packages=()

  doTheThing $1 $subProject deps inc src libDirs libs packages

  return $?
}

main $1
return $?
