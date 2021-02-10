#!/bin/bash

cd FileSys

make clean

make

./crFilesys -f -o allow_other /tmp/filesys1