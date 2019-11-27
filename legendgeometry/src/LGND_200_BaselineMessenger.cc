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
//                                                          
// $Id: LGND_200_BaselineMessenger.cc,v 1.4 2005/03/31 01:02:29 jasondet Exp $ 
//      
// CLASS IMPLEMENTATION:  LGND_200_BaselineMessenger.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 * 
 *
 */
// 
//---------------------------------------------------------------------------//
/**
 * AUTHOR: R. Massarczyk
 * CONTACT: massarczyk@lanl.gov
 * FIRST SUBMISSION: May 2018
 * 
 * REVISION:
 *
 * 05-2018, Created, R. Massarczyk
 */
//---------------------------------------------------------------------------//
//

#include "globals.hh"
#include "G4ios.hh"
#include "G4ApplicationState.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIdirectory.hh"

#include "legendgeometry/LGND_200_Baseline.hh"
#include "io/MGLogger.hh"

//---------------------------------------------------------------------------//

#include "legendgeometry/LGND_200_BaselineMessenger.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;


LGND_200_BaselineMessenger::LGND_200_BaselineMessenger(
LGND_200_Baseline *legend200) : fLegend200(legend200)
{
  // /LEGEND-200
  fLegend200Directory = new G4UIdirectory("/MG/L200/");

  fTestCmd = new G4UIcmdWithAString("/MG/L200/SetTest", this);
  fTestCmd->SetGuidance("This is just a test until we have more commands");
  fTestCmd->AvailableForStates(G4State_PreInit);

	fCalibrationCmd = new G4UIcmdWithABool("/MG/L200/CalibrationOn", this);
  fCalibrationCmd->SetGuidance("Set to true to use calibration source");
	fCalibrationCmd->AvailableForStates(G4State_PreInit);

	fCalibrationSetSourceNumberCmd = new G4UIcmdWithAnInteger("/MG/L200/CalibrationSetSourceNumber", this);
  fCalibrationSetSourceNumberCmd->SetGuidance("Set the source you wanna use");
  fCalibrationSetSourceNumberCmd->SetGuidance("1-6 standard between middle and outer ring");
  fCalibrationSetSourceNumberCmd->SetGuidance("11-13 in the middle ring (replace JSONfile)");
  fCalibrationSetSourceNumberCmd->SetGuidance("21-23 in the outer ring (replace JSONfile)");
	//fCalibrationSetSourceNumberCmd->AvailableForStates(G4State_PreInit);

	fCalibrationSetSourcePositionCmd = new G4UIcmdWithADoubleAndUnit("/MG/L200/CalibrationSetSourceHeight", this);
  fCalibrationSetSourcePositionCmd->SetGuidance("Set Z position of the selected source");
  fCalibrationSetSourcePositionCmd->SetGuidance("between xxx and yyy mm");

	fCalibrationSetAbsorberCmd = new G4UIcmdWithABool("/MG/L200/CalibrationSetAbsorber", this);
  fCalibrationSetAbsorberCmd->SetGuidance("Set to true to put copper absorber in place");
	fCalibrationSetAbsorberCmd->AvailableForStates(G4State_PreInit);

  fRadonShoudRadius = new G4UIcmdWithADoubleAndUnit("/MG/L200/RadonShroudRadius",this);
  fRadonShoudRadius->SetGuidance("Set Radon Shroud Radius");
  fRadonShoudRadius->SetGuidance("Suggest radii are 375 mm, 500 mm, 700 mm");

  fSetSensitiveVolumeArgon = new G4UIcmdWithABool("/MG/L200/SetSensitiveVolumeArgon",this);
  fSetSensitiveVolumeArgon->SetGuidance("Set Liquid Argon ('Detector') as sensitive volume, default on");
  
  fSetSensitiveVolumeGermanium = new G4UIcmdWithABool("/MG/L200/SetSensitiveVolumeGermanium",this);
  fSetSensitiveVolumeGermanium->SetGuidance("Set Germanium as sensitive volume, default on");

  fSetSensitiveVolumeFiberCore = new G4UIcmdWithABool("/MG/L200/SetSensitiveVolumeFiberCore",this);
  fSetSensitiveVolumeFiberCore->SetGuidance("Set Fiber Core as sensitive volume, default off");

  fSetSensitiveVolumeSiPM = new G4UIcmdWithABool("/MG/L200/SetSensitiveVolumeSiPM",this);
  fSetSensitiveVolumeFiberCore->SetGuidance("Set SiPM Core as sensitive volume, default off");

}

//---------------------------------------------------------------------------//

LGND_200_BaselineMessenger::~LGND_200_BaselineMessenger()
{

	delete fTestCmd;
	delete fCalibrationCmd;
	delete fCalibrationSetSourcePositionCmd;
	delete fCalibrationSetSourceNumberCmd;
	delete fCalibrationSetAbsorberCmd;
  delete fLegend200Directory;
  delete fRadonShoudRadius;
  delete fSetSensitiveVolumeArgon;
  delete fSetSensitiveVolumeGermanium;
  delete fSetSensitiveVolumeFiberCore;
  delete fSetSensitiveVolumeSiPM;
	
}

//---------------------------------------------------------------------------//

void LGND_200_BaselineMessenger::SetNewValue(G4UIcommand *cmd, G4String nV)
{
	if (cmd == fTestCmd) fLegend200->SetTest(nV);
	else if (cmd == fCalibrationCmd)
		fLegend200->SetCalibration(fCalibrationCmd->GetNewBoolValue(nV));
	else if (cmd == fCalibrationSetSourceNumberCmd) 
		fLegend200->SetCalibrationSourceNumber(fCalibrationSetSourceNumberCmd->GetNewIntValue(nV));
	else if (cmd == fCalibrationSetSourcePositionCmd) 
		fLegend200->SetCalibrationSourcePosition(fCalibrationSetSourcePositionCmd->GetNewDoubleValue(nV));
	else if (cmd == fCalibrationSetAbsorberCmd)
		fLegend200->SetCalibrationAbsorber(fCalibrationSetAbsorberCmd->GetNewBoolValue(nV));
  else if (cmd == fRadonShoudRadius)
    fLegend200->SetRadonShieldRadius(fRadonShoudRadius->GetNewDoubleValue(nV));
  else if (cmd == fSetSensitiveVolumeArgon)
    fLegend200->SetSensitiveVolumeArgon(fSetSensitiveVolumeArgon->GetNewBoolValue(nV));
  else if (cmd == fSetSensitiveVolumeGermanium)
    fLegend200->SetSensitiveVolumeGermanium(fSetSensitiveVolumeGermanium->GetNewBoolValue(nV));
  else if (cmd == fSetSensitiveVolumeFiberCore)
    fLegend200->SetSensitiveVolumeFiberCore(fSetSensitiveVolumeFiberCore->GetNewBoolValue(nV));
  else if (cmd == fSetSensitiveVolumeSiPM)
    fLegend200->SetSensitiveVolumeSiPM(fSetSensitiveVolumeSiPM->GetNewBoolValue(nV));  
	return;
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
