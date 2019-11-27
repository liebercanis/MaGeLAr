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
//
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 * This class is used to place cylinders or boxs of custum size
   in order to help with the debugging of object placement
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Neil McFadden
 * CONTACT: nmcfadde@unm.edu
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
#include "legendgeometry/LGND_DebugPart.hh"
#include "legendgeometry/LGND_Part.hh"

//---------------------------------------------------------------------------//
//
using namespace CLHEP;

LGND_DebugPart::LGND_DebugPart(G4double x, G4double y, G4double z,G4double r = 0,G4String shape = "") :
  LGND_Part("LGND_DebugPart", "", "", "PolystyreneFiber"),
  fShape(shape),fX(x),fY(y),fZ(z),fR(r)
{
  BuildLogicalVolume();
}

LGND_DebugPart::LGND_DebugPart(const LGND_DebugPart & rhs) :
  LGND_Part(rhs)
{;}

LGND_DebugPart::~LGND_DebugPart()
{;}

G4LogicalVolume* LGND_DebugPart::BuildLogicalVolume()
{
  G4LogicalVolumeStore *storePtr = G4LogicalVolumeStore::GetInstance();
  G4String logicalName = fDrawingNumber + "_" + fPartMaterial+"x"+fPartName;
  G4LogicalVolume* pVol = storePtr->GetVolume(logicalName, false);
  
  if(pVol == NULL){
    G4VSolid* coreSolid;
    //A Box is a cuboid of given half lengths
    //centred on the origin with sides parallel to the x/y/z axes.
    if(fShape == "square"){
      coreSolid = new G4Box("coreSolid",fX/2.,fY/2.,fZ/2);
    } 
    else if(fShape == "circle"){
      coreSolid = new G4Tubs("coreSolid",0,fR,fZ/2,0,2*pi);
    }
    else
      MGLog(error) << "Incorrect shape for debugVolume : "<<fShape<<" not valid! \n use square or cirlce"<<endlog;

    pVol = new G4LogicalVolume(coreSolid,G4Material::GetMaterial(this->GetMaterial()),logicalName); 
  }


  return pVol;
}
