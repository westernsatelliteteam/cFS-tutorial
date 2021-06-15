#!/bin/bash
# prep, compile, install the build, switch into the directory, then run cFS
make prep &&                  \
make &&                       \
make install &&               \
cd $O/exe/cpu1 &&             \
echo "Installed to $O" &&     \
./core-cpu1