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

#ifndef _MGOutputMCRun_HH
#define _MGOutputMCRun_HH

#include <string>
#include "TTree.h"
#include "TH3D.h"
#include "TH2D.h"

#include "io/MGLogger.hh"
#include "io/MGOutputRoot.hh"
#include "MGTMCEventHeader.hh"
#include "MGTMCEventSteps.hh"
#include "MGTMCRun.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Navigator.hh"
#include "obj/TGeEvent.hxx"
#include "obj/TLArEvent.hxx"



class G4Event;
class G4Step;
class G4UImessenger;
class G4ParticleDefinition;

/**                                                            
 * ROOT output to write all relevant G4 step data to tree. This can be used as a
 * base class for a more detailed output.  Values are in CLHEP units.
 *
 * AUTHOR: ASchubert
 * CONTACT: alexis3@u.washington.edu
 * FIRST SUBMISSION: Fri Jan 22 07:17:08 PST 2010
 * 
 * REVISION:
 *
 * MM-DD-YYYY
 * 05-09-2008, Created, J. Detwiler
 * 03-31-2010, Modified for MGDO classes, initial submissionA. Schubert
 * 04-08-2010, removed fRunInfoTree, made fMCRun a branch in fTree, A. Schubert
 * 04-20-2010, retrieved A, Z range for radioactive decay, stored in fMCRun, A.
 *             Schubert
 * 07-27-2010, removed decay chain stopping; this is handled by Gent4's nucleus
 *             limits, A. Schubert
 * 08-04-2010, active volumes are now any whose physical volume names contain 
 *             "ctive."  Added check to physical volume name length, A. Schubert
 * 09-07-2010, temporary fix to active volume search for MJDemonstrator naming
 *             scheme, M. Green
 * 09-28-2010, added method to print surface areas of all physical volumes,
 *             cleaned up method declarations, A. Schubert
 * 09-29-2010, manually imported changes from MaGe/branches/phys-list-G49.3, if
 *             fWriteAllSteps is false fTree is only filled for events that
 *             deposit energy, A.  Schubert
 * 10-19-2010, set process name of presteps to  creator process per V. Gehman
 *             suggestion, A. Schubert
 * 10-22-2010, changed post step local coords to resolve inconsistency between
 *             local coords and physical volume info for steps involving
 *             transportation, A. Schubert
 * 11-08-2010, Added MJDemonstrator active volume naming scheme
 * 11-15-2010, fixed classic naming scheme, length needs to be >= 28, A.
 *             Schubert
 * 11-27-2010, Cleared MGTMCEventHeader energies in WritePartialEvent() to fix
 *             bug in filling of event header during windowed events, A.
 *             Schubert
 * 05-20-2011, Added track weight, A. Schubert
 * 12-01-2011, Added fWriteAllStepsInEventsThatDepositEnergy to allow writing of
 *             all steps for only those events that deposit energy, A. Schubert
 * 12-07-2011, Calling MGMCRun SetUseImportanceSampling(),
 *             SetBiasedParticleID(), and SetUseParallelWorld() methods to
 *             record importance-sampling status,  A. Schubert
 * 12-13-2011, Setting fOffsetTime to zero in EndOfEventAction() to fix a bug
 *             found by Jason -- fOffsetTime was non-zero for the event following a
 *             time-windowed event, A. Schubert
 *
 */

/// Record Geant4 results in ROOT TTree with MGDO MGTMC* output classes.
class MGOutputMCRun : public MGOutputRoot
{
public:
  MGOutputMCRun(G4bool isMother);

  virtual ~MGOutputMCRun();

  // overloaded methods:
  virtual void BeginOfEventAction(const G4Event *event);
  virtual void BeginOfRunAction();
  virtual void DefineSchema();
  virtual void EndOfEventAction(const G4Event *event);
  virtual void EndOfRunAction();
  virtual void RootSteppingAction(const G4Step* step);
  virtual void WriteEvent();
  virtual void WriteFile();
  virtual void WritePartialEvent(const G4Event*) { WriteEvent(); }
 
  /// Clear event steps and event header.
  virtual inline void ResetPartialEvent(const G4Event*) 
    { fMCEventSteps->ClearSteps(); fMCEventHeader->ClearEnergies(); }

  // set and get methods:

  /// Set run ID.
  virtual inline void SetRunID(uint64_t runID) { fRunID = runID; }

  ///default 50000 via MGTMCEventSteps::InitializeArray()
  virtual inline void SetNSteps(uint64_t nsteps) {fNSteps = nsteps; }

  /// Set run description.
  virtual inline void SetDescription(std::string description) { fRunDescription = description; }

  /// Set whether to kill all alpha tracks outside sensitive volume after one step.
  virtual inline void SetKillAlphas(G4bool stat) { fKillAlphas = stat; }

