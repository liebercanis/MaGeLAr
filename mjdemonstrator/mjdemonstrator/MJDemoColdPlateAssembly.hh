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
 * CLASS DECLARATION:  MJDemoColdPlateAssembly.hh
 *
 *---------------------------------------------------------------------------//
 *
 * DESCRIPTION: 
 *
 */ 
// Begin description of class here
/**
 *
 *The Cold Plate assembly, comprising the cold plate, pins, wedges, hv takeups,
 *and captured hex bolts and nuts.
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
 * CONTACT: mpgreen@ornl.gov
 * FIRST SUBMISSION: Oct 1, 2014
 * 
 * REVISION:
 * 
 * 10-01-2014, Created, M. Green
 */
// --------------------------------------------------------------------------//

#ifndef _MJDEMOCOLDPLATEASSEMBLY_HH
#define _MJDEMOCOLDPLATEASSEMBLY_HH

//---------------------------------------------------------------------------//

#include "mjdemonstrator/MJVDemoAssembly.hh"
#include "mjdemonstrator/MJVDemoPart.hh"

class G4LogicalVolume;
class MJDemoColdplateCryo1Symmetric;


using namespace std;
//---------------------------------------------------------------------------//

class MJDemoColdPlateAssembly: public MJVDemoAssembly
{
  
public:
  MJDemoColdPlateAssembly(G4String, G4String);
  MJDemoColdPlateAssembly(const MJDemoColdPlateAssembly &);
  ~MJDemoColdPlateAssembly();

  MJDemoColdplateCryo1Symmetric* GetCP() {return fCPPtr;}


  void Place(G4ThreeVector* assemPosition, G4RotationMatrix* assemRotation,
                     G4LogicalVolume* motherLogical);

  
  
private:
  MJDemoColdplateCryo1Symmetric* fCPPtr;

};
//
#endif
