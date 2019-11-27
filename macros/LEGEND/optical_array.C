#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(){

  ofstream outputFile;
  //Make sure fileName is unique,
  //i.e. if you are running interior SiPMs only,
  //indicate that in the fileName
  //also...
  //fileName will have the run number appended to it
  string fileName = "optical14String";
  //string fileName = "optical";
  //First bin is from 845 to 850
  //Last bin is from -850 to -845
  double zMax = 845;
  double zMin = -850;
  double binSize = 5;
  int Nevents = (zMax-zMin)/binSize+1;

  for(int i = 0; i < Nevents ; i++){
    double z = zMax - binSize*i;
    cout<<"Setting Z to "<<z<<"mm...Range is from 850mm to -850mm , fileName is "<<fileName+ std::to_string(i) +string(".mac")<<endl;
    string n = std::to_string(i);
    outputFile.open(fileName + std::to_string(i) +string(".mac"));
    
    outputFile<<"/MG/manager/mglog routine"<<endl;
    outputFile<<"/MG/manager/seedWithUUID"<<endl;
    outputFile<<"/MG/processes/realm DarkMatter"<<endl; 
    outputFile<<"/MG/processes/lowenergy false"<<endl;
    outputFile<<"/MG/processes/opticalOnly true"<<endl;

    outputFile<<"/MG/geometry/detector LGND_200_14String"<<endl; 
    outputFile<<"/MG/L200/RadonShroudRadius 700 mm"<<endl;
    outputFile<<"/MG/L200/SetSensitiveVolumeArgon false"<<endl;
    outputFile<<"/MG/L200/SetSensitiveVolumeGermanium false"<<endl;
    outputFile<<"/MG/L200/SetSensitiveVolumeSiPM true"<<endl;
    //outputFile<<"/MG/L200/SetSensitiveVolumeSiPMOuter true"<<endl;
    outputFile<<"/MG/L200/SetSensitiveVolumeSiPMInner true"<<endl;

    outputFile<<"/run/initialize"<<endl;

    outputFile<<"/MG/eventaction/rootschema MCOpticalRun"<<endl;
    outputFile<<"/MG/eventaction/reportingfrequency 10"<<endl;
    outputFile<<"/MG/eventaction/rootfilename "<<fileName  + std::to_string(i) <<".root"<<endl;

    outputFile<<"/MG/io/MCOpticalRun/SetSensitiveIDLabelScheme askGeom"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/setRunID 001"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/useTimeWindow true"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/setTimeWindow 86400 second"<<endl;
    outputFile<<"/MG/io/MCOpticalRun/setNSteps 10000000000000"<<endl;

    outputFile<<"/MG/generator/select LGNDLiquidArgon"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetRadiusMin 0. mm"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetRadiusMax 300. mm"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetHeight "<<to_string(z)<<" mm"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetCenterVector 0.0 0.0 0.0 mm"<<endl;
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetNParticles 1"<<endl;
    //Voxel size
    outputFile<<"/MG/generator/LGNDLiquidArgon/SetBinWidth 5 mm"<<endl;

    //number of events per voxel = beamOn*SetNParticles
    //usually set SetNParticles = 1
    outputFile<<"/run/beamOn 1"<<endl;
    outputFile.close();
  }

return 0;

}
