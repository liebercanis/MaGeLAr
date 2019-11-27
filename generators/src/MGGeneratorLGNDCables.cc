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
// $Id: MGGeneratorLGNDCables.cc,v 1.4 2014-07-14 09:24:09 mgmarino Exp $
//
// CLASS IMPLEMENTATION:  MGGeneratorLGNDCables.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: M. Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: Feb 18, 2019
 *
 * REVISION:
 *
 * Feb-2019, Adopted from Calibration Source generator - M. Green
 *
 */
//---------------------------------------------------------------------------//
//

#include <sstream>
#include "Randomize.hh"

#include "G4ios.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4RandomDirection.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
#include "G4Run.hh"
#include "G4ThreeVector.hh"
#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4UIcommandTree.hh"
#include "io/MGLogger.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolume.hh"

//---------------------------------------------------------------------------//

#include "generators/MGGeneratorLGNDCables.hh"
#include "generators/MGGeneratorLGNDCablesMessenger.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;

MGGeneratorLGNDCables::MGGeneratorLGNDCables()
{
	fA = 228;
	fZ = 90;
  fGeneratorName = "LGNDCables";
	fG4Messenger = new MGGeneratorLGNDCablesMessenger(this);
  fParticleGun = new G4ParticleGun(1);
	fNCables = 0;
	fTotalLength = 0.0;

	G4double xpos = 0.0;
  G4double ypos = 0.0;
	G4double zpos = 0.0;
	G4double length = 0.0;
	G4String logVname;

  //MGLog(routine) << "Initialized the generator!" << endlog;

	//get fPositionSampler and lengths of the cables
  G4PhysicalVolumeStore* volumeStore = G4PhysicalVolumeStore::GetInstance();
  G4int nVolumes = (G4int) volumeStore->size();
  G4String candidateList;
  for(G4int i=0;i<nVolumes;i++) {
    candidateList = (*volumeStore)[i]->GetName();
		//MGLog(routine) << candidateList << endlog;
		if(candidateList.contains("HVSigCable")){
			xpos = (*volumeStore)[i]->GetTranslation().getX();
			ypos = (*volumeStore)[i]->GetTranslation().getY();
			zpos = (*volumeStore)[i]->GetTranslation().getZ();
			fPos.push_back(G4ThreeVector(xpos, ypos, zpos));
			logVname = (*volumeStore)[i]->GetLogicalVolume()->GetName();
			//MGLog(routine) << "Cable Located: " << logVname << endlog;
			length = 0.0*mm;
			//MGLog(routine) << logVname.substr(logVname.find("x")+1,std::string::npos) << endlog;
			length = G4UIcommand::ConvertToDouble(logVname.substr(logVname.find("x")+1,std::string::npos).c_str());
      //MGLog(routine) << "Cable Position: " << xpos << " " << ypos << " " << zpos << endlog;
			//MGLog(routine) << "Cable Length: " << length << endlog;
			fLength.push_back(length);
			fTotalLength += length;
			//MGLog(routine) << "Total Length: " << fTotalLength << endlog;
			fLengthCumm.push_back(fTotalLength);
		}
  }
	fNCables = fPos.size();
	//MGLog(routine) << "  Number of Cables: " << fNCables << endlog;
	//MGLog(routine) << "  Total Cable Length: " << fTotalLength << endlog;
}

//---------------------------------------------------------------------------//

MGGeneratorLGNDCables::MGGeneratorLGNDCables(const MGGeneratorLGNDCables & other) : MGVGenerator(other)
{;}

//---------------------------------------------------------------------------//

MGGeneratorLGNDCables::~MGGeneratorLGNDCables()
{
  delete fParticleGun;
}

//---------------------------------------------------------------------------//

void MGGeneratorLGNDCables::BeginOfRunAction(G4Run const*)
{
  Dump();
}

//---------------------------------------------------------------------------//

void MGGeneratorLGNDCables::Dump()
{
  MGLog(routine) << "-------------------------------------------" << endlog;
  MGLog(routine) << "  LGND Cable Source Parameters:" << endlog;
  MGLog(routine) << "  Ion Z: " << fZ << endlog;
  MGLog(routine) << "  Ion A: " << fA << endlog;
	MGLog(routine) << "  Number of Cables: " << fNCables << endlog;
	MGLog(routine) << "  Total Cable Length: " << fTotalLength << endlog;
  MGLog(routine) << "-------------------------------------------" << endlog;
}

//---------------------------------------------------------------------------//

void MGGeneratorLGNDCables::EndOfRunAction(G4Run const*)
{;}

//---------------------------------------------------------------------------//

void MGGeneratorLGNDCables::GeneratePrimaryVertex(G4Event *event)
{
	G4ThreeVector fStartPosition;

	//Fix this later - radius hard-coded here and in LGND_HVSigCable.
  G4double radius = 0.1*mm;
  G4double xvalue = radius*(2*G4UniformRand()-1);
  G4double yvalue = radius*(2*G4UniformRand()-1);
	while(xvalue*xvalue+yvalue*yvalue > radius*radius){
      xvalue = radius*(2*G4UniformRand()-1);
      yvalue = radius*(2*G4UniformRand()-1);
  }

	//Select a cable and primary z position by comparing fLengthCumm to fTotalLength:
	G4double pos_overall = fTotalLength * G4UniformRand();
  int i = 0;
	while (pos_overall > fLengthCumm.at(i)) {i++;}
  G4double zvalue = 0;
	if (i == 0){
	    zvalue = pos_overall;
	}
	else {
		  zvalue = pos_overall - fLengthCumm.at(i-1);
	}
  //MGLog(routine) << "Cable i: " << i << endlog;
	//MGLog(routine) << "Pos_overall: " << pos_overall << endlog;
	//MGLog(routine) << "fLengthCumm: " << fLengthCumm.at(i) << endlog;
	//MGLog(routine) << "z value: " << zvalue << endlog;


	fStartPosition.setX(fPos.at(i).x() + xvalue);
	fStartPosition.setY(fPos.at(i).y() + yvalue);
	fStartPosition.setZ(fPos.at(i).z() - zvalue);


  G4IonTable *theIonTable =
    (G4IonTable*)(G4ParticleTable::GetParticleTable()->GetIonTable());
  G4ParticleDefinition *aIon = theIonTable->GetIon(fZ, fA);
  fParticleGun->SetParticleDefinition(aIon);
  fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
  fParticleGun->SetParticleEnergy(0.0);
  fParticleGun->SetParticlePosition(fStartPosition);
  fParticleGun->GeneratePrimaryVertex(event);
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
