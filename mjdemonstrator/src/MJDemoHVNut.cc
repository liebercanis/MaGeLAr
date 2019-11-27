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
// CLASS IMPLEMENTATION:  MJDemoHVNut.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 * 
 *Part Origin: Coaxial with threaded hole, coincident with mating shoulder.
 */
// 
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Matthew Green
 * CONTACT: mpgreen@physics.unc.edu
 * FIRST SUBMISSION: Jul 22, 2010
 * 
 * REVISION:
 * 
 * 07-22-2010, Created, M. Green
 */
//---------------------------------------------------------------------------//
//

#include "G4LogicalVolume.hh"	
#include "G4LogicalVolumeStore.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"

//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "mjdemonstrator/MJDemoHVNut.hh"
#include "mjdemonstrator/MJVDemoPart.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;


MJDemoHVNut::MJDemoHVNut(G4String partName, G4String serialNumber) :
  MJVDemoPart(partName, serialNumber, "MJ80-02-001", "Teflon")
{;}

MJDemoHVNut::MJDemoHVNut(const MJDemoHVNut & rhs) : 
  MJVDemoPart(rhs)
{;}

MJDemoHVNut::~MJDemoHVNut()
{;}

G4LogicalVolume* MJDemoHVNut::ConstructPart()
{
  G4LogicalVolumeStore *storePtr = G4LogicalVolumeStore::GetInstance();
  G4String logicalName = fDrawingNumber + "_" + fPartMaterial;
  
  G4LogicalVolume* pVol = storePtr->GetVolume(logicalName, false);
  if (pVol == NULL){
    G4double zPlanes[] = {-0.05*25.4*mm, -0.315*25.4*mm};
    G4double rInner[] = {0, 0};
    G4double rOuter[] = {0.156*25.4*mm, 0.156*25.4*mm};
    G4Polyhedra* hex = new G4Polyhedra("Hex", 0, 2*pi, 6, 2, zPlanes, rInner, rOuter);
    
    G4double zConePlanes[] = {-0.1*25.4*mm, 0*25.4*mm, 0*25.4*mm, 0.257*25.4*mm};
    G4double rConeInner[] = {0, 0, 0, 0};
    G4double rConeOuter[] = {0.18*25.4*mm, 0.18*25.4*mm, 0.1375*25.4*mm, 0.1375*25.4*mm};
    G4Polycone* barrel = new G4Polycone("Barrel", 0, 2*pi, 4, zConePlanes, rConeInner, rConeOuter);

    G4UnionSolid* hexBarrel = new G4UnionSolid("hexBarrel", hex, barrel, 0, G4ThreeVector(0,0,0));

    G4Tubs* threadHole = new G4Tubs("threadHole", 0, 0.1141*25.4*mm, 0.35*25.4*mm, 0, 2*pi);       

    G4SubtractionSolid* HVNut = new G4SubtractionSolid("HV Nut", hexBarrel, threadHole);   
                                                                   
    G4VisAttributes* grayVisAtt = new G4VisAttributes(G4Colour(0.7,0.7,0.7)); // gray
    grayVisAtt->SetForceWireframe( false );
    G4Material *material = G4Material::GetMaterial(this->GetMaterial());
    pVol = new G4LogicalVolume(HVNut, material, logicalName);
    pVol->SetVisAttributes(grayVisAtt); 
    MGLog(debugging) << "Created HV Nut Logical" << endlog;
  }
  else  MGLog(debugging) << "Using pre-existing HV Nut Logical" << endlog; 
  return pVol;
}  
