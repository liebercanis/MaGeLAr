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
// $Id: MGGeneratorLGNDCablesMessenger.cc,v 1.2 2007-02-21 09:31:33 mgmarino Exp $
//
// CLASS IMPLEMENTATION:  MGGeneratorLGNDCablesMessenger.cc
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
 * AUTHOR: M. Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: 02-18-2019
 *
 * REVISION:
 *
 * Feb-2019, Adopted from Calibration Messenger, M. Green
 *
 */
//---------------------------------------------------------------------------//
//

#include "globals.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include "generators/MGGeneratorLGNDCables.hh"

//---------------------------------------------------------------------------//

#include "generators/MGGeneratorLGNDCablesMessenger.hh"

//---------------------------------------------------------------------------//

MGGeneratorLGNDCablesMessenger::MGGeneratorLGNDCablesMessenger(
MGGeneratorLGNDCables *generator) : fLGNDCablesGenerator(generator)
{
  // /MG/generator/LGNDCables
  fLGNDCablesDirectory = new G4UIdirectory("/MG/generator/LGNDCables/");
  fLGNDCablesDirectory->SetGuidance("LGND HV/Signal Cable generator control.");

  // MG/generator/LGNDCables/dump
  fDumpCmd = new G4UIcmdWithoutParameter("/MG/generator/LGNDCables/dump", this);
  fDumpCmd->SetGuidance("Dump parameters of generator to screen");

  // /MG/generator/LGNDCables/setZ
  fZCmd = new G4UIcmdWithAnInteger("/MG/generator/LGNDCables/setZ", this);
  fZCmd->SetGuidance("The Z value of the ion");

  // /MG/generator/LGNDCables/setA
  fACmd = new G4UIcmdWithAnInteger("/MG/generator/LGNDCables/setA", this);
  fACmd->SetGuidance("The A value of the ion");

}

//---------------------------------------------------------------------------//

MGGeneratorLGNDCablesMessenger::MGGeneratorLGNDCablesMessenger(const MGGeneratorLGNDCablesMessenger & other) : G4UImessenger(other)
{;}

//---------------------------------------------------------------------------//

MGGeneratorLGNDCablesMessenger::~MGGeneratorLGNDCablesMessenger()
{
  delete fACmd;
  delete fZCmd;
  delete fDumpCmd;
  delete fLGNDCablesDirectory;
}


//---------------------------------------------------------------------------//

void MGGeneratorLGNDCablesMessenger::SetNewValue(G4UIcommand *cmd, G4String newValues)
{
  if(cmd == fZCmd)
    fLGNDCablesGenerator->SetIonZ(fZCmd->GetNewIntValue(newValues));
  else if(cmd == fACmd)
    fLGNDCablesGenerator->SetIonA(fACmd->GetNewIntValue(newValues));
  else if(cmd == fDumpCmd)
    fLGNDCablesGenerator->Dump();
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
