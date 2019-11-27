//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
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
// $Id: MJcodeTemplate.cc,v 1.3 2005-02-15 23:26:55 akbarm Exp $ 
//      
// CLASS IMPLEMENTATION:  MJVDemoDetector.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 * 
 *
 */
// 
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Matthew Green
 * CONTACT: mpgreen@physics.unc.edu
 * FIRST SUBMISSION: Mon Jul  26 09:19:15 EST 2010
 * 
 * REVISION:
 *
 * 07-26-2010, Created, M. Green.
 *
 */
//---------------------------------------------------------------------------//
//
 
#include "G4String.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "mjdemonstrator/MJVDemoDetector.hh"      //Present MJ Class Headers 

using namespace CLHEP;


//---------------------------------------------------------------------------//

MJVDemoDetector::MJVDemoDetector():
  MJVDemoPart()
{;}

//---------------------------------------------------------------------------//

MJVDemoDetector::MJVDemoDetector(G4String partName, G4String serialNumber, 
                         G4String drawingNumber, G4String material):
  MJVDemoPart(partName, serialNumber, drawingNumber, material)
{;}

//---------------------------------------------------------------------------//

MJVDemoDetector::MJVDemoDetector(const MJVDemoDetector & rhs):
  MJVDemoPart(rhs)
{;}

//---------------------------------------------------------------------------//

MJVDemoDetector::~MJVDemoDetector()
{;}

//---------------------------------------------------------------------------//
