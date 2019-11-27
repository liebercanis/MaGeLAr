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
// $Id: MGcodeTemplate.cc,v 1.1 2004-12-09 08:58:35 pandola Exp $
//
// CLASS IMPLEMENTATION:  LGND_HVSigCable.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 *
 *Part Origin:  Coaxial with rod, coincident with top.
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Matthew Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: Feb 13, 2019
 *
 * REVISION:
 *
 * 02-13-2019, Created, M. Green
 */
//---------------------------------------------------------------------------//
//

#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Polycone.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4UIcommand.hh"

//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "legendgeometry/LGND_HVSigCable.hh"
#include "legendgeometry/LGND_Part.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;


LGND_HVSigCable::LGND_HVSigCable(G4String partName, G4String serialNumber, G4double length, G4String material) :
  LGND_Part(partName, serialNumber, "LGND_HVSigCable", material),
  fLength(length*mm)
{;}

LGND_HVSigCable::LGND_HVSigCable(G4String partName, G4String serialNumber, G4double length) :
  LGND_Part(partName, serialNumber, "LGND_HVSigCable", "Copper-EF"),
  fLength(length*mm)
{;}

LGND_HVSigCable::LGND_HVSigCable(const LGND_HVSigCable & rhs) :
  LGND_Part(rhs)
{;}

LGND_HVSigCable::~LGND_HVSigCable()
{;}

G4LogicalVolume* LGND_HVSigCable::BuildLogicalVolume()
{
  G4LogicalVolumeStore *storePtr = G4LogicalVolumeStore::GetInstance();
  G4String logicalName = fDrawingNumber + "_" + fPartMaterial+"x"+G4UIcommand::ConvertToString(fLength);
  G4LogicalVolume* pVol = storePtr->GetVolume(logicalName, false);
  if (pVol == NULL){

    G4double rout[2] = {0.1*mm, 0.1*mm};
    G4double rin[2] = {0.0*mm, 0.0*mm};
    G4double z[2] = {0.0, -fLength*mm};

    G4Polycone* cable = new G4Polycone("cable", 0.0, 2*pi, 2, z, rin, rout);

    G4VisAttributes* copperVisAtt = new G4VisAttributes(G4Colour(0.839,0.373,0.169,0.5)); //copper color
    copperVisAtt->SetForceWireframe( false );
    G4Material *material = G4Material::GetMaterial(this->GetMaterial());
    pVol = new G4LogicalVolume(cable, material, logicalName);
    pVol->SetVisAttributes(copperVisAtt);
    MGLog(debugging) << "Created Cable Logical" << endlog;
  }
  else  MGLog(debugging) << "Using pre-existing Cable Logical" << endlog;

  return pVol;
}
