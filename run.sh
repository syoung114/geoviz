#!/bin/bash

#if I want to compile from the beginning...
if [ "$1" = "--reset" ]; then
    rm -rf build; mkdir build; cd build; cmake ..; make all; ./geoviz $2; cd ..

#debug with gdb. need to recompile everything here
elif [ "$1" = "--debug" ]; then
    rm -rf build; mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=Debug ..; make all; gdb geoviz $2; cd ..

#run normally without compiling dependences (assuming they are already compiled)
else
    cd build; make all; ./geoviz $1; cd ..

fi
