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
//                                                          
// $Id: MGManagerMessenger.cc,v 1.10 2007-08-17 21:41:45 mgmarino Exp $ 
//      
// CLASS IMPLEMENTATION:  MGManagerMessenger.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 */
// 
//---------------------------------------------------------------------------//
/**
 * AUTHOR: R.Henning
 * CONTACT: 
 * FIRST SUBMISSION: Tue Jul  6 17:37:42 PDT 2004
 * 
 * REVISION:
 *
 * 07-06-2004, Created, R. Henning
 * 12-07-2004, Modified for Gerda Integration, R. Henning
 * 01-27-2005, If heprandomseed is set in the macro file, set flag to not change
 *             the seed at the beginning of each run, Kareem
 *
 */
//---------------------------------------------------------------------------//

#include <fstream>

//#include "CLHEP/Random/Random.h"
#include "Randomize.hh"        

#include "globals.hh"        
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"   
#include "G4UIcmdWithoutParameter.hh"   
#include "G4UImessenger.hh"

#include "management/MGManager.hh"
#include "management/MGManagementRunAction.hh"
#include "io/MGLogger.hh"

#include "TUUID.h"

//---------------------------------------------------------------------------//

#include "management/MGManagerMessenger.hh"

//---------------------------------------------------------------------------//

using namespace std;

MGManagerMessenger::MGManagerMessenger(MGManager* /*manager*/)/*:
  fManager(manager)*/
{
  fDirectory = new G4UIdirectory("/MG/manager/");
  fDirectory->SetGuidance("Management controls.");

  // /MG/manager/mjlog
  fMGLogCmd = new G4UIcmdWithAString("/MG/manager/mglog", this);
  fMGLogCmd->SetGuidance("Set severity of logs to report to stdout.");
  fMGLogCmd->SetGuidance("Options, in ascending order of severity, are:");
  fMGLogCmd->SetGuidance("debugging: Displays all logs ");
  fMGLogCmd->SetGuidance("trace: All logs, except debugging(default)");
  fMGLogCmd->SetGuidance("routine: All logs, except debugging and trace");
  fMGLogCmd->SetGuidance("warning: All logs, except trace, debugging and routine:");
  fMGLogCmd->SetGuidance("error: Only error and fatal logs.");
  fMGLogCmd->SetGuidance("fatal: Only fatal logs.");

  //MG/manager/heprandomseed
  fHEPRandomSeedCmd=new G4UIcmdWithAnInteger("/MG/manager/heprandomseed",this);
  fHEPRandomSeedCmd->SetGuidance("Sets random number generator seed.");

  //MG/manager/useInternalSeed
  fUseInternalSeedCmd = 
    new G4UIcmdWithAnInteger("/MG/manager/useInternalSeed", this);
  fUseInternalSeedCmd->SetGuidance("Sets random number generator seed using internal seed table.");
  fUseInternalSeedCmd->SetGuidance("Provide the index of the seed you would like to use (0-429)");
  fUseInternalSeedCmd->SetParameterName("index", false);
  fUseInternalSeedCmd->SetRange("index>=0 && index<430");

  //MG/manager/seedWithDevRandom
  fSeedWithDevRandomCmd = new G4UIcmdWithoutParameter("/MG/manager/seedWithDevRandom", this);
  fSeedWithDevRandomCmd->SetGuidance("Seed random number generator with a \"truly\" random number");
  fSeedWithDevRandomCmd->SetGuidance("generated by a read from /dev/random");

  //MG/manager/seedWithUUID
  fSeedWithUUIDCmd = new G4UIcmdWithoutParameter("/MG/manager/seedWithUUID", this);
  fSeedWithUUIDCmd->SetGuidance("Seed random number generator quickly with an almost random number");
  fSeedWithUUIDCmd->SetGuidance("Generated using ROOT's TUUID class");

  //MG/manager/useRandomEngine
  fUseRandomEngine = 
    new G4UIcmdWithAString("/MG/manager/useRandomEngine", this);
  fUseRandomEngine->SetGuidance("Sets type of random engine to use.");
  G4String randomEngineCandidates;
  randomEngineCandidates = "JamesRandom RanLux MTwist";
  fUseRandomEngine->SetCandidates(randomEngineCandidates);

  MGLog(trace) << "Constructor called." << endlog;
}

//---------------------------------------------------------------------------//

MGManagerMessenger::MGManagerMessenger(const MGManagerMessenger & other) : G4UImessenger(other)
{;}

//---------------------------------------------------------------------------//

MGManagerMessenger::~MGManagerMessenger()
{
  delete fHEPRandomSeedCmd;
  delete fMGLogCmd;
  delete fDirectory;
}

//---------------------------------------------------------------------------//

G4String MGManagerMessenger::GetCurrentValue(G4UIcommand*)
{ 
  G4String cv = "";
  return cv;
}
//---------------------------------------------------------------------------//

