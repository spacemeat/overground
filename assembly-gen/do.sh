#!/bin/bash

source ../buildproj.sh
source ../buildDefaults.sh

main() {
  local subProject="assembly-gen"
  local deps=("engine" "utils")
  local inc=()
  local libSrc=("assembly-gen" "asset-gen" "commandList-gen" "config-gen" "material-gen" "model-gen" "renderPlan-gen" "tableau-gen" )
  local exeSrc=()
  local libDirs=()
  local libs=()
  local packages=()

  inc+=" ${defaultIncWithVk[@]}"
  libDirs+=" ${defaultLibDirsWithVk[@]}"
  libs+=" ${defaultLibsWithVk[@]}"

  doTheThing $1 $subProject deps inc libSrc exeSrc libDirs libs packages

  return $?
}

main $1
return $?
