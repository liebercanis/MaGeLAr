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
// CLASS IMPLEMENTATION:  LGND_200_StringAssembly.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 *
 *Assembly origin:  Coaxial with string, coincident with top face of string
 *adapter plate.
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Matthew Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: Jul 22, 2017
 *
 * REVISION:
 *
 * 07-22-2017, Created, M. Green
 *
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
#include "legendgeometry/LGND_200_StringAssembly.hh"
#include "legendgeometry/LGND_200_DetUnitAssembly.hh"
#include "legendgeometry/LGND_HVSigCable.hh"
#include "legendgeometry/LGND_MiniShroud.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;


LGND_200_StringAssembly::LGND_200_StringAssembly(G4String fName, G4String serialNumber, G4bool SiPMArrayFlag, G4String configFile) :
  LGND_Assembly(fName, serialNumber, "StringAssemDwg"),fSiPMArrayFlag(SiPMArrayFlag)
{
  fCrystalNum = 15;
  LGND_200_DetUnitAssembly** temp = new LGND_200_DetUnitAssembly*[fCrystalNum];
  LGND_HVSigCable** temp2 = new LGND_HVSigCable*[fCrystalNum];
  fConfigFile = configFile;
  fDetUnitPtr = temp;
  fCablePtr = temp2;
  fStringLength = 0.0;
}

LGND_200_StringAssembly::~LGND_200_StringAssembly()
{
  delete[] fDetUnitPtr;
  delete fMiniShroudPtr;
  //delete fMiniShroudOuterTPBptr;
  //delete fMiniShroudInnerTPBptr;
}

void LGND_200_StringAssembly::SetNumberOfCrystals(size_t crystalNum)
{
  fCrystalNum = crystalNum;
}

