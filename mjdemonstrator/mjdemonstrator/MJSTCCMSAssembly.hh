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
//      
// CLASS IMPLEMENTATION:  MJSTCCMSAssembly.hh
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
 * AUTHOR: Jacquie MacMullin
 * CONTACT: jacq3749@gmail.com
 * FIRST SUBMISSION: Tuesday January 21 2014
 * 
 * REVISION:
 * 01-21-2014, Created. Used to be a part of ColdPlateAssembly. I separated
 *             it to make it easier to rotate it through the messenger, J. MacMullin
 *
 */
//---------------------------------------------------------------------------//
//


//---------------------------------------------------------------------------//

#ifndef _MJSTCCMSASSEMBLY_HH
#define _MJSTCCMSASSEMBLY_HH

//---------------------------------------------------------------------------//

#include "mjdemonstrator/MJVDemoAssembly.hh"
#include "mjdemonstrator/MJVDemoPart.hh"

class G4LogicalVolume;
class MJSTCCMSStand;
class MJSTCCMSSpool;
class MJSTCCMSGrooves;

using namespace std;

//---------------------------------------------------------------------------//

class MJSTCCMSAssembly: public MJVDemoAssembly
{
  
public:
  MJSTCCMSAssembly(G4String, G4String);
  MJSTCCMSAssembly(const MJSTCCMSAssembly &);
  ~MJSTCCMSAssembly();

  MJSTCCMSStand* GetStand() {return fStandPtr;}
  MJSTCCMSSpool* GetSpool() {return fSpoolPtr;}
  MJSTCCMSGrooves* GetGrooves() {return fGroovesPtr;}
    
  void Place(G4ThreeVector* assemPosition, G4RotationMatrix* assemRotation,
                     G4LogicalVolume* motherLogical);
  
private:
  MJSTCCMSStand* fStandPtr;
  MJSTCCMSSpool* fSpoolPtr;
  MJSTCCMSGrooves* fGroovesPtr;

};
//
#endif
