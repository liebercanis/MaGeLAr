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
// CLASS IMPLEMENTATION:  MJDemoTopIRShieldSupportFarEnd.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 * Part origin:  Box Center
 *
 */
// 
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Max Hays
 * CONTACT: maxhays8@gmail.com
 * FIRST SUBMISSION: June 5, 2014
 * 
 * REVISION:
 * 
 * 05-06-2010, Created, M. Hays
 */
//---------------------------------------------------------------------------//
//

#include "G4LogicalVolume.hh" 
#include "G4LogicalVolumeStore.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4GenericTrap.hh"
#include "G4UnionSolid.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"

//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "mjdemonstrator/MJDemoTopIRShieldSupportFarEnd.hh"
#include "mjdemonstrator/MJVDemoPart.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;


MJDemoTopIRShieldSupportFarEnd::MJDemoTopIRShieldSupportFarEnd(G4String partName, G4String serialNumber) :
  MJVDemoPart(partName, serialNumber, "MJ80-11-180", "Copper-EF")
{;}

MJDemoTopIRShieldSupportFarEnd::MJDemoTopIRShieldSupportFarEnd(const MJDemoTopIRShieldSupportFarEnd & rhs) : 
  MJVDemoPart(rhs)
{;}

MJDemoTopIRShieldSupportFarEnd::~MJDemoTopIRShieldSupportFarEnd()
{;}

G4LogicalVolume* MJDemoTopIRShieldSupportFarEnd::ConstructPart()
{
  G4LogicalVolumeStore *storePtr = G4LogicalVolumeStore::GetInstance();
  G4String logicalName = fDrawingNumber + "_" + fPartMaterial;
  
  G4LogicalVolume* pVol = storePtr->GetVolume(logicalName, false);
  if (pVol == NULL){
    G4double epsilon = 0.01*mm;

    G4Box* mainRecPrism = new G4Box("Main Rec Prism", 28.575/2*mm, 11.43/2*mm, 121.313/2*mm);
    G4Box* sideSubRecPrism1 = new G4Box("Sub Rec Prism 1", 9.525/2*mm+epsilon, 11.43/2*mm+epsilon, (104.775/2)*mm);
    G4Box* sideSubRecPrism2 = new G4Box("Sub Rec Prism 2", 6.35/4*mm+epsilon, 11.43/2*mm+epsilon, (104.775/2-6.35/4)*mm);
    G4Box* sideSubRecPrism3 = new G4Box("Sub Rec Prism 3", 6.35/4*mm+epsilon, 11.43/2*mm+epsilon, 73.025/2*mm);
    G4Box* sideSubRecPrism4 = new G4Box("Sub Rec Prism 4", 6.35/4*mm+epsilon, 11.43/2*mm+epsilon, (73.025-6.35/2)/2*mm);
    G4Box* sideSubRecPrism5 = new G4Box("Sub Rec Prism 5", 9.525/2*mm+epsilon, 11.43/2*mm+epsilon, (2.337/2)*mm+epsilon);
    G4Box* sideSubRecPrism6 = new G4Box("Sub Rec Prism 6", 70*mm, 11.43/2*mm+epsilon, 10*mm);
    G4Box* sideSubRecPrism7 = new G4Box("Sub Rec Prism 7", 7*mm, 2*mm, 12.7/2*mm);
    G4Tubs* sideSubCyl = new G4Tubs("Subtracted Cylinder from Side", 0.0*mm, 6.35/2*mm, 11.43/2*mm + epsilon, 0, 2*M_PI);
    G4Tubs* screwSubCyl1 = new G4Tubs("Cylindrical Hole", 0.0*mm, 1.825*mm, 12.7/2*mm + epsilon, 0, 2*M_PI); //1.727
    G4Tubs* screwSubCyl2 = new G4Tubs("Cylindrical Hole", 0.0*mm, 2.35*mm, 12.7/2*mm + epsilon, 0, 2*M_PI); //2.248

    G4RotationMatrix* rotX = new G4RotationMatrix;
    G4RotationMatrix* rotY = new G4RotationMatrix;
    G4RotationMatrix* rotZ = new G4RotationMatrix;
    G4RotationMatrix* rotZ2 = new G4RotationMatrix;
    G4RotationMatrix* rotN = new G4RotationMatrix;
    rotX->rotateX(M_PI/2.*rad);
    rotY->rotateY(5.326*M_PI/180*rad);
    rotZ->rotateZ(M_PI/4.*rad);
    rotZ2->rotateZ(-M_PI/4.*rad);
    G4SubtractionSolid* subSolid;

    subSolid = new G4SubtractionSolid("Sub Solid", mainRecPrism, sideSubRecPrism1, rotN, G4ThreeVector((28.575-9.525)/2*mm, 0, (121.313/2-10.188-104.775/2)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubRecPrism2, rotN, G4ThreeVector((28.575/2-12.7+6.35/4)*mm, 0, (121.313/2-10.188-104.775/2+6.35/4)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubRecPrism3, rotN, G4ThreeVector(-(28.575/2 - 12.7 - 6.35/4)*mm, 0, (121.313/2-10.188-73.025/2)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubRecPrism4, rotN, G4ThreeVector((28.575/2 - 19.05+6.35/4)*mm, 0, (121.313/2-10.188-73.025/2-6.35/4)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubRecPrism5, rotN, G4ThreeVector((28.575-9.525)/2*mm, 0, -(121.313/2-2.337/2)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubRecPrism6, rotY, G4ThreeVector((28.575)/2*mm, 0, (121.313/2+10)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubRecPrism7, rotZ, G4ThreeVector(-(28.575/2-6.35)*mm, (11.43/2+2*sqrt(2))*mm, (121.313/2-83.213+12.7/2)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubRecPrism7, rotZ2, G4ThreeVector(-(28.575/2-6.35)*mm, -(11.43/2+2*sqrt(2))*mm, (121.313/2-83.213+12.7/2)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubCyl, rotX, G4ThreeVector(-(28.575/2 - 19.05)*mm, 0, -(121.313/2-9.525)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubCyl, rotX, G4ThreeVector((28.575/2 - 15.875)*mm, 0, (121.313/2-13.363)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, sideSubCyl, rotX, G4ThreeVector((28.575/2 - 9.638)*mm, 0, -(121.313/2+0.838)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, screwSubCyl1, rotN, G4ThreeVector((28.575/2 - 5.058)*mm, 0, (121.313/2)*mm));
    subSolid = new G4SubtractionSolid("Sub Solid", subSolid, screwSubCyl2, rotN, G4ThreeVector((28.575/2 - 3.175)*mm, 0, -(121.313/2)*mm));  

    G4VisAttributes* copperVisAtt = new G4VisAttributes(G4Colour(0.839,0.373,0.169,1.0));
    copperVisAtt->SetForceWireframe( false );
    G4Material *material = G4Material::GetMaterial(this->GetMaterial());
    pVol = new G4LogicalVolume(subSolid, material, logicalName);
    pVol->SetVisAttributes(copperVisAtt);
    MGLog(debugging) << "Created Top IR Shield Support Far End Logical" << endlog;
  }
  else  MGLog(debugging) << "Using pre-existing Top IR Shield Support Far End Logical" << endlog; 
  return pVol;
}  
