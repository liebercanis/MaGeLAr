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
 * $Id: TSCylinderShieldTankMessenger.hh,v 1.1 2011-03-11  $
 *      
 * CLASS DECLARATION:  TSCylinderShieldTankMessenger.hh
 *
 *---------------------------------------------------------------------------//
 *
 * DESCRIPTION: 
 *
 */ 
// Begin description of class here
/**
 *
 *
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
 * AUTHOR: R.Martin
 * CONTACT: 
 * FIRST SUBMISSION: 11 Mar 2011
 * 
 * REVISION:
 * 
 * 03-11-2011 R. Martin created
 */
// --------------------------------------------------------------------------//

#ifndef _TSCYLINDERSHIELDTANKMESSENGER_HH
#define _TSCYLINDERSHIELDTANKMESSENGER_HH

//---------------------------------------------------------------------------//

#include "G4UImessenger.hh"

//---------------------------------------------------------------------------//

class TSCylinderShieldTank;

class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;
class G4UIcommand;

class TSCylinderShieldTankMessenger : public G4UImessenger
{
  public:
    TSCylinderShieldTankMessenger(TSCylinderShieldTank *assy);
    ~TSCylinderShieldTankMessenger();
  
    void SetNewValue(G4UIcommand* cmd, G4String nV);

  private:
    G4UIdirectory        *fDirectory;
    TSCylinderShieldTank *fTank;
  
    // Commands.
    G4UIcmdWithADoubleAndUnit *fTankRadiusCmd;
    G4UIcmdWithADoubleAndUnit *fTankHeightCmd;
    G4UIcmdWithADoubleAndUnit *fTankWallThicknessCmd;  
    G4UIcmdWithAString        *fShieldMaterialCmd;
    G4UIcmdWithAString        *fTankWallMaterialCmd;
};
#endif
