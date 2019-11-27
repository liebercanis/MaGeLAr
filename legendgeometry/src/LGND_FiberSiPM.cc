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
// CLASS IMPLEMENTATION:  LGND_MiniShroud.cc
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
 * AUTHOR: Neil McFadden
 * CONTACT: ncmfadde@unm.edu
 *
 * REVISION:
 *
 */
//---------------------------------------------------------------------------//
//

#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4UIcommand.hh"

//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "legendgeometry/LGND_FiberSiPM.hh"
#include "legendgeometry/LGND_Part.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;

LGND_FiberSiPM::LGND_FiberSiPM(G4String partName, G4String serialNumber,G4double length) :
  LGND_Part(partName, serialNumber, "LGND_FiberSiPM", "Silicon"),
  fLength(length*mm)
{;}

LGND_FiberSiPM::LGND_FiberSiPM(G4String partName, G4String serialNumber,G4double length,G4String shape) :
  LGND_Part(partName, serialNumber, "LGND_FiberSiPM", "Silicon"),
  fLength(length*mm),
  fShape(shape),
  fPartName(partName),
  fRadius(0)
{
  if(fShape == "") fShape = G4String("square");
  BuildLogicalVolume();
}

LGND_FiberSiPM::LGND_FiberSiPM(G4String partName, G4String serialNumber,G4double length,G4double radius,G4String shape) :
  LGND_Part(partName, serialNumber, "LGND_FiberSiPM", "Silicon"),
  fLength(length*mm),
  fShape(shape),
  fPartName(partName),
  fRadius(radius)
{
  if(fShape == "") fShape = G4String("square");
  BuildLogicalVolume();
}


LGND_FiberSiPM::LGND_FiberSiPM(G4String partName, G4String serialNumber) :
  LGND_Part(partName, serialNumber, "LGND_FiberSiPM", "Silicon")
{;}

LGND_FiberSiPM::LGND_FiberSiPM(const LGND_FiberSiPM & rhs) :
  LGND_Part(rhs)
{;}

LGND_FiberSiPM::~LGND_FiberSiPM()
{;}

G4LogicalVolume* LGND_FiberSiPM::BuildLogicalVolume()
{
  G4LogicalVolumeStore *storePtr = G4LogicalVolumeStore::GetInstance();
  //remove all non alphabetic characters from the string,
  //want one fPartName per array
  fPartName.erase(remove_if(fPartName.begin(), fPartName.end(), [](char c) { return !isalpha(c); } ), fPartName.end());
  G4String logicalName = fPartName + fDrawingNumber + "_" + fPartMaterial+"x"+G4UIcommand::ConvertToString(fLength);
  G4LogicalVolume* pVol = storePtr->GetVolume(logicalName, false);
  G4VSolid* SiPMSolid;
  //SiPM thickness is ~.1mm
  G4double radius_inner = 0;//1*mm + .01*mm;
  G4double radius_outer = .5*mm + 200.*nm;
  if(fRadius  == 0)
    fRadius = radius_outer;
  else
    radius_outer = fRadius;

  if(pVol == NULL){
    if(fShape == "square"){
      //A Box is a cuboid of given half lengths
      //centred on the origin with sides parallel to the x/y/z axes.
      SiPMSolid = new G4Box("SiPMSolid",radius_outer,radius_outer,fLength);
      //G4cout<<"Radius outer "<<radius_outer/mm<<", radius inner "<<radius_inner/mm<<G4endl;
    }
    else if(fShape == "circle"){
      SiPMSolid = new G4Tubs("SiPMSolid",radius_inner,radius_outer,fLength,0,2*pi);
    }
    else
      MGLog(error) << "Incorrect shape for fiber core : "<<fShape<<" not valid! \n use square or cirlce"<<endlog;
    
    pVol = new G4LogicalVolume(SiPMSolid,G4Material::GetMaterial(this->GetMaterial()),logicalName);
    G4VisAttributes* greyVisAtt = new G4VisAttributes(G4Colour(0.4,0.74,.9,1)); 
    greyVisAtt->SetForceWireframe( false );
    pVol->SetVisAttributes(greyVisAtt);
  }


  return pVol;
}
