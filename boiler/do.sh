#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="boiler"
  local deps=("utils")
  local inc=()
  local libSrc=()
  local exeSrc=("assemblies" "enums" "main")
  local libDirs=()
  local libs=()
  local packages=()

  inc+=" ${defaultInc[@]}"
  libDirs+=" ${defaultLibDirs[@]}"
  libs+=" ${defaultLibs[@]}"

  doTheThing $1 $subProject deps inc libSrc exeSrc libDirs libs packages

  return $?
}

main $1
return $?
