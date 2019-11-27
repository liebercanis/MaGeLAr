#!/bin/bash
alias dds='ls --color -alsF'
export SHIFTER=/global/project/projectdirs/m2676/users/mgold/shifter
export PATH=./:$PATH
export G4WORKDIR=/global/project/projectdirs/m2676/users/mgold/shifter/MaGeLAr
source $SHIFTER/rootsetup.sh
echo $G4WORKDIR
echo $SHIFTER
echo $PATH
echo "./configure  --disable-g4gdml --enable-streamers --with-rootsys=/opt/root --with-mgdo=$SHIFTER/MGDO --prefix=$SHIFTER/MaGeLAr"
