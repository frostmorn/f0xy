#!/usr/bin/bash
# TODO : Makefile?
clear
echo "Deleting old f0xy binary"
rm f0xy
gcc f0xy.c -lpthread -ltoxcore -lsodium -lm -g3 -o f0xy -O0 -g3
