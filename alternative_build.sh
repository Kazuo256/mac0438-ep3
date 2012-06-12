#!/bin/bash

builddir=build

if [ ! -d $builddir ]; then
  mkdir $builddir
fi

cd $builddir
cmake ..
make
cd ..
mv $builddir/ep3 .