  /// Set whether to kill all beta tracks outside sensitive volume after one step.
  virtual inline void SetKillBetas(G4bool stat) { fKillBetas = stat; }

  /// Set whether to kill all gamma tracks outside sensitive volume after one step.
  virtual inline void SetKillGammas(G4bool stat) { fKillGammas = stat; }

  /// Set whether to kill all neutron tracks outside sensitive volume after one step.
  virtual inline void SetKillNeutrons(G4bool stat) { fKillNeutrons = stat; }

  /// Set whether to stop nuclei outside sensitive volume, but don't kill them. This allows them to decay. 
  virtual inline void SetStopNuclei(G4bool blah) { fStopNuclei = blah; }

  /// Set whether to write all steps in event.
  virtual inline void SetWriteAllSteps(G4bool val) {fWriteAllSteps = val;}

  /// Set whether to write all steps in events that deposit energy in sensitive volumes.
  virtual inline void SetWriteAllStepsInEventsThatDepositEnergy(G4bool val)     
      {fWriteAllStepsInEventsThatDepositEnergy = val;}

  /// Set whether to print surface areas.
  virtual inline void SetAreSurfaceAreasPrinted(G4bool val) { fAreSurfaceAreasPrinted = val; }

  /// Return sensitive ID of given physical volume.
  virtual int GetSensitiveIDofPhysicalVolume(G4VPhysicalVolume* physVol);

  /// Return pointer to MGTMCRun object.
  virtual inline MGTMCRun* GetMCRun() const { return fMCRun; }
  
  /// Return pointer to MGTMCEventHeader. 
  virtual inline MGTMCEventHeader *GetMCEventHeader() { return fMCEventHeader; }

  /// Return pointer to MGTMCEventSteps event step data.
  virtual inline MGTMCEventSteps *GetMCEventSteps() { return fMCEventSteps; }

  /// Return pointer to MGTMCEventSteps primary particle data.
  virtual inline MGTMCEventSteps *GetMCEventPrimaries() { return fMCEventPrimaries; }

  // Don't override any volumes already set unless flag is set
  // Only messenger calls will override

  /// Return MaGe particle ID.
  static int GetMaGeParticleID(G4ParticleDefinition* particle);

  /// Return whether particle is a germanium nucleus.
  static bool MaGeParticleIDIsGeNucleus(int pid);

  // return elemet number in list geDet if exists, otherwise make a new one
  Int_t getGeDet(Int_t idet,  G4VPhysicalVolume* physVol )  {
    for(unsigned i=0; i< fGeEvent->geDet.size() ; ++i ) if(fGeEvent->geDet[i].id== idet) return Int_t(i);
    TGeDet *geDet = new TGeDet(idet);
    G4ThreeVector trans = physVol->GetTranslation();
    G4ThreeVector pmin;
    G4ThreeVector pmax;
    physVol->GetLogicalVolume()->GetSolid()->BoundingLimits(pmin,pmax); 
    geDet->setGlobal(trans.x(),trans.y(),trans.z());
    geDet->setPmin(pmin.x(),pmin.y(),pmin.z());
    geDet->setPmax(pmax.x(),pmax.y(),pmax.z());
    fGeEvent->geDet.push_back(*geDet);
    TString globprint(Form( "(%f,%f,%f )",  geDet->global.X() , geDet->global.Y() , geDet->global.Z()) );
    TString pminprint(Form( "(%f,%f,%f )",  geDet->pMin.X() , geDet->pMin.Y() , geDet->pMin.Z()) );
    TString pmaxprint(Form( "(%f,%f,%f )",  geDet->pMax.X() , geDet->pMax.Y() , geDet->pMax.Z()) );
    MGLog(routine) << " GGGGGG  created new GeDet id = "  << idet 
      << " global " << globprint << " pmin " << pminprint << " pmax " << pmaxprint << " total # is " << fGeEvent->geDet.size() << endlog; 
    return  Int_t(fGeEvent->geDet.size() -1);
  }

  void lArEventZero() {
    lArEvent.ev=0;
    lArEvent.edep=0;
    lArEvent.PE=0; 
    lArEvent.PVx=0; 
    lArEvent.PVy=0; 
    lArEvent.PVz=0; 
    lArEvent.id=0;    
    lArEvent.e0=0; 
    lArEvent.x0=0; 
    lArEvent.y0=0; 
    lArEvent.z0=0;    
    lArEvent.xf=0; 
    lArEvent.yf=0; 
    lArEvent.zf=0;    
  }

