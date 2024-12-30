#!/bin/sh

make clean
rm rl-linux_build
clear
make -j4
mv output/main ./rl-linux_build
./rl-linux_build "$@"
