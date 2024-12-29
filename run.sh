#!/bin/sh

make clean
clear
make -j4
./output/main "$@"
