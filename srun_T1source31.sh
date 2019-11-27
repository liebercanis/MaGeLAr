#!/bin/bash
export projectdir=/global/project/projectdirs/m2676/users/mgold/shifter/MaGe
echo "salloc --qos=interactive -C haswell -n 1"
echo "shifter --env-file=$projectdir/MaGeEnvirons --image docker:legendexp/legend-base:latest $projectdir/bin/MaGe $projectdir/TlSource-job31.mac"
#salloc --qos=interactive -C haswell -n 1
shifter --env-file=$projectdir/MaGeEnvirons --image docker:legendexp/legend-base:latest $projectdir/bin/MaGe $projectdir/TlSource-job31.mac
