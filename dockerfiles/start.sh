#!/bin/bash
# prep, compile, install the build, switch into the directory, then run cFS
make prep &&                  \
make &&                       \
make install &&               \
echo "Installed to $O" &&     \
if [ "$O" == "build-dev" ]; then
    cd $O/exe/cpu1 &&         \
    ./core-cpu1
fi