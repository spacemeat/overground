#!/bin/bash

source ../buildproj.sh

subProject="assets"
deps=("pools" "jobs" "utils")
inc=("../../ansiTermCpp/inc" "../../humon/inc" "../../../balls/vulkan/1.1.77.0/x86_64/include")
src=("fileRegistry" "assetPack" "checkForFileUpdateJob" "loadHumonFileJob" "initFromHumonJob" "config" "mesh" "model")
libDirs=("../../humon/bin")
libs=("humon-d")
packages=()

if [ "$1" == "buildlib" ]; then
  buildlib $subProject deps inc packages src || return $?
elif [ "$1" == "buildtest" ]; then
  buildlib $subProject deps inc packages src || return $?
  buildtest $subProject deps inc libDirs libs packages
elif [ "$1" == "runtest" ]; then
  runtest $subProject || return $?
fi

return 0