void LGND_200_StringAssembly::Place(G4ThreeVector* assemPosition,
                G4RotationMatrix* assemRotation, G4LogicalVolume* motherLogical)
{
  G4AffineTransform *assemAffine = new G4AffineTransform(assemRotation,*assemPosition);

  LGND_JSONReader* reader = new LGND_JSONReader(fConfigFile);
  std::vector<G4String> crysAssemList = reader->ReadCrystalAssemblyList(fSerialNumber);
  delete reader;

  fCrystalNum = crysAssemList.size();

  G4double* crystalZ = new G4double[fCrystalNum];
  G4ThreeVector *DetUnitLocalPos;
  G4RotationMatrix *DetUnitLocalRot;
  G4AffineTransform *DetUnitAffine;
  G4ThreeVector *DetUnitGlobalPos;
  G4RotationMatrix *DetUnitGlobalRot;

  G4ThreeVector *CableLocalPos;
  G4RotationMatrix *CableLocalRot;
  G4AffineTransform *CableAffine;
  G4ThreeVector *CableGlobalPos;
  G4RotationMatrix *CableGlobalRot;

  for(size_t i = 0; i<fCrystalNum; i++){
    G4String DetUnitAssemblyName = fName + "_DetUnit_";
    if (i+1 < 100) DetUnitAssemblyName += "0";
    if (i+1 < 10) DetUnitAssemblyName += "0";
    DetUnitAssemblyName += G4UIcommand::ConvertToString((G4int)i+1);

    fDetUnitPtr[i] = new LGND_200_DetUnitAssembly(DetUnitAssemblyName, crysAssemList.at(i), fConfigFile);
    if (i == 0){
      crystalZ[i] = 11.1*mm-fDetUnitPtr[i]->GetDUheight();
    }
    else {
      crystalZ[i] = crystalZ[i-1] - fDetUnitPtr[i]->GetDUheight();
    }
    //fDetUnitPtr[i]->ConstructParts();
    DetUnitLocalPos = new G4ThreeVector(0, 0, crystalZ[i]);
    DetUnitLocalRot = new G4RotationMatrix();
    DetUnitLocalRot->rotateX(pi);
    DetUnitAffine = new G4AffineTransform(DetUnitLocalRot,*DetUnitLocalPos);
    *DetUnitAffine *= *assemAffine;
    DetUnitGlobalPos = new G4ThreeVector(DetUnitAffine->NetTranslation());
    DetUnitGlobalRot= new G4RotationMatrix(DetUnitAffine->NetRotation());
    fDetUnitPtr[i]->Place(DetUnitGlobalPos, DetUnitGlobalRot, motherLogical);

    delete DetUnitLocalPos;
    delete DetUnitLocalRot;
    delete DetUnitAffine;

    //fStringLength = -crystalZ[i]+fDetUnitPtr[i]->GetDUheight()-crystalZ[0];
    fStringLength += fDetUnitPtr[i]->GetDUheight();


    G4String CableAssemblyName = fName + "_HVSigCable_";
    if (i+1 < 100) CableAssemblyName += "0";
    if (i+1 < 10) CableAssemblyName += "0";
    CableAssemblyName += G4UIcommand::ConvertToString((G4int)i+1);

    fCablePtr[i] = new LGND_HVSigCable(CableAssemblyName, "CABLESN", fStringLength);
    CableLocalPos = new G4ThreeVector(-45.0*mm, (i*15.0/fCrystalNum-7.5)*mm, 0);
    CableLocalRot = new G4RotationMatrix();
    CableAffine = new G4AffineTransform(CableLocalRot,*CableLocalPos);
    *CableAffine *= *assemAffine;
    CableGlobalPos = new G4ThreeVector(CableAffine->NetTranslation());
    CableGlobalRot= new G4RotationMatrix(CableAffine->NetRotation());
    fCablePtr[i]->Place(CableGlobalPos, CableGlobalRot, motherLogical);

    delete CableLocalPos;
    delete CableLocalRot;
    delete CableAffine;
  }

  fMiniShroudPtr = new LGND_MiniShroud(fName + "_MiniShroudNylon_001", "867-5309", fStringLength+10.0*mm,"TPBOnNylon");
  //fMiniShroudInnerTPBptr = new LGND_MiniShroud(fName + "_MiniShroudTPBInner_001", "00011-0004", fStringLength+10.0*mm,"TPBNylon");
  //fMiniShroudOuterTPBptr = new LGND_MiniShroud(fName + "_MiniShroudTPBOuter_001", "00011-0003", fStringLength+10.0*mm,"TPBNylon");

  G4ThreeVector *miniShroudlocalPos =
             new G4ThreeVector(0, 0, -fStringLength/2.0*mm );
  G4RotationMatrix *miniShroudlocalRot = new G4RotationMatrix();
  G4AffineTransform *miniShroudaffine = new G4AffineTransform(miniShroudlocalRot,
                 *miniShroudlocalPos);
  *miniShroudaffine*=*assemAffine;
  G4ThreeVector *miniShroudglobalPos = new G4ThreeVector(
                  miniShroudaffine->NetTranslation());
  G4RotationMatrix *miniShroudglobalRot= new G4RotationMatrix(
                 miniShroudaffine->NetRotation());

  if(fSiPMArrayFlag) fMiniShroudPtr->Place(miniShroudglobalPos, miniShroudglobalRot, motherLogical);
  //fMiniShroudInnerTPBptr->Place(miniShroudglobalPos, miniShroudglobalRot, motherLogical);
  //fMiniShroudOuterTPBptr->Place(miniShroudglobalPos, miniShroudglobalRot, motherLogical);

  //fMiniShroudOuterTPBptr->GetPhysicalVolume()->CheckOverlaps(1000, 0, true);
  //fMiniShroudInnerTPBptr->GetPhysicalVolume()->CheckOverlaps(1000, 0, true);
  delete miniShroudlocalPos;
  delete miniShroudlocalRot;
  delete miniShroudaffine;
}
