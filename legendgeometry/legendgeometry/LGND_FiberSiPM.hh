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
 * CLASS DECLARATION:  LGND_FiberSiPM.hh
 *
 *---------------------------------------------------------------------------//
 *
 * DESCRIPTION:
 *
 */
// Begin description of class here
/**
 *
 *Geometry code for the string tie rods
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
 * AUTHOR: Neil McFadden
 * CONTACT: nmcfadde@unm.edu
 * FIRST SUBMISSION: 
 *
 * REVISION:
 *
 */
// --------------------------------------------------------------------------//

#ifndef _LGND_FIBESIPM_HH
#define _LGND_FIBERSIPM_HH

//---------------------------------------------------------------------------//

#include "legendgeometry/LGND_Part.hh"

class G4LogicalVolume;

using namespace std;
//---------------------------------------------------------------------------//

class LGND_FiberSiPM: public LGND_Part
{

public:
  LGND_FiberSiPM(G4String, G4String, G4double);
  LGND_FiberSiPM(G4String, G4String, G4double,G4String);
  LGND_FiberSiPM(G4String, G4String, G4double,G4double,G4String);
  LGND_FiberSiPM(G4String, G4String);
  LGND_FiberSiPM(const LGND_FiberSiPM &);
  ~LGND_FiberSiPM();

  G4LogicalVolume* BuildLogicalVolume();
  void SetLength(G4double length) {fLength = length*CLHEP::mm;}
  G4String GetShape(){return fShape;}
  G4double GetRadius(){return fRadius;}
  G4double GetLength(){return fLength;}

private:
  G4double fLength;
  G4String fShape = "square";
  G4double fRadius;
  G4String fPartName = "";

};
//
#endif
