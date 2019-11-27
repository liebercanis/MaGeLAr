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
 * CLASS DECLARATION:  TSCryostatAssembly.hh
 *
 *---------------------------------------------------------------------------//
 *
 * DESCRIPTION: 
 *
 */ 
// Begin description of class here
/**
 *
 *The Cryostat assembly MJDemoCryostatAssembly was modified to remove the 
 *cross arm
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
 * CONTACT: mpgreen@physics.unc.edu
 * FIRST SUBMISSION: Oct 1, 2010
 * 
 * REVISION:
 * 
 * 10-01-2010, Created, M. Green
 * 03-02-2011, Modified by R. Martin
 */
// --------------------------------------------------------------------------//

#ifndef _TSCRYOSTATASSEMBLY_HH
#define _TSCRYOSTATASSEMBLY_HH

//---------------------------------------------------------------------------//

#include "mjdemonstrator/MJVDemoAssembly.hh"
#include "mjdemonstrator/MJVDemoPart.hh"

class G4LogicalVolume;
class MJDemoCryostatBottomLid;
class MJDemoCryostatTopLid;
class TSCryostatHoop;
class MJDemoCryostatCrossArmTube;
class MJDemoCryostatRailAssembly;

//---------------------------------------------------------------------------//

class TSCryostatAssembly: public MJVDemoAssembly
{
  public:
    TSCryostatAssembly(G4String, G4String);
    TSCryostatAssembly(const TSCryostatAssembly &); // copy constructor
    ~TSCryostatAssembly();
  
    MJDemoCryostatBottomLid* GetBottomLid() {return fBottomLidPtr;}
    MJDemoCryostatTopLid* GetTopLid() {return fTopLidPtr;}
    TSCryostatHoop* GetHoop() {return fHoopPtr;}
    //MJDemoCryostatCrossArmTube* GetTube() {return fCrossArmTubePtr;}
    //MJDemoCryostatRailAssembly* GetRailAssembly1() {return fRailAssembly1Ptr;}
    //MJDemoCryostatRailAssembly* GetRailAssembly2() {return fRailAssembly2Ptr;}
  
    void Place(G4ThreeVector* assemPosition, G4RotationMatrix* assemRotation, G4LogicalVolume* motherLogical);
  
  private:
    MJDemoCryostatBottomLid* fBottomLidPtr;
    MJDemoCryostatTopLid* fTopLidPtr;
    TSCryostatHoop* fHoopPtr;
    //MJDemoCryostatCrossArmTube* fCrossArmTubePtr;
    //MJDemoCryostatRailAssembly* fRailAssembly1Ptr;
    //MJDemoCryostatRailAssembly* fRailAssembly2Ptr; 
};

#endif
