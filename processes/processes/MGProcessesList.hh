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
 * $Id: MGProcessesList.hh,v 1.8 2009-01-17 15:14:12 jasondet Exp $
 *      
 * CLASS DECLARATION:  MGProcessesList.hh
 *
 *---------------------------------------------------------------------------//
 *
 * DESCRIPTION: 
 *
 */ 
// Begin description of class here
/**
 * This class is the primary physics list definition. It invokes a few other
 * classes, that should also be in the MG/processes hierarchy.
*/
// End class description
//
/**  
 * SPECIAL NOTES:
 * The physics list is an amalgam of the physics list from the underground
 * physics advanced example that's distributed with GEANT4 and the QGSP_HP
 * physics list.
 */
// 
// --------------------------------------------------------------------------//
/** 
 * AUTHOR: R.Henning
 * CONTACT: 
 * FIRST SUBMISSION: Mon Apr 19 14:42:36 PDT 2004
 * 
 * REVISION:
 * 
 * 04-19-2004, Initiated, R. Henning.
 * 04-23-2004, Kareem
 *             First editing after file initialization
 * 09-14-2004, Kareem
 *             Added the SetRealm method for interfacing with the list messenger
 * 02-14-2005, Luciano
 *             Added a few methods for Cerenkov and Muon-Nucleus Construction
 * 02-16-2005, Luciano
 *             Added a flag for switching Std/LowE EM
 * 07-12-2005, Luciano
 *             Added method for alternative physics lists and a boolean flag
 * 04-16-2008, Luciano
 *             Added method and private members to dump physics list
 * 01-26-2010, Luciano
 *             Migration of physics list according to Geant4 9.3
 * 18 Nov 2011 A. Schubert
 *             Added parallel world scoring process
 * 24 Aug 2017 R. Massarczyk
 *             Added getStep limits to check that limits are set properly
 * 25-06-2018, Ralph Massarczyk     Added different physics list options, when lowenergy flag enabled
 */
// --------------------------------------------------------------------------//

#ifndef _MGPROCESSESLIST_HH
#define _MGPROCESSESLIST_HH

//---------------------------------------------------------------------------//

#include <map>

//  GEANT4 headers
#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "G4ios.hh"

//  Forward declarations
class MGProcessesMessenger;
class G4VPhysicsConstructor;

//---------------------------------------------------------------------------//

class MGProcessesList : public G4VModularPhysicsList {

  //public interface
public:
  
  //default constructor
  MGProcessesList();
    
  //destructor
  virtual ~MGProcessesList();
  
public:
  virtual void SetCuts();
  void SetRealm( G4String );
  void SetOpticalFlag(G4bool val) {constructOptical = val;};
  void SetOpticalPhysicsOnly(G4bool val) {fUseOpticalPhysicsOnly = val;}//used to speed up optical only simulations
  void SetLowEnergyFlag(G4bool val) {useLowE = val;};
  void SetLowEnergyOption(G4int val) {fuseLowEoption = val;};

  void SetUseBertiniCascadeFlag(G4bool val) {fUseBertiniCascade = val;};
  void SetUseFTFFlag(G4bool val) {fUseFTFFlag = val;};
  void SetUseNoHadPhysFlag(G4bool val) {fUseNoHadPhysFlag = val;};
  void SetUseAllHPFlag(G4bool val) {fUseAllHPFlag = val;};  // For TENDL/ChargedParticleHP
  void SetUseAngCorr(G4int maxTwoJ);//{ fAngCorrMaxTwoJ = maxTwoJ; }
  void SetStoreICLevelData(G4bool store);
  void DumpPhysicsList();
  void GetStepLimits();

  virtual inline void LimitStepForParticle(G4String particleName) {
    fLimitSteps[particleName] = true;
  }
  
  //protected members
protected:

  // Define mandatory inherited virtual methods.
  void ConstructParticle();
  void ConstructProcess();
  
  // These methods Construct physics processes and register them
  virtual void AddTransportation();
  virtual void AddParallelWorldScoring();
  virtual void ConstructOp();

  virtual void ConstructCerenkov();

  //private  members
private:
  G4int VerboseLevel;
  G4int OpVerbLevel;
  
  G4double cutForOpticalPhoton;
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;
  G4double cutForAlpha;
  G4double cutForGenericIon;
  
  G4double cutForGammaSensitive;
  G4double cutForElectronSensitive;
  G4double cutForPositronSensitive;

  G4bool constructOptical;
  G4bool useLowE;
	G4int  fuseLowEoption;
  G4bool fUseBertiniCascade;
  G4bool fUseFTFFlag;
  G4bool fUseNoHadPhysFlag;
  G4bool fUseAllHPFlag;
  G4bool fUseOpticalPhysicsOnly;

  G4String fPhysicsListHadrons; 

  std::map<G4String, bool> fLimitSteps;
  
  G4VPhysicsConstructor* fEMConstructor;

  MGProcessesMessenger* processesMessenger;
};
#endif
