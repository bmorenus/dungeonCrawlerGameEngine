#!/bin/bash

# Set the arguments of each of the options for compiling
# our source code.
# Assume by default this is for linux
COMPILER="g++"
ARGS="-g -std=c++17 -D LINUX"
SRC="./src/*.cpp"
INCLUDE="./include"
BINARY="./prog"
LIBS="-lSDL2 -ldl"

# Echo out the platform we are compilng on.
echo "Compiling on ${OSTYPE}"

# Build the compile string
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo ""
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Compilng on Mac"
    COMPILER="clang++"
    INCLUDE="./include `sdl2-config --clfags`"
    LIBS="`sdl2-config --libs` "
    echo ""
elif [[ "$OSTYPE" == "mysys" ]] ; then
    echo "Compiling on Windows(mysys)"
    ARGS="-g -std=clang++17 -D MINGW"
    LIBS="-lmingw32 -lSDL2main -lSDL2"
    echo ""
else
    echo "Not sure what operating system to build for?? Trying defaults"
    echo ""
fi

COMPILE="${COMPILER} ${ARGS} ${SRC} -I ${INCLUDE} -o ${BINARY} ${LIBS}"

# Write out the compile string for the user to see
echo ${COMPILE}

# Evaluate the compile string
eval $COMPILE
