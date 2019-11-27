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
// CLASS IMPLEMENTATION:  LGND_200_14StringArrayAssembly.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 *
 *Assembly origin:
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Matthew Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: Aug 8, 2017
 *
 * REVISION:
 * added a flag to toggle between SiPM array and fiber
 * nylon shroud
 * 08-08-2017, Created, M. Green
 */
//---------------------------------------------------------------------------//
//
#include <math.h>
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4AffineTransform.hh"

//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "legendio/LGND_JSONReader.hh"
#include "legendgeometry/LGND_200_14StringArrayAssembly.hh"
#include "legendgeometry/LGND_200_StringAssembly.hh"

using namespace CLHEP;

//---------------------------------------------------------------------------//

LGND_200_14StringArrayAssembly::LGND_200_14StringArrayAssembly(G4String fName, G4String serialNumber, G4bool SiPMArrayFlag) :
  LGND_Assembly(fName, serialNumber, "LGND_200_Strings"),fSiPMArrayFlag(SiPMArrayFlag)
{
  fConfigFile = "LGND_200_14String.json";
  LGND_JSONReader* reader = new LGND_JSONReader(fConfigFile);
  std::vector<G4String> stringList;
  stringList = reader->ReadAssemblyStringList(serialNumber);
  delete reader;

  fNumStrings = stringList.size();
  cout << "14StringArrayAssem fNumStrings: " << fNumStrings << endl;
  for(size_t i = fNumStrings; i < 14; i++)
    stringList.push_back("867-5309"); //Don't want the next few lines to throw an error
  if(fNumStrings == 0)
    fNumStrings = 14;

  if(stringList.at(0) == "NULL")
    fString1Ptr = NULL;
  else
    fString1Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_001", stringList.at(0),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(1) == "NULL")
    fString2Ptr = NULL;
  else
    fString2Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_002", stringList.at(1),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(2) == "NULL")
    fString3Ptr = NULL;
  else
    fString3Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_003", stringList.at(2),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(3) == "NULL")
    fString4Ptr = NULL;
  else
    fString4Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_004", stringList.at(3),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(4) == "NULL")
    fString5Ptr = NULL;
  else
    fString5Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_005", stringList.at(4),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(5) == "NULL")
    fString6Ptr = NULL;
  else
    fString6Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_006", stringList.at(5),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(6) == "NULL")
    fString7Ptr = NULL;
  else
    fString7Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_007", stringList.at(6),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(7) == "NULL")
    fString8Ptr = NULL;
  else
    fString8Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_008", stringList.at(7),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(8) == "NULL")
      fString9Ptr = NULL;
  else
      fString9Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_009", stringList.at(8),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(9) == "NULL")
      fString10Ptr = NULL;
  else
      fString10Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_010", stringList.at(9),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(10) == "NULL")
      fString11Ptr = NULL;
  else
      fString11Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_011", stringList.at(10),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(11) == "NULL")
      fString12Ptr = NULL;
  else
      fString12Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_012", stringList.at(11),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(12) == "NULL")
      fString13Ptr = NULL;
  else
      fString13Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_013", stringList.at(12),fSiPMArrayFlag,fConfigFile);

  if(stringList.at(13) == "NULL")
      fString14Ptr = NULL;
  else
      fString14Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_014", stringList.at(13),fSiPMArrayFlag,fConfigFile);


}

LGND_200_14StringArrayAssembly::LGND_200_14StringArrayAssembly(const LGND_200_14StringArrayAssembly & rhs) :
  LGND_Assembly(rhs)
{
  fString1Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_001", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString2Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_002", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString3Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_003", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString4Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_004", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString5Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_005", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString6Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_006", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString7Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_007", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString8Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_008", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString9Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_009", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString10Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_010", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString11Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_011", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString12Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_012", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString13Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_013", "867-5309",fSiPMArrayFlag,fConfigFile);
  fString14Ptr = new LGND_200_StringAssembly(fName+"_StringAssembly_014", "867-5309",fSiPMArrayFlag,fConfigFile);
}

