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
// CLASS IMPLEMENTATION:  LGND_200_DetUnitAssembly.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 *
 *Assembly origin:  Crystal Contact
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Matthew Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: Jul 22, 2010
 *
 * REVISION:
 *
 * 07-22-2017, Created, M. Green
 */
//---------------------------------------------------------------------------//
//

#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4AffineTransform.hh"
#include "G4UIcommand.hh"
//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "legendio/LGND_JSONReader.hh"
#include "legendgeometry/LGND_200_DetUnitAssembly.hh"
#include "legendgeometry/LGND_JSONDet.hh"
#include "legendgeometry/LGND_SiPlate.hh"
#include "legendgeometry/LGND_LMFE.hh"
#include "legendgeometry/LGND_CrystalInsulator.hh"
#include "legendgeometry/LGND_DUSupportRod.hh"

using namespace CLHEP;



//---------------------------------------------------------------------------//

LGND_200_DetUnitAssembly::LGND_200_DetUnitAssembly(G4String fName, G4String serialNumber, G4String configFile) :
  LGND_Assembly(fName, serialNumber, "LGND_200_DetUnitAssembly"), fPostRadius(46.5*mm), fDUheight(0.0)
{
  fConfigFile = configFile;
  LGND_JSONReader* reader = new LGND_JSONReader(fConfigFile);
  std::vector<G4String> detectorSerial = reader->ReadCrystalAssembly(serialNumber);
  delete reader;
  fDetectorPtr = new LGND_JSONDet(fName + "_ActiveDet_001", detectorSerial.at(0), fConfigFile);
  fCrystalDiameter = fDetectorPtr->GetDiameter();
  fCrystalHeight = fDetectorPtr->GetHeight();
  fSiPlatePtr = new LGND_SiPlate(fName + "_SiPlate_001", "867-5309");
  fLMFEPtr = new LGND_LMFE(fName + "_LMFE_001", "867-5309");
  fInsulator1Ptr = new LGND_CrystalInsulator(fName + "_CrystalInsulator_001", "867-5309");
  fInsulator2Ptr = new LGND_CrystalInsulator(fName + "_CrystalInsulator_002", "867-5309");
  fInsulator3Ptr = new LGND_CrystalInsulator(fName + "_CrystalInsulator_003", "867-5309");
  fDUheight = 95.0;
  //fDUheight = fCrystalHeight+15.0;
  fSupport1Ptr = new LGND_DUSupportRod(fName + "_SupportRod_001", "867-5309", fDUheight-0.01);
  fSupport2Ptr = new LGND_DUSupportRod(fName + "_SupportRod_002", "867-5309", fDUheight-0.01);
  fSupport3Ptr = new LGND_DUSupportRod(fName + "_SupportRod_003", "867-5309", fDUheight-0.01);
  //AllocateParts();
}

LGND_200_DetUnitAssembly::LGND_200_DetUnitAssembly(const LGND_200_DetUnitAssembly & rhs) :
  LGND_Assembly(rhs), fCrystalDiameter(rhs.fCrystalDiameter),
  fCrystalHeight(rhs.fCrystalHeight), fPostRadius(rhs.fPostRadius), fDUheight(rhs.fDUheight)
{
  //AllocateParts();
}

LGND_200_DetUnitAssembly::~LGND_200_DetUnitAssembly()
{
  UnallocateParts();
}

void LGND_200_DetUnitAssembly::AllocateParts()
{
}

void LGND_200_DetUnitAssembly::UnallocateParts()
{
  delete fDetectorPtr;
  fPartsList.resize(0);
  fAssembliesList.resize(0);
}