  void printlArEvent() {
    TString mess;
    mess.Form(" ***** lArEvent %i  ****  (%.1f,%.1f,%.1f)",lArEvent.ev,lArEvent.PVx,lArEvent.PVy,lArEvent.PVz);
    MGLog(routine) << mess << endlog;
    mess.Form(" pid %i e0 %.3f first (%.1f,%.1f,%.1f) last (%.1f,%.1f,%.1f) " ,lArEvent.id,lArEvent.e0,
        lArEvent.x0,lArEvent.y0,lArEvent.z0,lArEvent.xf,lArEvent.yf,lArEvent.zf);
    MGLog(routine) << mess << endlog;
    mess.Form(" edep %.3f PE %.3f",lArEvent.edep,lArEvent.PE);
    MGLog(routine) << mess << endlog;
  }


private:
  MGTMCRun          *fMCRun;             // MGDO encapsulation of run-level info 
  MGTMCEventHeader  *fMCEventHeader;     // MGDO encapsulation of event-level info
  MGTMCEventSteps   *fMCEventSteps;      // MGDO encapsulation of steps 
  MGTMCEventSteps   *fMCEventPrimaries;  // MGDO encapsulation of steps

  G4bool firstDecay;
  G4Navigator *navigator; 

  /* for LAr
  *** If the address points to more than one numerical variable, 
  *** we strongly recommend that the variable be sorted in decreasing order of size. 
  */
  struct lArEvent_t {
    double edep;
    double PE;
    double PVx;
    double PVy;
    double PVz;
    double e0;
    double x0;
    double y0;
    double z0;
    double xf;
    double yf;
    double zf;
    int ev;
    int id;
  };
  lArEvent_t lArEvent;

  TGeEvent* fGeEvent;
  TLArEvent* fLArEvent;
  TLArHit* fLArHit;

  const double lArHitLenthCut = 20;  

  // get map files
  const double SiPMQE = 0.164;
  const double scintYield = 42370;
  
  TH3D *hMap;
  TH2D *hMapExterior;

  G4int       fRunID;
  G4int       fNSteps;
  G4int       fNevents;
  G4String    fRunDescription;

  G4bool      fWriteAllSteps;          // Write steps in all volumes.
  G4bool      fWriteAllStepsInEventsThatDepositEnergy; // Write steps in all
                                      // volumes for those events that deposit non-zero energy

  G4bool      fAreSurfaceAreasPrinted; // print surface areas of components

  G4bool fWriteRandGenState;

  G4bool      fKillAlphas;             // Kill all alpha tracks outside sensitive volume after one step.
  G4bool      fKillBetas;              // Kill all beta tracks outside sensitive volume after one step.
  G4bool      fKillGammas;             // Kill all gamma tracks outside sensitive volume after one step.
  G4bool      fKillNeutrons;           // Kill all neutron tracks outside sensitive volume after one step.
  G4bool      fStopNuclei;             // Stop nuclei outside sensitive volume, but don't kill them. This allows them to decay.

  G4UImessenger *fMessenger; 

  // a map of physical volume pointers to sensitive ids:
  std::map<G4VPhysicalVolume*, int> fSensitiveIDOfPhysicalVol;

  // Sensitive volume name - ID pairs are taken from the list stored in fMCRun
  // Can be set e.g. using /MG/io/MCRun/AddSensitiveVolnameID [volname] [ID]
  // In addition, the following methods are provided to give further flexibility
  // for specifying sentivie volume name - ID pairs:
  // kClassic: used historically by MJ. Deprecated.
  // kLabelID: look for volumes named [label][ID].
  // kAskGeom: ask the geometry class using the MGVGeometrySensVolList interface. 
  //   Note: only valid for geometry classes deriving from MGVGeometrySensVolList!
  // kFile: specify a file containing a list of volume name - ID pairs, like this:
  //   # comments starting with "#" less than 1024 chars in length are allowed
  //   volumeName1  1022
  //   volumeName2  2343
  //   ...
  // kManual: the user will specify the sensitive volumes only manually 
  //   (e.g. via the macro command given above). 
  enum ESensitiveIDLabelScheme { kClassic, kLabelID, kAskGeom, kFile, kManual};
  ESensitiveIDLabelScheme fSensitiveIDLabelScheme; 
  std::string fSensitiveIDLabel;
  virtual void ReadSensIDFile(const char* filename);

public:
  virtual void SetSensitiveIDLabelSchemeClassic() { fSensitiveIDLabelScheme = kClassic; }
  virtual void SetSensitiveIDLabelSchemeLabelID(const std::string& label) 
    { fSensitiveIDLabelScheme = kLabelID; fSensitiveIDLabel = label; }
  virtual void SetSensitiveIDLabelSchemeAskGeom() { fSensitiveIDLabelScheme = kAskGeom; }  
  virtual void SetSensitiveIDLabelSchemeFile(const std::string& filename)
    { fSensitiveIDLabelScheme = kFile; ReadSensIDFile(filename.c_str()); }
  virtual void SetSensitiveIDLabelSchemeManual() { fSensitiveIDLabelScheme = kManual; }
};

#endif