void MGManagerMessenger::SetNewValue(G4UIcommand *command, G4String newValues)
{
  // /MG/manager/mjlog
  if(command == fMGLogCmd) {
    if(newValues == "debugging")
      MGLogger::SetSeverity(MGLogger::debugging);
    else if(newValues == "trace")
      MGLogger::SetSeverity(MGLogger::trace);
    else if(newValues == "routine")
      MGLogger::SetSeverity(MGLogger::routine);
    else if(newValues == "warning")
      MGLogger::SetSeverity(MGLogger::warning);
    else if(newValues == "error") 
      MGLogger::SetSeverity(MGLogger::error);
    else if(newValues == "fatal")
      MGLogger::SetSeverity(MGLogger::fatal);
    else
      G4cout << "Unknown option." << G4endl;

  // /MG/manager/heprandomseed
  } else if (command == fHEPRandomSeedCmd) {

	  // We could make the comparison through strings
	  std::stringstream strval;
	  strval << newValues;
	  long theSeed;
	  strval >> theSeed;

	  if (theSeed >= std::numeric_limits<long>::max()) {
      MGLog(error) << "Seed [" << newValues << "] is too large. Largest possible seed : " << std::numeric_limits<long>::max() << endlog;
      G4Exception("MGManagerMessenger::SetNewValue","ValueOverflow",FatalException,"Seed too large for the size of integer.");
	  }

	  CLHEP::HepRandom::setTheSeed(theSeed);
    MGLog(routine) << "CLHEP::HepRandom seed set to: "
       << theSeed << endlog;

    MGManager* manager = MGManager::GetMGManager();
    manager->GetMGRunAction()->SetControlledRandomization();
  } 
  
  // /MG/manager/useInternalSeed
  else if (command == fUseInternalSeedCmd) {
    int index = fUseInternalSeedCmd->GetNewIntValue(newValues);

    long seeds[2];
    int tableIndex = index/2;
    CLHEP::HepRandom::getTheTableSeeds(seeds, tableIndex);

    int arrayIndex = index % 2;
    CLHEP::HepRandom::setTheSeed(seeds[arrayIndex]);

    MGLog(routine) << "CLHEP::HepRandom seed set to: " << seeds[arrayIndex] << endlog;
	
    MGManager* manager = MGManager::GetMGManager();
	manager->GetMGRunAction()->SetControlledRandomization();
  }
 
  // /MG/manager/seedWithDevRandom
  
  else if (command == fSeedWithDevRandomCmd) {
    ifstream devrandom("/dev/random");
    if (devrandom.bad()) {
      MGLog(warning) << "seedWithDevRandom: couldn't open /dev/random. Your seed is not set." << endl;
    }
    else {
      long seed;
      MGLog(routine) << "Reading a seed from /dev/random..." << endl;
      devrandom.read((char*)(&seed), sizeof(long));

      // Negative seeds give nasty sequences for some engines. For example,
      // CLHEP's JamesRandom.cc contains a specific check for this. Might 
      // as well make all seeds positive; randomness is not affected (one 
      // bit of randomness goes unused).
      if (seed < 0) seed = -seed;
 
      CLHEP::HepRandom::setTheSeed(seed);
      MGLog(routine) << "CLHEP::HepRandom seed set to: " << seed << endlog;

      MGManager* manager = MGManager::GetMGManager();
        manager->GetMGRunAction()->SetControlledRandomization();
    }
    devrandom.close();
  }

  // /MG/manager/seedWithUUID
  
  else if (command == fSeedWithUUIDCmd) {
    TUUID uuid;
    UInt_t buffer[4];
    uuid.GetUUID((UChar_t*) buffer);
    long seed = (buffer[0] + buffer[1] + buffer[2] + buffer[3]);
    // Negative seeds give nasty sequences for some engines. For example,
    // CLHEP's JamesRandom.cc contains a specific check for this. Might 
    // as well make all seeds positive; randomness is not affected (one 
    // bit of randomness goes unused).
    if (seed < 0) seed = -seed;
 
    CLHEP::HepRandom::setTheSeed(seed);
    MGLog(routine) << "CLHEP::HepRandom seed set to: " << seed << endlog;

    MGManager* manager = MGManager::GetMGManager();
      manager->GetMGRunAction()->SetControlledRandomization();
  } 

  else if (command == fUseRandomEngine) {
    if(newValues == "JamesRandom") {
      CLHEP::HepRandom::setTheEngine(new CLHEP::HepJamesRandom);
      MGLog(routine) << "Using James engine." << endlog;
    }
    else if(newValues == "RanLux") {
      CLHEP::HepRandom::setTheEngine(new CLHEP::RanluxEngine);
      MGLog(routine) << "Using Ranlux engine." << endlog;
    }
    else if(newValues == "MTwist") {
      CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
      MGLog(routine) << "Using MTwist engine." << endlog;
    }
    else {
      CLHEP::HepRandom::setTheEngine(new CLHEP::HepJamesRandom);
      MGLog(routine) << "Using James engine." << endlog;
    }
  }
}
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
