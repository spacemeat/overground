#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="utils"
  local deps=()
  local inc=()
  local src=("utils" "logger")
  local libDirs=()
  local libs=()
  local packages=()

  inc+=" ${defaultInc[@]}"
  libDirs+=" ${defaultLibDirs[@]}"
  libs+=" ${defaultLibs[@]}"

  doTheThing $1 $subProject deps inc src libDirs libs packages

  return $?
}

main $1
return $?
