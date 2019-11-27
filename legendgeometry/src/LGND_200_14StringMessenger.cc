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
// $Id: LGND_200_14StringMessenger.cc,v 1.4 2005/03/31 01:02:29 jasondet Exp $
//
// CLASS IMPLEMENTATION:  LGND_200_14StringMessenger.cc
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

#include "legendgeometry/LGND_200_14String.hh"
#include "io/MGLogger.hh"

//---------------------------------------------------------------------------//

#include "legendgeometry/LGND_200_14StringMessenger.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;


LGND_200_14StringMessenger::LGND_200_14StringMessenger(
LGND_200_14String *legend200) : fLegend200(legend200)
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
  fCalibrationSetSourceNumberCmd->SetGuidance("31-33 for ring design (with 3 sources)");
  fCalibrationSetSourceNumberCmd->SetGuidance("41-44 for ring design (with 4 sources)");
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
  fSetSensitiveVolumeSiPM->SetGuidance("Set SiPM Core as sensitive volume, default off");

  fSetSensitiveVolumeSiPMArray = new G4UIcmdWithABool("/MG/L200/SetSensitiveVolumeSiPMArray",this);
  fSetSensitiveVolumeSiPMArray->SetGuidance("Set SiPM Array SiPM Array -N. McFadden design for alternatice to fibers");


  //Use these two commands (inner/outer SiPM) in conjuction
  //with SetSensitiveVolumeSiPM in order to only use inner/outer 
  //SiPM array as sentivitive volumes
  //Mario Schwarz requested this to do multiplicity studies in the LAr
  fSetSensitiveVolumeSiPMOuter = new G4UIcmdWithABool("/MG/L200/SetSensitiveVolumeSiPMOuter",this);
  fSetSensitiveVolumeSiPMOuter->SetGuidance("Set SiPMOuter array as sensitive volume, default true");

  fSetSensitiveVolumeSiPMInner = new G4UIcmdWithABool("/MG/L200/SetSensitiveVolumeSiPMInner",this);
  fSetSensitiveVolumeSiPMInner->SetGuidance("Set SiPMInner array as sensitive volume, default true");
  
  fLiquidCmd = new G4UIcmdWithAString("/MG/L200/SetLiquid", this);
  fLiquidCmd->SetGuidance("Set Active shielding liquid, default is Argon-Liq, other options are Xenon-Doped-Argon-Liq");

}

//---------------------------------------------------------------------------//

LGND_200_14StringMessenger::~LGND_200_14StringMessenger()
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
  delete fSetSensitiveVolumeSiPMOuter;
  delete fSetSensitiveVolumeSiPMInner;
  delete fSetSensitiveVolumeSiPMArray;
  delete fLiquidCmd;


}

//---------------------------------------------------------------------------//

void LGND_200_14StringMessenger::SetNewValue(G4UIcommand *cmd, G4String nV)
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
  else if(cmd == fSetSensitiveVolumeSiPMOuter){
    fLegend200->SetSensitiveVolumeSiPMOuter(fSetSensitiveVolumeSiPMOuter->GetNewBoolValue(nV));
    MGLog(routine)<<"Setting outer SiPM array as a sensitive volume and removing inner array as sensitive volume \n"<<
      "DO NOT use messenger command to remove inner array now that outer array is enabled"<<endlog;
  }
  else if(cmd == fSetSensitiveVolumeSiPMInner){
    fLegend200->SetSensitiveVolumeSiPMInner(fSetSensitiveVolumeSiPMInner->GetNewBoolValue(nV));
    MGLog(routine)<<"Setting inner SiPM array as a sensitive volume and removing outer array as sensitive volume \n"<<
      "DO NOT use messenger command to remove outer array now that inner array is enabled"<<endlog;
  }
  else if(cmd == fSetSensitiveVolumeSiPMArray){
    fLegend200->SetSensitiveVolumeSiPMArray(fSetSensitiveVolumeSiPMArray->GetNewBoolValue(nV));
  }
  else if(cmd == fLiquidCmd)
    fLegend200->SetLiquid(nV);
	return;
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
