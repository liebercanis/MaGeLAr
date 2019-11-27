#!/bin/bash
export projectdir=/home/gold/legend/MaGe
echo "./configure  --disable-g4gdml --enable-streamers --with-rootsys=$ROOTSYS --with-mgdo=/home/admin/MGDO/ --prefix=$projectdir"
./configure  --disable-g4gdml --enable-streamers --with-rootsys=$ROOTSYS --with-mgdo=/home/admin/MGDO/ --prefix=$projectdir

