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
 *
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
#include "legendgeometry/LGND_FiberCoreCurved.hh"
#include "legendgeometry/LGND_Part.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;

LGND_FiberCoreCurved::LGND_FiberCoreCurved(G4String partName, G4String serialNumber, G4double length) :
  LGND_Part(partName, serialNumber, "LGND_FiberCoreCurved", "PolystyreneFiber"),
  fLength(length*mm)
{;}
LGND_FiberCoreCurved::LGND_FiberCoreCurved(G4String partName, G4String serialNumber, G4double length, G4String shape, G4double curvatureAngle) :
  LGND_Part(partName, serialNumber, "LGND_FiberCoreCurved", "PolystyreneFiber"),
  fLength(length*mm),
  fShape(shape),
  fCurvatureAngle(curvatureAngle)
{
  if(fShape == "") fShape = G4String("square");
  //When part is declared, logical volume is created, that way there is immediate access to internal part values
  BuildLogicalVolume();
}

LGND_FiberCoreCurved::LGND_FiberCoreCurved(G4String partName, G4String serialNumber) :
  LGND_Part(partName, serialNumber, "LGND_FiberCoreCurved", "PolystyreneFiber")
{;}

LGND_FiberCoreCurved::LGND_FiberCoreCurved(const LGND_FiberCoreCurved & rhs) :
  LGND_Part(rhs)
{;}

LGND_FiberCoreCurved::~LGND_FiberCoreCurved()
{;}

G4LogicalVolume* LGND_FiberCoreCurved::BuildLogicalVolume()
{
  G4LogicalVolumeStore *storePtr = G4LogicalVolumeStore::GetInstance();
  G4String logicalName = fDrawingNumber + "_" + fPartMaterial+"x"+G4UIcommand::ConvertToString(fLength);
  G4LogicalVolume* pVol = storePtr->GetVolume(logicalName, false);
  G4double size_length = 0.5*mm - 0.04*mm-0.02*mm;
  fRadius = size_length;
  if(pVol == NULL){
    G4VSolid* coreSolid;
    //Curved fiber has OD of fLength
    if(fShape == "square"){
      //coreSolid = new G4Tubs("coreSolidCurved",fLength-size_length,fLength+size_length,size_length,0,0.5*pi);
      coreSolid = new G4Tubs("coreSolidCurved",fLength-size_length,fLength+size_length,size_length,0,fCurvatureAngle);
    } 
    else if(fShape == "circle"){
      //coreSolid = new G4Tubs("coreSolid",0,size_length,fLength,0,2*pi);
      coreSolid = new G4Tubs("coreSolid",0,size_length,fLength,0,fCurvatureAngle);
      G4cout<<"Don't make it a circle"<<G4endl;
      return NULL;
    }
    else
      MGLog(error) << "Incorrect shape for fiber core : "<<fShape<<" not valid! \n use square or cirlce"<<endlog;

    pVol = new G4LogicalVolume(coreSolid,G4Material::GetMaterial(this->GetMaterial()),logicalName);
    /*
    G4VisAttributes* greyVisAtt = new G4VisAttributes(G4Colour(0.4,0.74,.9,1)); 
    greyVisAtt->SetForceWireframe( false );
    pVol->SetVisAttributes(greyVisAtt);
    */
  }


  return pVol;
}
