rm bin/exe-boiler
cd utils
source do.sh buildlib
cd ../boiler
source do.sh buildexe
cd ..
gdb --args bin/exe-boiler assembly assembly/defs.hu assembly-gen
gdb --args bin/exe-boiler enums ../../balls/vulkan/1.1.77.0/x86_64/include/vulkan/vulkan.hpp utils
# rm obj/*

