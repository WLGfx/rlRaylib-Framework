#!/bin/sh

make clean
clear
make -j4
mv output/main ./rl-linux_build
./rl-linux_build "$@"
