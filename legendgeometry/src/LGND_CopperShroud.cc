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
// CLASS IMPLEMENTATION:  LGND_CoppperShroud.cc
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
 * 8-06-2018, Created, N. McFadden
 */
//---------------------------------------------------------------------------//
//

#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4UIcommand.hh"

//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "legendgeometry/LGND_CopperShroud.hh"
#include "legendgeometry/LGND_Part.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;


LGND_CopperShroud::LGND_CopperShroud(G4String partName, G4String serialNumber, G4double length, G4double outerRadius, G4String material) :
  LGND_Part(partName, serialNumber, "LGND_CopperShroud", material),
  fLength(length*mm),
  fOuterRadius(outerRadius*mm)
{;}

LGND_CopperShroud::LGND_CopperShroud(const LGND_CopperShroud & rhs) :
  LGND_Part(rhs)
{;}

LGND_CopperShroud::~LGND_CopperShroud()
{;}

G4LogicalVolume* LGND_CopperShroud::BuildLogicalVolume()
{
  G4LogicalVolumeStore *storePtr = G4LogicalVolumeStore::GetInstance();
  G4String logicalName = fDrawingNumber + "_" + fPartMaterial+"x"+G4UIcommand::ConvertToString(fLength);
  G4LogicalVolume* pVol = storePtr->GetVolume(logicalName, false);
  
  G4double TPBthickness = 600.*nm;//5*um;
  G4double VM2000thickness = 1*mm;
  //Default value for radon shield
  //G4double shroudOuterRadius = 500.0*mm;
  //max value for radon shield
  //G4double shroudOuterRadius = 700.0*mm;
  //Lower Radius
  //G4double shroudOuterRadius = 375.0*mm;
  G4double shroudOuterRadius = fOuterRadius;
  G4double shroudThickness = 2*mm;

  const int N = 4;
 if (pVol == NULL && this->GetMaterial() == "TPBOnTetratex"){
    
    G4double r = shroudOuterRadius - shroudThickness - VM2000thickness;
    G4double R = shroudOuterRadius - shroudThickness;
    G4double z0 = -(fLength-shroudThickness);
    G4double z1 = -(fLength-shroudThickness-VM2000thickness);
    G4double z2 = fLength;
    G4double Z[N] =    {z0,z1,z1,z2};
    G4double Rmin[N] = {0, 0, r, r};
    G4double Rmax[N] = {R, R, R, R};
    G4Polycone * vm2000Shroud = new G4Polycone("",0,2*pi,N,Z,Rmin,Rmax);

    G4Material *material = G4Material::GetMaterial(this->GetMaterial());
    pVol = new G4LogicalVolume(vm2000Shroud,material,logicalName);
    G4VisAttributes* greyVisAtt = new G4VisAttributes(G4Colour(1.0,1,0,0.3)); // yellow color
    pVol->SetVisAttributes(greyVisAtt);
  }
  else if (pVol == NULL && this->GetMaterial() == "Copper-EF"){
    
    G4double r = shroudOuterRadius - shroudThickness;
    G4double R = shroudOuterRadius;
    G4double z0 = -(fLength);
    G4double z1 = -(fLength-shroudThickness);
    G4double z2 = fLength;
    G4double Z[N] =    {z0,z1,z1,z2};
    G4double Rmin[N] = {0, 0, r, r};
    G4double Rmax[N] = {R, R, R, R};
    G4Polycone * coppershroud = new G4Polycone("",0,2*pi,N,Z,Rmin,Rmax);
    
    G4Material *material = G4Material::GetMaterial(this->GetMaterial());
    pVol = new G4LogicalVolume(coppershroud,material,logicalName);
    G4VisAttributes* greyVisAtt = new G4VisAttributes(G4Colour(0.5,5,5,0.3)); // New copper color
    pVol->SetVisAttributes(greyVisAtt);
  }
  else
    MGLog(error)<<"unknow material: "<<this->GetMaterial()<<" for CopperShroud construction"<<endlog;
  
  return pVol;
}
