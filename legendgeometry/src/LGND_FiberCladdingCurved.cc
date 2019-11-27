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
#include "legendgeometry/LGND_FiberCladdingCurved.hh"
#include "legendgeometry/LGND_Part.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;

LGND_FiberCladdingCurved::LGND_FiberCladdingCurved(G4String partName, G4String serialNumber, G4double length) :
  LGND_Part(partName, serialNumber, "LGND_FiberCladdingCurved", "PMMA"),
  fLength(length*mm)
{;}
LGND_FiberCladdingCurved::LGND_FiberCladdingCurved(G4String partName, G4String serialNumber, G4double length,G4String shape,G4String material,G4double curvatureAngle) :
  LGND_Part(partName, serialNumber, "LGND_FiberCladdingCurved",material),
  fLength(length*mm),
  fShape(shape),
  fCurvatureAngle(curvatureAngle)
{
  if(fShape == "") fShape = G4String("square");  
  //When part is declared, logical volume is created, that way there is immediate access to internal part values
  BuildLogicalVolume();
}
LGND_FiberCladdingCurved::LGND_FiberCladdingCurved(G4String partName, G4String serialNumber) :
  LGND_Part(partName, serialNumber, "LGND_FiberCladdingCurved", "PMMA")
{;}

LGND_FiberCladdingCurved::LGND_FiberCladdingCurved(const LGND_FiberCladdingCurved & rhs) :
  LGND_Part(rhs)
{;}

LGND_FiberCladdingCurved::~LGND_FiberCladdingCurved()
{;}

G4LogicalVolume* LGND_FiberCladdingCurved::BuildLogicalVolume()
{
  //from S. Schonert talk 6/12/2018 (june) "Baseline plan for Liquid Argon Scintillation light readout for LEGEND-200"
  G4LogicalVolumeStore *storePtr = G4LogicalVolumeStore::GetInstance();
  G4String logicalName = fDrawingNumber + "_" + fPartMaterial+"x"+G4UIcommand::ConvertToString(fLength);
  G4LogicalVolume* pVol = storePtr->GetVolume(logicalName, false);
  G4VSolid* claddingSolid;
  G4double lengthTotal = 0.5*mm; //total diameter of fiber
  G4double innerThickness = 0.04*mm;
  G4double outerThickness = 0.02*mm;
  //total thickness of cladding (how much it adds to radius of fiber)
  //Needed when placing
  fRadius = innerThickness+outerThickness; //0.06*mm

  if(pVol == NULL){
    //Inner Cladding n = 1.49
    if(this->GetMaterial() == "PMMA"){
      G4double lengthInner = lengthTotal - innerThickness - outerThickness;
      G4double lengthOuter = lengthTotal - outerThickness;
      if(fShape == "square"){
        /*
        //A Box is a cuboid of given half lengths
        //centred on the origin with sides parallel to the x/y/z axes.
        G4VSolid* innerSolid = new G4Box("innerSolid",lengthInner,lengthInner,fLength);
        G4VSolid* outerSolid = new G4Box("outerSolid",lengthOuter,lengthOuter,fLength);
        claddingSolid = new G4SubtractionSolid("claddingSolid",outerSolid,innerSolid);
        */
        //fLength is the radius of the Tube
        G4VSolid* innerSolid = new G4Tubs("innerSolidCurved",fLength-lengthInner,fLength+lengthInner,lengthInner,0,0.5*pi);
        G4VSolid* outerSolid = new G4Tubs("outerSolidCurved",fLength-lengthOuter,fLength+lengthOuter,lengthOuter,0,0.5*pi);
        claddingSolid = new G4SubtractionSolid("claddingSolid",outerSolid,innerSolid);

      }
      else if(fShape == "circle"){
        claddingSolid = new G4Tubs("claddingSolid",lengthInner,lengthOuter,fLength,0,2*pi);
        MGLog(fatal)<<"Curved fibers should not have circular cross sections "<<endlog;
      }
      else
        MGLog(error) << "Incorrect shape for fiber core : "<<fShape<<" not valid! \n use square or cirlce"<<endlog;

      pVol = new G4LogicalVolume(claddingSolid,G4Material::GetMaterial(this->GetMaterial()),logicalName); 
    }
    //Outer Cladding n = 1.42
    else if(this->GetMaterial() == "Fluor-acrylic"){
      G4double lengthInner = lengthTotal - outerThickness;
      G4double lengthOuter = lengthTotal;
      if(fShape == "square"){
        /*
        //A Box is a cuboid of given half lengths
        //centred on the origin with sides parallel to the x/y/z axes.
        G4VSolid* innerSolid = new G4Box("innerSolid",lengthInner,lengthInner,fLength);
        G4VSolid* outerSolid = new G4Box("outerSolid",lengthOuter,lengthOuter,fLength);
        claddingSolid = new G4SubtractionSolid("claddingSolid",outerSolid,innerSolid);
        */
        G4VSolid* innerSolid = new G4Tubs("innerSolidCurved",fLength-lengthInner,fLength+lengthInner,lengthInner,0,0.5*pi);
        G4VSolid* outerSolid = new G4Tubs("outerSolidCurved",fLength-lengthOuter,fLength+lengthOuter,lengthOuter,0,0.5*pi);
        claddingSolid = new G4SubtractionSolid("claddingSolid",outerSolid,innerSolid);
      }
      else if(fShape == "circle"){
        claddingSolid = new G4Tubs("claddingSolid",lengthInner,lengthOuter,fLength,0,2*pi);
        MGLog(fatal)<<"Curved fibers should not have circular cross sections "<<endlog;
      }
      else
        MGLog(error) << "Incorrect shape for fiber core : "<<fShape<<" not valid! \n use square or cirlce"<<endlog;

      pVol = new G4LogicalVolume(claddingSolid,G4Material::GetMaterial(this->GetMaterial()),logicalName); 
    }
  }


  return pVol;
}
