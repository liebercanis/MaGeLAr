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
 * CLASS DECLARATION:  LGND_HVSigCable.hh
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
 * AUTHOR: Matthew Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: Dec 2, 2017
 *
 * REVISION:
 *
 * 12-02-2017, Created, M. Green
 */
// --------------------------------------------------------------------------//

#ifndef _LGND_HVSIGCABLE_HH
#define _LGND_HVSIGCABLE_HH

//---------------------------------------------------------------------------//

#include "legendgeometry/LGND_Part.hh"

class G4LogicalVolume;

using namespace std;
//---------------------------------------------------------------------------//

class LGND_HVSigCable: public LGND_Part
{

public:
  LGND_HVSigCable(G4String, G4String, G4double, G4String);
  LGND_HVSigCable(G4String, G4String, G4double);
  LGND_HVSigCable(const LGND_HVSigCable &);
  ~LGND_HVSigCable();

  G4LogicalVolume* BuildLogicalVolume();
  void SetLength(G4double length) {fLength = length*CLHEP::mm;}

private:
  G4double fLength;

};
//
#endif