LGND_200_14StringArrayAssembly::~LGND_200_14StringArrayAssembly()
{
  delete fString1Ptr;
  delete fString2Ptr;
  delete fString3Ptr;
  delete fString4Ptr;
  delete fString5Ptr;
  delete fString6Ptr;
  delete fString7Ptr;
  delete fString8Ptr;
  delete fString9Ptr;
  delete fString10Ptr;
  delete fString11Ptr;
  delete fString12Ptr;
  delete fString13Ptr;
  delete fString14Ptr;
}

void LGND_200_14StringArrayAssembly::Place(G4ThreeVector* assemPosition,
                G4RotationMatrix* assemRotation, G4LogicalVolume* motherLogical)
{
  G4AffineTransform *assemAffine = new G4AffineTransform(assemRotation,*assemPosition);

  G4double stringRadius = 235.0*mm;

  if(fString1Ptr != NULL)
  {
    G4ThreeVector *StringAssembly1localPos = new G4ThreeVector(stringRadius*cos(0*360.0/14.0*deg), stringRadius*sin(0*360.0/14.0*deg), 0);//0
    G4RotationMatrix *StringAssembly1localRot = new G4RotationMatrix();
    StringAssembly1localRot->rotateZ(-0*360.0/14.0*deg);
    G4AffineTransform *StringAssembly1affine = new G4AffineTransform(StringAssembly1localRot,*StringAssembly1localPos);
    *StringAssembly1affine*=*assemAffine;
    G4ThreeVector *StringAssembly1globalPos = new G4ThreeVector(StringAssembly1affine->NetTranslation());
    G4RotationMatrix *StringAssembly1globalRot= new G4RotationMatrix(StringAssembly1affine->NetRotation());
    fString1Ptr->Place(StringAssembly1globalPos, StringAssembly1globalRot, motherLogical);
    delete StringAssembly1localPos;
    delete StringAssembly1localRot;
    delete StringAssembly1affine;
  }

  if(fString2Ptr != NULL)
  {
    G4ThreeVector *StringAssembly2localPos;
    G4RotationMatrix *StringAssembly2localRot = new G4RotationMatrix();
    StringAssembly2localRot->rotateZ(-1*360.0/14.0*deg);
	  StringAssembly2localPos = new G4ThreeVector(stringRadius*cos(1*360.0/14.0*deg), stringRadius*sin(1*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly2affine = new G4AffineTransform(StringAssembly2localRot,*StringAssembly2localPos);
    *StringAssembly2affine*=*assemAffine;
    G4ThreeVector *StringAssembly2globalPos = new G4ThreeVector(StringAssembly2affine->NetTranslation());
    G4RotationMatrix *StringAssembly2globalRot= new G4RotationMatrix(StringAssembly2affine->NetRotation());
    fString2Ptr->Place(StringAssembly2globalPos, StringAssembly2globalRot, motherLogical);
    delete StringAssembly2localPos;
    delete StringAssembly2localRot;
    delete StringAssembly2affine;
  }

  if(fString3Ptr != NULL)
  {
    G4ThreeVector *StringAssembly3localPos;
    G4RotationMatrix *StringAssembly3localRot = new G4RotationMatrix();
    StringAssembly3localRot->rotateZ(-2*360.0/14.0*deg);
	  StringAssembly3localPos = new G4ThreeVector(stringRadius*cos(2*360.0/14.0*deg), stringRadius*sin(2*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly3affine = new G4AffineTransform(StringAssembly3localRot,*StringAssembly3localPos);
    *StringAssembly3affine*=*assemAffine;
    G4ThreeVector *StringAssembly3globalPos = new G4ThreeVector(StringAssembly3affine->NetTranslation());
    G4RotationMatrix *StringAssembly3globalRot= new G4RotationMatrix(StringAssembly3affine->NetRotation());
    fString3Ptr->Place(StringAssembly3globalPos, StringAssembly3globalRot, motherLogical);
    delete StringAssembly3localPos;
    delete StringAssembly3localRot;
    delete StringAssembly3affine;
  }

  if(fString4Ptr != NULL)
  {
    G4ThreeVector *StringAssembly4localPos;
    G4RotationMatrix *StringAssembly4localRot = new G4RotationMatrix();
    StringAssembly4localRot->rotateZ(-3*360.0/14.0*deg);
    StringAssembly4localPos = new G4ThreeVector(stringRadius*cos(3*360.0/14.0*deg), stringRadius*sin(3*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly4affine = new G4AffineTransform(StringAssembly4localRot,*StringAssembly4localPos);
    *StringAssembly4affine*=*assemAffine;
    G4ThreeVector *StringAssembly4globalPos = new G4ThreeVector(StringAssembly4affine->NetTranslation());
    G4RotationMatrix *StringAssembly4globalRot= new G4RotationMatrix(StringAssembly4affine->NetRotation());
    fString4Ptr->Place(StringAssembly4globalPos, StringAssembly4globalRot, motherLogical);
    delete StringAssembly4localPos;
    delete StringAssembly4localRot;
    delete StringAssembly4affine;
  }

  if(fString5Ptr != NULL)
  {
    G4ThreeVector *StringAssembly5localPos;
    G4RotationMatrix *StringAssembly5localRot = new G4RotationMatrix();
    StringAssembly5localRot->rotateZ(-4*360.0/14.0*deg);
    StringAssembly5localPos = new G4ThreeVector(stringRadius*cos(4*360.0/14.0*deg), stringRadius*sin(4*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly5affine = new G4AffineTransform(StringAssembly5localRot,*StringAssembly5localPos);
    *StringAssembly5affine*=*assemAffine;
    G4ThreeVector *StringAssembly5globalPos = new G4ThreeVector(StringAssembly5affine->NetTranslation());
    G4RotationMatrix *StringAssembly5globalRot= new G4RotationMatrix(StringAssembly5affine->NetRotation());
    fString5Ptr->Place(StringAssembly5globalPos, StringAssembly5globalRot, motherLogical);
    delete StringAssembly5localPos;
    delete StringAssembly5localRot;
    delete StringAssembly5affine;
  }

  if(fString6Ptr != NULL)
  {
    G4ThreeVector *StringAssembly6localPos;
    G4RotationMatrix *StringAssembly6localRot = new G4RotationMatrix();
    StringAssembly6localRot->rotateZ(-5*360.0/14.0*deg);
    StringAssembly6localPos = new G4ThreeVector(stringRadius*cos(5*360.0/14.0*deg), stringRadius*sin(5*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly6affine = new G4AffineTransform(StringAssembly6localRot,*StringAssembly6localPos);
    *StringAssembly6affine*=*assemAffine;
    G4ThreeVector *StringAssembly6globalPos = new G4ThreeVector(StringAssembly6affine->NetTranslation());
    G4RotationMatrix *StringAssembly6globalRot= new G4RotationMatrix(StringAssembly6affine->NetRotation());
    fString6Ptr->Place(StringAssembly6globalPos, StringAssembly6globalRot, motherLogical);
    delete StringAssembly6localPos;
    delete StringAssembly6localRot;
    delete StringAssembly6affine;
  }

  if(fString7Ptr != NULL)
  {
    G4ThreeVector *StringAssembly7localPos;
    G4RotationMatrix *StringAssembly7localRot = new G4RotationMatrix();
    StringAssembly7localRot->rotateZ(-6*360.0/14.0*deg);
    StringAssembly7localPos = new G4ThreeVector(stringRadius*cos(6*360.0/14.0*deg), stringRadius*sin(6*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly7affine = new G4AffineTransform(StringAssembly7localRot,*StringAssembly7localPos);
    *StringAssembly7affine*=*assemAffine;
    G4ThreeVector *StringAssembly7globalPos = new G4ThreeVector(StringAssembly7affine->NetTranslation());
    G4RotationMatrix *StringAssembly7globalRot= new G4RotationMatrix(StringAssembly7affine->NetRotation());
    fString7Ptr->Place(StringAssembly7globalPos, StringAssembly7globalRot, motherLogical);
    delete StringAssembly7localPos;
    delete StringAssembly7localRot;
    delete StringAssembly7affine;
  }

  if(fString8Ptr != NULL)
  {
    G4ThreeVector *StringAssembly8localPos;
    G4RotationMatrix *StringAssembly8localRot = new G4RotationMatrix();
    StringAssembly8localRot->rotateZ(-7*360.0/14.0*deg);
    StringAssembly8localPos = new G4ThreeVector(stringRadius*cos(7*360.0/14.0*deg), stringRadius*sin(7*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly8affine = new G4AffineTransform(StringAssembly8localRot,*StringAssembly8localPos);
    *StringAssembly8affine*=*assemAffine;
    G4ThreeVector *StringAssembly8globalPos = new G4ThreeVector(StringAssembly8affine->NetTranslation());
    G4RotationMatrix *StringAssembly8globalRot= new G4RotationMatrix(StringAssembly8affine->NetRotation());
    fString8Ptr->Place(StringAssembly8globalPos, StringAssembly8globalRot, motherLogical);
    delete StringAssembly8localPos;
    delete StringAssembly8localRot;
    delete StringAssembly8affine;
  }

  if(fString9Ptr != NULL)
  {
    G4ThreeVector *StringAssembly9localPos;
    G4RotationMatrix *StringAssembly9localRot = new G4RotationMatrix();
    StringAssembly9localRot->rotateZ(-8*360.0/14.0*deg);
    StringAssembly9localPos = new G4ThreeVector(stringRadius*cos(8*360.0/14.0*deg), stringRadius*sin(8*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly9affine = new G4AffineTransform(StringAssembly9localRot,*StringAssembly9localPos);
    *StringAssembly9affine*=*assemAffine;
    G4ThreeVector *StringAssembly9globalPos = new G4ThreeVector(StringAssembly9affine->NetTranslation());
    G4RotationMatrix *StringAssembly9globalRot= new G4RotationMatrix(StringAssembly9affine->NetRotation());
    fString9Ptr->Place(StringAssembly9globalPos, StringAssembly9globalRot, motherLogical);
    delete StringAssembly9localPos;
    delete StringAssembly9localRot;
    delete StringAssembly9affine;
  }

  if(fString10Ptr != NULL)
  {
    G4ThreeVector *StringAssembly10localPos;
    G4RotationMatrix *StringAssembly10localRot = new G4RotationMatrix();
    StringAssembly10localRot->rotateZ(-9*360.0/14.0*deg);
    StringAssembly10localPos = new G4ThreeVector(stringRadius*cos(9*360.0/14.0*deg), stringRadius*sin(9*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly10affine = new G4AffineTransform(StringAssembly10localRot,*StringAssembly10localPos);
    *StringAssembly10affine*=*assemAffine;
    G4ThreeVector *StringAssembly10globalPos = new G4ThreeVector(StringAssembly10affine->NetTranslation());
    G4RotationMatrix *StringAssembly10globalRot= new G4RotationMatrix(StringAssembly10affine->NetRotation());
    fString10Ptr->Place(StringAssembly10globalPos, StringAssembly10globalRot, motherLogical);
    delete StringAssembly10localPos;
    delete StringAssembly10localRot;
    delete StringAssembly10affine;
  }

  if(fString11Ptr != NULL)
  {
    G4ThreeVector *StringAssembly11localPos;
    G4RotationMatrix *StringAssembly11localRot = new G4RotationMatrix();
    StringAssembly11localRot->rotateZ(-10*360.0/14.0*deg);
    StringAssembly11localPos = new G4ThreeVector(stringRadius*cos(10*360.0/14.0*deg), stringRadius*sin(10*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly11affine = new G4AffineTransform(StringAssembly11localRot,*StringAssembly11localPos);
    *StringAssembly11affine*=*assemAffine;
    G4ThreeVector *StringAssembly11globalPos = new G4ThreeVector(StringAssembly11affine->NetTranslation());
    G4RotationMatrix *StringAssembly11globalRot= new G4RotationMatrix(StringAssembly11affine->NetRotation());
    fString11Ptr->Place(StringAssembly11globalPos, StringAssembly11globalRot, motherLogical);
    delete StringAssembly11localPos;
    delete StringAssembly11localRot;
    delete StringAssembly11affine;
  }

  if(fString12Ptr != NULL)
  {
    G4ThreeVector *StringAssembly12localPos;
    G4RotationMatrix *StringAssembly12localRot = new G4RotationMatrix();
    StringAssembly12localRot->rotateZ(-11*360.0/14.0*deg);
    StringAssembly12localPos = new G4ThreeVector(stringRadius*cos(11*360.0/14.0*deg), stringRadius*sin(11*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly12affine = new G4AffineTransform(StringAssembly12localRot,*StringAssembly12localPos);
    *StringAssembly12affine*=*assemAffine;
    G4ThreeVector *StringAssembly12globalPos = new G4ThreeVector(StringAssembly12affine->NetTranslation());
    G4RotationMatrix *StringAssembly12globalRot= new G4RotationMatrix(StringAssembly12affine->NetRotation());
    fString12Ptr->Place(StringAssembly12globalPos, StringAssembly12globalRot, motherLogical);
    delete StringAssembly12localPos;
    delete StringAssembly12localRot;
    delete StringAssembly12affine;
  }

  if(fString13Ptr != NULL)
  {
    G4ThreeVector *StringAssembly13localPos;
    G4RotationMatrix *StringAssembly13localRot = new G4RotationMatrix();
    StringAssembly13localRot->rotateZ(-12*360.0/14.0*deg);
    StringAssembly13localPos = new G4ThreeVector(stringRadius*cos(12*360.0/14.0*deg), stringRadius*sin(12*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly13affine = new G4AffineTransform(StringAssembly13localRot,*StringAssembly13localPos);
    *StringAssembly13affine*=*assemAffine;
    G4ThreeVector *StringAssembly13globalPos = new G4ThreeVector(StringAssembly13affine->NetTranslation());
    G4RotationMatrix *StringAssembly13globalRot= new G4RotationMatrix(StringAssembly13affine->NetRotation());
    fString13Ptr->Place(StringAssembly13globalPos, StringAssembly13globalRot, motherLogical);
    delete StringAssembly13localPos;
    delete StringAssembly13localRot;
    delete StringAssembly13affine;
  }

  if(fString14Ptr != NULL)
  {
    G4ThreeVector *StringAssembly14localPos;
    G4RotationMatrix *StringAssembly14localRot = new G4RotationMatrix();
    StringAssembly14localRot->rotateZ(-13*360.0/14.0*deg);
    StringAssembly14localPos = new G4ThreeVector(stringRadius*cos(13*360.0/14.0*deg), stringRadius*sin(13*360.0/14.0*deg), 0); //0
    G4AffineTransform *StringAssembly14affine = new G4AffineTransform(StringAssembly14localRot,*StringAssembly14localPos);
    *StringAssembly14affine*=*assemAffine;
    G4ThreeVector *StringAssembly14globalPos = new G4ThreeVector(StringAssembly14affine->NetTranslation());
    G4RotationMatrix *StringAssembly14globalRot= new G4RotationMatrix(StringAssembly14affine->NetRotation());
    fString14Ptr->Place(StringAssembly14globalPos, StringAssembly14globalRot, motherLogical);
    delete StringAssembly14localPos;
    delete StringAssembly14localRot;
    delete StringAssembly14affine;
  }

  delete assemAffine;
}
