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
 */
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Neil McFadden
 * CONTACT: nmcfadde@unm.edu
 * FIRST SUBMISSION: 
 *
 * REVISION:
 *
 */
//---------------------------------------------------------------------------//
//

#include <map>
#include <vector>
#include <string>

// Geant4
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4OpticalSurface.hh"

#ifndef _LGND_200_OpticalSurfaces_HH
#define _LGND_200_OpticalSurfaces_HH

//---------------------------------------------------------------------------//


class G4LogicalVolume;

using namespace std;
//---------------------------------------------------------------------------//

class LGND_200_OpticalSurfaces
{

public:
  LGND_200_OpticalSurfaces();
  ~LGND_200_OpticalSurfaces();

  // delete everything else
  LGND_200_OpticalSurfaces           (LGND_200_OpticalSurfaces const&) = delete;
  LGND_200_OpticalSurfaces& operator=(LGND_200_OpticalSurfaces const&) = delete;
  LGND_200_OpticalSurfaces           (LGND_200_OpticalSurfaces&&)      = delete;
  LGND_200_OpticalSurfaces& operator=(LGND_200_OpticalSurfaces&&)      = delete;

  static G4OpticalSurface* GetOpticalSurface(std::string name);
  static std::vector<std::string> GetListOfSurfaces();
private:
  static const G4double LambdaE;
  // hash table to store optical surfaces
  static std::map<std::string, G4OpticalSurface*> fOpticalSurfaces;
};
//
#endif
