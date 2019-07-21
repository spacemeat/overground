rm bin/exe-boiler
cd utils
source do.sh buildlib
cd ../boiler
source do.sh buildexe
cd ..
bin/exe-boiler boiler/defs.hu assets
rm obj/*
