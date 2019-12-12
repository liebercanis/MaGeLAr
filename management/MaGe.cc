//---------------------------------------------------------------------------//
//Bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
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
// $Id: MaGe.cc,v 1.20 2009-08-31 09:14:40 jliu Exp $
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 *
 * main() For MaGe simulation program. Handles command line interface and
 * Geant 4 initialization.
 *
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Reyco Henning
 * CONTACT: rhenning@lbl.gov
 * FIRST SUBMISSION: Wed Mar 17 13:50:47 PST 2004
 *
 * REVISION:
 *
 * 3-17-2004:  Created. R. Henning
 * 4-16-2004:  Added G4Manager and other G4 mandatory actions. R. Henning
 * 5-16-2004:  Added MJManagementVisualization. R. Henning
 * 7-06-2004:  Added MJManager, R. Henning
 * 11-08-2004: Added TrackingAction, Xiang
 * 12-07-2004, Modifed for Gerda Integration, R. Henning
 * 12-15-2004: Added Stacking Action, L. Pandola
 * 03-07-2007, Changed TrackingAction, so that GETrajectory is executed only when required,
 *             L. Pandola
 * 20-11-2017, Allow for up to 100 macro commands to be saved in G4UImanager::histVec K. v. Sturm 
 * 30-10-2018, Improve header and usage message, suppress the Geant4 header, L. Pertoldi
 */
//---------------------------------------------------------------------------//
//

#include <string.h>
#include <vector>

#include "CLHEP/ClhepVersion.h"
#include "G4Version.hh"

#include "globals.hh"
#include "G4PhysListFactory.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4UImanager.hh"
#include "G4UIsession.hh"
#include "G4UIterminal.hh"
#include "G4VisManager.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION "undefined"
#endif

#include "generators/MGGeneratorPrimary.hh"
#include "management/MGManagementEventAction.hh"
#include "management/MGManagementRunAction.hh"
#include "management/MGManagementTrackingAction.hh"
#include "management/MGManagementSteppingAction.hh"
#include "management/MGManagementStackingAction.hh"
#include "management/MGManagerDetectorConstruction.hh"
#include "management/MGManager.hh"
#include "processes/MGProcessesList.hh"
#include "io/MGLogger.hh"
#include "MGDOUtils.hh"

// Functions called from main().
void PrintHeader();
void PrintUsage();

using namespace std;

//---------------------------------------------------------------------------//

int main(int argc, char** argv)
{
  PrintHeader();

  // save command line arguments
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i) args.emplace_back(argv[i]);

  // help
  if (std::find(args.begin(), args.end(), "--help") != args.end()
      or std::find(args.begin(), args.end(), "-h") != args.end()) {
    PrintUsage();
    return 0;
  }

  // want a fancy colored output?
  auto term = getenv("TERM");
  if (std::find(args.begin(), args.end(), "--no-colors") != args.end() or !term) {
      MGLog(trace) << "Disabling colors in output" << endlog;
      MGLogger::SetColorOutput(false);
  }

  // too many arguments?
  if (argc > 5) {
      PrintUsage();
      return 1;
  }

  MGLog(trace) << "Creating G4 and MJ Runmanagers." << endlog;
  // Suppress the Geant4 header:
  // save underlying buffer and set null (only standard output)
  streambuf* orig_buf = cout.rdbuf();
  cout.rdbuf(nullptr);

  G4RunManager *runManager = new G4RunManager;
  runManager->SetVerboseLevel(0);

  // restore buffer
  cout.rdbuf(orig_buf);

  MGManager *mjMgmt = new MGManager;

  // Set mandatory Geant4 action classes:
  // ------------------------------------

  // Register detector geometry and materials.
  MGLog(trace) << "Creating and registering G4 geometry." << endlog;
  MGManagerDetectorConstruction *Simulateddetector =
    new MGManagerDetectorConstruction;
  runManager->SetUserInitialization(Simulateddetector);
  mjMgmt->SetUserInitialization(Simulateddetector);

  // Register Geant4 physics processes
  MGLog(trace) << "Registering G4 physics processes." << endlog;

  // Search command line for -p [physlistname]
  G4VUserPhysicsList* processes = nullptr;
  auto result = std::find(args.begin(), args.end(), "-p");
  if (result != args.end()) {
    if(result == args.end()-1) {
      PrintUsage();
      return 1;
    }
    MGLog(trace) << "Using G4 physics list '" << *(result+1) << "'" << endlog;
    processes = (new G4PhysListFactory)->GetReferencePhysList(*(result+1));
    if (processes == nullptr) {
        MGLog(trace) << "Aborting..." << endlog;
        return 1;
    }
  }

  if(processes == nullptr) processes = new MGProcessesList;
  runManager->SetUserInitialization(processes);
  mjMgmt->SetUserInitialization(processes);

  // Create and initialize visualization manager.
  MGLog(trace) << "Creating and initializing visualization manager." << endlog;
  G4VisManager* visManager = new G4VisExecutive();
  visManager->SetVerboseLevel(0);
  mjMgmt->SetUserInitialization(visManager);
  visManager->Initialize();
  MGLog(trace) << "Available graphic systems: " << endlog;
  std::string s = "";
  int count = 0;
  for (auto& i : visManager->GetAvailableGraphicsSystems()) {
    s += i->GetNickname() + " ";
    count++;
    if (count == 6) {
      MGLog(trace) << "    " << s << endlog;
      s = "";
      count = 0;
    }
  }
  MGLog(trace) << "    " << s << endlog;


  // Register event generator.
  MGLog(trace) << "Registering G4 event generator." << endlog;
  MGGeneratorPrimary *generator = new MGGeneratorPrimary;
  runManager->SetUserAction(generator);
  mjMgmt->SetUserInitialization(generator);

  // Register run action. What to do at beginning and end of each run.
  MGLog(trace) << "Registering G4 run action." << endlog;
  MGManagementRunAction *runAction = new MGManagementRunAction;
  runManager->SetUserAction(runAction);
  mjMgmt->SetUserInitialization(runAction);

  // Register event action, ie. what to save/compute for each event.
  MGLog(trace) << "Registering G4 event action." << endlog;
  MGManagementEventAction *eventAction = new MGManagementEventAction;
  runManager->SetUserAction(eventAction);
  mjMgmt->SetUserInitialization(eventAction);

  //Register tracking action
  MGLog(trace) << "Registering G4 tracking action." << endlog;
  MGManagementTrackingAction *trackAction = new MGManagementTrackingAction(eventAction);
  runManager->SetUserAction(trackAction);
  mjMgmt->SetUserInitialization(trackAction);

  // Register stepping action, ie. what to save/compute for each step.
  MGLog(trace) << "Registering G4 stepping action." << endlog;
  MGManagementSteppingAction *stepAction = new MGManagementSteppingAction(eventAction);
  runManager->SetUserAction(stepAction);
  mjMgmt->SetUserInitialization(stepAction);

  // Register stacking action, ie. what to do for each new stacked particle.
  MGLog(trace) << "Registering G4 stacking action." << endlog;
  MGManagementStackingAction *stackAction = new MGManagementStackingAction(eventAction);
  runManager->SetUserAction(stackAction);
  mjMgmt->SetUserInitialization(stackAction);


  // Select run mode.
  // --------------------------------------------------

  if (argc == 1) {
    MGLog(routine) << "Entering interactive mode." << endlog;
    G4UIsession *session = new G4UIterminal(new G4UItcsh);
    session->SessionStart();
    delete session;
  }
  else {
    MGLog(routine) << "Entering batch mode..." << endlog;
    MGLog(routine) << "Executing script file from command line: " << *(args.end()-1) << endlog;
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI -> SetMaxHistSize( 100 );
    G4String command = "/control/execute ";
    G4String fileName = *(args.end()-1);
    UI->ApplyCommand(command + fileName);
  }

  delete visManager;
  delete mjMgmt;
  if(!G4GeometryManager::GetInstance()->IsGeometryClosed()) delete runManager;
  else MGLog(warning) << " problem deleting runManger " << endlog;
  MGLog(routine) << " end MaGe " << endlog;

  return 0;
}