void LGND_200_DetUnitAssembly::Place(G4ThreeVector* assemPosition,
                G4RotationMatrix* assemRotation, G4LogicalVolume* motherLogical)
{
  G4AffineTransform *assemAffine = new G4AffineTransform(assemRotation,*assemPosition);

  //Place the crystal so that the point-contact is at the origin of the
  //coordinate system.
  G4ThreeVector *crystal1localPos = new G4ThreeVector(0, 0, -fCrystalHeight/2-0.025*mm);
  G4RotationMatrix *crystal1localRot;
  crystal1localRot = new G4RotationMatrix(0, pi, 0);
  G4AffineTransform *crystal1affine = new G4AffineTransform(crystal1localRot,*crystal1localPos);
  *crystal1affine *= *assemAffine;
  G4ThreeVector *crystal1globalPos = new G4ThreeVector(crystal1affine->NetTranslation());
  G4RotationMatrix *crystal1globalRot= new G4RotationMatrix(crystal1affine->NetRotation());
  fDetectorPtr->Place(crystal1globalPos, crystal1globalRot, motherLogical);
  delete crystal1localPos;
  delete crystal1localRot;
  delete crystal1affine;

  //Place the Si Plate
  G4ThreeVector *siPlatelocalPos = new G4ThreeVector(0, 0, 5.11*mm);
  G4RotationMatrix *siPlatelocalRot;
  siPlatelocalRot = new G4RotationMatrix();
  G4AffineTransform *siPlateaffine = new G4AffineTransform(siPlatelocalRot,*siPlatelocalPos);
  *siPlateaffine *= *assemAffine;
  G4ThreeVector *siPlateglobalPos = new G4ThreeVector(siPlateaffine->NetTranslation());
  G4RotationMatrix *siPlateglobalRot= new G4RotationMatrix(siPlateaffine->NetRotation());
  fSiPlatePtr->Place(siPlateglobalPos, siPlateglobalRot, motherLogical);
  delete siPlatelocalPos;
  delete siPlatelocalRot;
  delete siPlateaffine;

  //Place the LMFE
  G4ThreeVector *LMFElocalPos = new G4ThreeVector(5.0*mm, 0, 10.5*mm);
  G4RotationMatrix *LMFElocalRot;
  LMFElocalRot = new G4RotationMatrix();
  G4AffineTransform *LMFEaffine = new G4AffineTransform(LMFElocalRot,*LMFElocalPos);
  *LMFEaffine *= *assemAffine;
  //G4ThreeVector *LMFEglobalPos = new G4ThreeVector(LMFEaffine->NetTranslation());
  //G4RotationMatrix *LMFEglobalRot= new G4RotationMatrix(LMFEaffine->NetRotation());
  //fLMFEPtr->Place(LMFEglobalPos, LMFEglobalRot, motherLogical);
  delete LMFElocalPos;
  delete LMFElocalRot;
  delete LMFEaffine;


  //Place the Crystal Insulators
  G4ThreeVector *Insulator1localPos = new G4ThreeVector(fCrystalDiameter/2.0+0.1*mm, 0, -0.14*mm);
  G4RotationMatrix *Insulator1localRot;
  Insulator1localRot = new G4RotationMatrix();
  Insulator1localRot->rotateX(pi);
  G4AffineTransform *Insulator1affine = new G4AffineTransform(Insulator1localRot,*Insulator1localPos);
  *Insulator1affine *= *assemAffine;
  G4ThreeVector *Insulator1globalPos = new G4ThreeVector(Insulator1affine->NetTranslation());
  G4RotationMatrix *Insulator1globalRot= new G4RotationMatrix(Insulator1affine->NetRotation());
  fInsulator1Ptr->Place(Insulator1globalPos, Insulator1globalRot, motherLogical);
  delete Insulator1localPos;
  delete Insulator1localRot;
  delete Insulator1affine;

  G4ThreeVector *Insulator2localPos = new G4ThreeVector((fCrystalDiameter/2.0+0.1*mm)*cos(120*deg),
                                                (fCrystalDiameter/2.0+0.1*mm)*sin(120*deg), -0.14*mm);
  G4RotationMatrix *Insulator2localRot;
  Insulator2localRot = new G4RotationMatrix();
  Insulator2localRot->rotateZ(-120*deg);
  Insulator2localRot->rotateX(pi);
  G4AffineTransform *Insulator2affine = new G4AffineTransform(Insulator2localRot,*Insulator2localPos);
  *Insulator2affine *= *assemAffine;
  G4ThreeVector *Insulator2globalPos = new G4ThreeVector(Insulator2affine->NetTranslation());
  G4RotationMatrix *Insulator2globalRot= new G4RotationMatrix(Insulator2affine->NetRotation());
  fInsulator2Ptr->Place(Insulator2globalPos, Insulator2globalRot, motherLogical);
  delete Insulator2localPos;
  delete Insulator2localRot;
  delete Insulator2affine;

  G4ThreeVector *Insulator3localPos = new G4ThreeVector((fCrystalDiameter/2.0+0.1*mm)*cos(240*deg),
                                                (fCrystalDiameter/2.0+0.1*mm)*sin(240*deg), -0.14*mm);
  G4RotationMatrix *Insulator3localRot;
  Insulator3localRot = new G4RotationMatrix();
  Insulator3localRot->rotateZ(-240*deg);
  Insulator3localRot->rotateX(pi);
  G4AffineTransform *Insulator3affine = new G4AffineTransform(Insulator3localRot,*Insulator3localPos);
  *Insulator3affine *= *assemAffine;
  G4ThreeVector *Insulator3globalPos = new G4ThreeVector(Insulator3affine->NetTranslation());
  G4RotationMatrix *Insulator3globalRot= new G4RotationMatrix(Insulator3affine->NetRotation());
  fInsulator3Ptr->Place(Insulator3globalPos, Insulator3globalRot, motherLogical);
  delete Insulator3localPos;
  delete Insulator3localRot;
  delete Insulator3affine;

  G4ThreeVector *SupportRod1localPos = new G4ThreeVector(fPostRadius, 0, -(fDUheight-0.01)/2*mm+11.1*mm);
  G4RotationMatrix *SupportRod1localRot;
  SupportRod1localRot = new G4RotationMatrix();
  SupportRod1localRot->rotateX(pi);
  G4AffineTransform *SupportRod1affine = new G4AffineTransform(SupportRod1localRot,*SupportRod1localPos);
  *SupportRod1affine *= *assemAffine;
  G4ThreeVector *SupportRod1globalPos = new G4ThreeVector(SupportRod1affine->NetTranslation());
  G4RotationMatrix *SupportRod1globalRot= new G4RotationMatrix(SupportRod1affine->NetRotation());
  fSupport1Ptr->Place(SupportRod1globalPos, SupportRod1globalRot, motherLogical);
  delete SupportRod1localPos;
  delete SupportRod1localRot;
  delete SupportRod1affine;

  G4ThreeVector *SupportRod2localPos = new G4ThreeVector(fPostRadius*cos(120*deg), fPostRadius*sin(120*deg), -(fDUheight-0.01)/2*mm+11.1*mm);
  G4RotationMatrix *SupportRod2localRot;
  SupportRod2localRot = new G4RotationMatrix();
  SupportRod2localRot->rotateZ(-120*deg);
  SupportRod2localRot->rotateX(pi);
  G4AffineTransform *SupportRod2affine = new G4AffineTransform(SupportRod2localRot,*SupportRod2localPos);
  *SupportRod2affine *= *assemAffine;
  G4ThreeVector *SupportRod2globalPos = new G4ThreeVector(SupportRod2affine->NetTranslation());
  G4RotationMatrix *SupportRod2globalRot= new G4RotationMatrix(SupportRod2affine->NetRotation());
  fSupport2Ptr->Place(SupportRod2globalPos, SupportRod2globalRot, motherLogical);
  delete SupportRod2localPos;
  delete SupportRod2localRot;
  delete SupportRod2affine;

  G4ThreeVector *SupportRod3localPos = new G4ThreeVector(fPostRadius*cos(240*deg), fPostRadius*sin(240*deg), -(fDUheight-0.01)/2*mm+11.1*mm);
  G4RotationMatrix *SupportRod3localRot;
  SupportRod3localRot = new G4RotationMatrix();
  SupportRod3localRot->rotateZ(-240*deg);
  SupportRod3localRot->rotateX(pi);
  G4AffineTransform *SupportRod3affine = new G4AffineTransform(SupportRod3localRot,*SupportRod3localPos);
  *SupportRod3affine *= *assemAffine;
  G4ThreeVector *SupportRod3globalPos = new G4ThreeVector(SupportRod3affine->NetTranslation());
  G4RotationMatrix *SupportRod3globalRot= new G4RotationMatrix(SupportRod3affine->NetRotation());
  fSupport3Ptr->Place(SupportRod3globalPos, SupportRod3globalRot, motherLogical);
  delete SupportRod3localPos;
  delete SupportRod3localRot;
  delete SupportRod3affine;

}
