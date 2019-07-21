INV="g++ --std=c++2a -Wall -g -O0 -c"
ARG="-fno-stack-protector -Wno-class-memaccess"
OUT="-o boiler.o"
SRC="boiler.cpp"
INC="-I../utils/inc  -I../../ansiTermCpp/inc -I../../humon/inc -I../../fmt/include"

CCMD="$INV $ARG $OUT $SRC $INC"
echo $CCMD
eval $CCMD

INV="g++ --std=c++2a -Wall -g -O0"
OUT="-o boiler"
SRC="boiler.o"
LIBDIR=" -L../bin -L../../humon/bin -L../../../balls/vulkan/1.1.77.0/x86_64/lib -L../../../balls/fmt/build-5.3.0"
LIB="-pthread -Wl,--start-group -lutils-d -lhumon-d -lvulkan -lstdc++fs -lfmt -Wl,--end-group"

LCMD="$INV $ARG $OUT $LIBDIR $SRC $LIB"
echo $LCMD
eval $LCMD