//---------------------------------------------------------------------------//

void PrintHeader() {
  std::string title = "MaGe - Majorana/GERDA Monte Carlo Simulation Software";
  std::string mage_rev = "  From " + std::string(MGLogger::GetMaGeRevision()) + "/"
                         + std::string(MGLogger::GetMaGeTag()) + " ("
                         + std::string(MGLogger::GetMaGeDate()) + ")";
  std::string clhep_rev = "CLHEP version: " + CLHEP::Version::String();

  std::string G4v(G4Version.data());
  G4v = G4v.substr(14);
  G4v = G4v.substr(0, G4v.size()-2);
  std::string geant4_rev = "Geant4 version: " + G4v + " " + G4Date;
  std::string mgdo_rev = "MGDO version: " + std::string(MGDOUtils::GetMGDORevision()) + "/"
                         + std::string(MGDOUtils::GetMGDOTag()) + " ("
                         + std::string(MGDOUtils::GetMGDODate()) + ")";

  // get longest line
  int biggest_size = 0;
  for (auto& s : {title, mage_rev, clhep_rev, geant4_rev, mgdo_rev}) {
    if ((int)s.size() > biggest_size) biggest_size = s.size();
  }

  std::string line;
  std::string blank;

  for (int i = title.size();      i < biggest_size; i++) title += " ";
  for (int i = mage_rev.size();   i < biggest_size; i++) mage_rev += " ";
  for (int i = clhep_rev.size();  i < biggest_size; i++) clhep_rev += " ";
  for (int i = geant4_rev.size(); i < biggest_size; i++) geant4_rev += " ";
  for (int i = mgdo_rev.size();   i < biggest_size; i++) mgdo_rev += " ";
  for (int i = 0;                 i < biggest_size; i++) {
      line += "─";
      blank += " ";
  }
  line += "──";

  G4cout << " ┌"  << line       <<  "┐" << G4endl
         << " │ " << title      << " │" << G4endl
         << " │ " << blank      << " │" << G4endl
         << " │ " << mage_rev   << " │" << G4endl
         << " │ " << blank      << " │" << G4endl
         << " │ " << clhep_rev  << " │" << G4endl
         << " │ " << geant4_rev << " │" << G4endl
         << " │ " << mgdo_rev   << " │" << G4endl
         << " └"  << line       <<  "┘" << G4endl << G4endl;
}

//---------------------------------------------------------------------------//

void PrintUsage() {
  G4cout << "Usage:"                                                          << G4endl;
  G4cout << "    MaGe [OPTIONS] [SCRIPT]"                                     << G4endl << G4endl;
  G4cout << "Options:"                                                        << G4endl;
  G4cout << "    --help, -h     : display this help message and exit"         << G4endl;
  G4cout << "    -p <list-name> : use Geant4 internal list-name physics list" << G4endl;
  G4cout << "    --no-colors    : disable colors in output"                   << G4endl << G4endl;
  G4cout << "Invoking MaGe without arguments starts an interactive session."  << G4endl << G4endl;
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
