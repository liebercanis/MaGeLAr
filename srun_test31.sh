#!/bin/bash
export projectdir=/global/project/projectdirs/m2676/users/mgold/shifter/MaGeLAr
echo "salloc --qos=interactive -C haswell -n 1"
echo "shifter --env-file=$projectdir/MaGeEnvirons --image docker:legendexp/legend-base:latest $projectdir/bin/MaGe $projectdir/TlSource-test31.mac"
#salloc --qos=interactive -C haswell -n 1
shifter --env-file=$projectdir/MaGeEnvirons --image docker:legendexp/legend-base:latest $projectdir/bin/Linux-g++/MaGe $projectdir/TlSource-test31.mac
