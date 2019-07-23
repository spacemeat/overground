rm bin/exe-boiler
cd utils
source do.sh buildlib
cd ../boiler
source do.sh buildexe
cd ..
bin/exe-boiler assets assets/defs.hu assets
bin/exe-boiler enums ../../balls/vulkan/1.1.77.0/x86_64/include/vulkan/vulkan.hpp utils
rm obj/*

