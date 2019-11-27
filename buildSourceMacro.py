#!/usr/bin/env python
import sys
import os
import subprocess
import numpy as np
import math
import pprint


def main(args):
    if len(args)==0: 
        print(' enter valid number 1,2,or 3 ')
        exit(0)

    jobn = int(args[0]) 
    if (jobn<1 or jobn>3) :
        print(' enter valid number 1,2,or 3 ')
        exit(0)

    jobn = jobn+30
    macroname = 'TlSource-job%i.mac' % jobn
    outputname = 'TlSource-job%i.root' % jobn
    print(macroname,' ',outputname)
    exists = os.path.isfile(macroname)
    if exists:
        print('removing existing %s' %macroname)
        call='rm %s'% macroname
        os.system(call)
    # Load configuration file values
    # Load configuration file values
    f = open(macroname, 'w')
    print(f,' ',outputname)
    f.write('/MG/manager/mglog  routine \n')
    f.write('/MG/manager/seedWithUUID\n')
    f.write('/MG/processes/realm BBdecay\n')
    f.write('/MG/processes/lowenergy true\n')
    f.write('/MG/geometry/detector LGND_200_14String\n')
    f.write('/MG/eventaction/reportingfrequency 10000\n')
    f.write('/MG/L200/CalibrationOn true\n')
    f.write('/MG/L200/CalibrationSetSourceNumber  %i \n' % jobn)
    f.write('/MG/L200/CalibrationSetSourceHeight 500 mm #0 # -500 mm\n')
    f.write('/MG/L200/CalibrationSetAbsorber true \n')
    f.write('/MG/L200/SetSensitiveVolumeArgon true \n')
    f.write('/MG/L200/SetSensitiveVolumeGermanium true\n')
    f.write('/MG/eventaction/rootschema MCRun\n')
    f.write('/MG/io/MCRun/SetSensitiveIDLabelScheme askGeom\n')
    f.write('/MG/eventaction/rootfilename %s \n' % outputname)
    f.write('/MG/eventaction/reportingfrequency 1000\n')
    f.write('/MG/generator/select LGND200Calibration\n')
    f.write('/MG/generator/LGND200Calibration/setZ 81\n')
    f.write('/MG/generator/LGND200Calibration/setA 208\n')
    f.write('/run/initialize \n')
    f.write('/run/beamOn 500000\n')
    f.close()

#print(" yar ",__name__)
if __name__ == "__main__":
    main(sys.argv[1:])
