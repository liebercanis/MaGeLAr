//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//                                                                           //
//                            MaGe Simulation                                //
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
//---------------------------------------------------------------------------//
//
//---------------------------------------------------------------------------//
/**
 *
 * AUTHOR:  Nuno Barros
 * CONTACT: @CONTACT@
 * FIRST SUBMISSION: 05-22-2012
 * DESCRIPTION: Implements the sensitive detector for the LAr Instrumentation.
 *
 *
 * REVISION:
 *    18-07-2012, N. Barros, Updated G4Exception call to keep compatibility with geant4 9.5
 *    19-09-2012, N. Barros, Updated class to pre-register the sensitive volumes.
 *
 *
 */
//---------------------------------------------------------------------------//
//



#include "gerdageometry/GEGeometryLArInstSD.hh"
#include "gerdageometry/GEGeometryLArInstSDHit.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include "G4OpticalPhoton.hh"

#include "io/MGLogger.hh"



GEGeometryLArInstSD::GEGeometryLArInstSD(G4String name, G4String colName)
:G4VSensitiveDetector(name)
{
	MGLog(debugging) << "Building LAr Inst with name " << colName << " attached to sensitive detector " << name <<  endlog;
	collectionName.insert(colName);
}

GEGeometryLArInstSD::~GEGeometryLArInstSD()
{;}

void GEGeometryLArInstSD::Initialize(G4HCofThisEvent* HCE)
{
	for (G4int i = 0; i < (G4int)collectionName.size(); ++i) {
		G4int HCID = -1;
		fHitCollection = new GEGeometryLArInstSDHitsCollection
			(SensitiveDetectorName,collectionName[i]);

		if (HCID < 0) {
			HCID = GetCollectionID(i);
		}
		HCE->AddHitsCollection(HCID,fHitCollection);
		MGLog(debugging) << "Initialized hits collection: " << collectionName[i] << endlog;
	}
}

G4bool GEGeometryLArInstSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
	// optical photon?
	G4ParticleDefinition* particleType = aStep->GetTrack()->GetDefinition();
	if(particleType != G4OpticalPhoton::OpticalPhotonDefinition()) return false;

	// this is actually irrelevant as optical photons do not truly carry the energy deposited
	G4double eph = aStep->GetTrack()->GetTotalEnergy(); /// This yeidls the photon wavelength (in energy units)
	if( eph <= 0. ) return false;

	// Get the physical volume of the detection point (post step)
	// a step starts at PreStepPoint and ends at PostStepPoint
	// if a boundary is reached the PostStepPoint belongs logically to the next volume 
    // as we write down the hit when the photon reaches the boundary we 
    // need to check the PostStepPoint here 
	const G4VPhysicalVolume* physVol = aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
	G4String name = physVol->GetLogicalVolume()->GetName();

	// Check if PostStepVolume has a SensitiveDetector attached
	// If not skip
	if(!physVol->GetLogicalVolume()->GetSensitiveDetector()) {
		MGLog(debugging) << "PostStep volume NOT defined as SD " << name << endlog;
		return false;
	}

	// Get copy number -- uniquely identifies the physical volume being hit
	G4int partNumber = aStep->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();
	G4int copyID = physVol->GetCopyNo();

	// Do a crosscheck. We have a low enough number of hits that we can afford to make this check.
	if (copyID != partNumber) {
		std::ostringstream msg;
		msg << "Something is wrong with the LArInst part number"  << partNumber << " <> " << copyID << ".\n" << std::endl;
		G4Exception("GEGeometryLArInstSD::ProcessHits","IdMismatch",FatalErrorInArgument,msg.str().c_str());
		return false;
	}

	/**
	 * Identification of the LAr Instrumentation part number
	 *
	 * The part number must be identifiable by the logical volume and the physical copy number
	 * part_id = logical_code * 100 + copy_number
	 *
	 * The parts are registered at construction level
	 * and get the correct code out of it.
	 */
	it_logicCode = logicCodeParts.find(name);

	if (it_logicCode == logicCodeParts.end()) {
		// If the part number was not previously registered then there is something wrong here. Better to exit
    	std::ostringstream msg;
    	msg << "Something is wrong with the LArInst part number. PV " << physVol->GetName() << " LV " << name << " CopyNo "<< partNumber << " <> " << copyID << ".\n" << std::endl;
    	G4Exception("GEGeometryLArInstSD::ProcessHits","PartMismatch",FatalErrorInArgument,msg.str().c_str());
    	return false;
	}

	// write hit to disk
	GEGeometryLArInstSDHit* theHit = new GEGeometryLArInstSDHit(physVol->GetLogicalVolume());

	partNumber = logicCodeParts[name] + copyID;

	theHit->SetEnergy(eph); /// In reality this is the wavelength
	theHit->SetHittime(aStep->GetTrack()->GetGlobalTime());
	theHit->SetPart(partNumber);
	theHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
	theHit->SetPartName(physVol->GetName());
	theHit->SetParticleDirection((aStep->GetPreStepPoint())->GetMomentumDirection());

	fHitCollection->insert( theHit );

	return true;
}

G4bool GEGeometryLArInstSD::ProcessHits_constStep(const G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
	G4Step *theStep = const_cast<G4Step*>(aStep);
	return this->ProcessHits(theStep,NULL);
}

// One can use the logical volumes and the number of instances to register the map
void GEGeometryLArInstSD::RegisterDetectorInstances(G4LogicalVolume *log_vol) {
  // Search for the logical volume name. The low end part of the code comes from the copy number in
  // the physical volume
  // the logicCode is just the global code for each "cluster of instrumentation"
  it_logicCode = logicCodeParts.find(log_vol->GetName());
  if (it_logicCode == logicCodeParts.end()) {
    G4int d = 1 + logicCodeParts.size();
    logicCodeParts[log_vol->GetName()] = 100 * d;
  }
}

void GEGeometryLArInstSD::EndOfEvent(G4HCofThisEvent*)
{;}

void GEGeometryLArInstSD::clear()
{;}

void GEGeometryLArInstSD::DrawAll()
{;}

void GEGeometryLArInstSD::PrintAll()
{;}




