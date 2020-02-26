//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//                                                                           //
//                                                                           //
//                         MaGe Simulation                                   //
//                                                                           //
//      This code implementation is the intellectual property of the         //
//      MAJORANA and Gerda Collaborations. It is based on Geant4, an         //
//      intellectual property of the RD44 GEANT4 collaboration.              //
//                                                                           //
//                        *********************                              //
//                                                                           //
//    Neither the authors of this software system, nor their employing       //
//    institutes, nor the agencies providing financial support for this      //
//    work  make  any representation or  warranty, express or implied,       //
//    regarding this software system or assume any liability for its use.    //
//    By copying, distributing or modifying the Program (or any work based   //
//    on on the Program) you indicate your acceptance of this statement,     //
//    and all its terms.                                                     //
//                                                                           //
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//---------------------------------------------------------------------------//
/**                                                            
 * $Id: MJAnalysisWF.cc,v 1.2 2006-06-05 23:19:41 jasondet Exp $
 *      
 * CLASS DECLARATION:  MJAnalysisWF.cc
 *
 *---------------------------------------------------------------------------//
 *
 * DESCRIPTION: 
 *
 * Sample wf generation program for Majorana.
 *
 * AUTHOR: J. Detwiler
 * CONTACT: 
 * FIRST SUBMISSION: Wed Jan  4 15:01:33 PST 2006
 * 
 * REVISION:
 * 
 * 05-01-2006, Created, J. Detwiler
 *
 */


#include "CLHEP/ClhepVersion.h"
#include "G4Version.hh"

#include "globals.hh"
#include "G4PhysListFactory.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4UImanager.hh"
#include "G4UIsession.hh"
#include "G4UIterminal.hh"
#include "G4VisManager.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"


#include "io/MGLogger.hh"
#include "mjprocessors/MGAnalysisWFGeneration.hh"
#include "waveform/MGWFGenGaussResponse.hh"

//using namespace MGWF;
using namespace std;
using namespace CLHEP;

int main(int argc, char *argv[])
{
  MGLog(routine) << "Going..." << endlog;
  MGLogger::SetSeverity(MGLogger::routine);
  if(argc == 1) {
    MGLog(error) << "No file specified!" << endlog;
  } else {
    G4double preTriggerTime = 10.0*ns, sigma = 10.0*ns, delay = 30.0*ns;
    MGWFGenGaussResponse wfGenGauss(preTriggerTime, sigma, delay);
    //wfGenGauss.SetSegmentationParameters(3, 2, 0.4*cm, 3.1*cm, 7.0*cm, 6.0*cm); // nz, nphi, r_i, r_o, h, well depth
    wfGenGauss.SetWaveformParameters(512, 1.0*GHz); // number of samples, sampling frequency
    MGAnalysisWFGeneration *analysis = new MGAnalysisWFGeneration(&wfGenGauss);
    for(int i = 1; i < argc; i++) {
      analysis->AddMCFile(argv[i]);
      MGLog(routine) << "Adding file : " << argv[i] << endlog;
    }
    analysis->SetNEntriesToProcess(1000);
    analysis->RunAllProcessors();
    MGLog(routine) << "Done..." << endlog;
    delete analysis;
  }
}

