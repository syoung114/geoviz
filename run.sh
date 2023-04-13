#!/bin/bash
if [ $1 = '--reset' ]; then
    rm -rf build; mkdir build; cd build; cmake ..
else
    cd build
fi
make all; ./geoviz; cd ..
