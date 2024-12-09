#!/bin/sh

clear
make clean
make -j4
./output/main "$@"
