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
/**
 * $Id: MGheadertemplate.hh,v 1.1 2004-12-09 08:58:35 pandola Exp $
 *
 * CLASS DECLARATION:  LGND_200_StringAssembly.hh
 *
 *---------------------------------------------------------------------------//
 *
 * DESCRIPTION:
 *
 */
// Begin description of class here
/**
 *
 *The assembly consisting of a string of 77mm crystal assemblies.
 *
 *
 */
// End class description
//
/**
 * SPECIAL NOTES:
 *
 */
//
// --------------------------------------------------------------------------//
/**
 * AUTHOR: Matthew Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: Jul 22, 2017
 *
 * REVISION:
 *
 * 07-22-2017, Created, M. Green
 */
// --------------------------------------------------------------------------//

#ifndef _LGND_200_STRINGASSEMBLY_HH
#define _LGND_200_STRINGASSEMBLY_HH

//---------------------------------------------------------------------------//

#include "legendgeometry/LGND_Assembly.hh"
#include "legendgeometry/LGND_Part.hh"

class G4LogicalVolume;
class LGND_200_DetUnitAssembly;
class LGND_HVSigCable;
class LGND_MiniShroud;

using namespace std;
//---------------------------------------------------------------------------//

class LGND_200_StringAssembly: public LGND_Assembly
{

public:
  LGND_200_StringAssembly(G4String, G4String, G4bool,G4String configFile = "LGND_200.json" );
  LGND_200_StringAssembly(const LGND_200_StringAssembly &);
  ~LGND_200_StringAssembly();

  size_t GetNumberOfCrystals() {return fCrystalNum;}
  void SetNumberOfCrystals(size_t crystalNum);
  G4double GetStringLength() {return fStringLength;}

  void Place(G4ThreeVector* assemPosition, G4RotationMatrix* assemRotation,
                     G4LogicalVolume* motherLogical);


private:
  size_t fCrystalNum;
  G4String fConfigFile;
  G4bool fSiPMArrayFlag;
  LGND_200_DetUnitAssembly** fDetUnitPtr;
  LGND_HVSigCable** fCablePtr;
  G4double fStringLength;
  LGND_MiniShroud* fMiniShroudPtr;
  LGND_MiniShroud* fMiniShroudInnerTPBptr;
  LGND_MiniShroud* fMiniShroudOuterTPBptr;


};
//
#endif
