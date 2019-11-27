//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//                                                                           //
//                                                                           //
//                         MaGe Simulation                                   //
//                                                                           //
//      This code implementation is the intellectual property of the         //
//      MAJORANA and Gerda Collaborations. It is based on Geant4, an         //
//      intellectual property of the RD44 GEANT4 collaboration.              //
//                                                                           //
//                        *********************                              //
//                                                                           //
//    Neither the authors of this software system, nor their employing       //
//    institutes, nor the agencies providing financial support for this      //
//    work  make  any representation or  warranty, express or implied,       //
//    regarding this software system or assume any liability for its use.    //
//    By copying, distributing or modifying the Program (or any work based   //
//    on on the Program) you indicate your acceptance of this statement,     //
//    and all its terms.                                                     //
//                                                                           //
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//---------------------------------------------------------------------------//
/**                                                            
* $Id:
*      
* CLASS DECLARATION:  MGGeneratorPb210.hh
*
*---------------------------------------------------------------------------//
*
* DESCRIPTION: 
*
*/ 
// Begin description of class here
/**
*
* Generates gammas as from Pb210 shielding; constructs root TF1 functions
* and TH1F histograms to sample energy, zenith angle, and origin, then
* produces a gamma at a random point on the lead shield, with the chosen
* zenith angle and energy.
* Currently, the simulator can produce second order photons, but will always
* produce first order photons.
* Based on Pavol Vojtyla, Fast computer simulations of background of low-level
* Ge γ-spectrometers induced by 210Pb/210Bi in shielding lead; NUCL INSTRUM METH
* B; 117, 1 August 1996, Pages 189-198.
* http://dx.doi.org/10.1016/0168-583X(96)00275-3
* 
*
*/
// End class description
//
/**  
* SPECIAL NOTES:
* Using this class requires GSS.  The macro macros/Pb210Generator_BEGE.mac
* shows an example of how to use GSS with this class.
*
*/
// 
// --------------------------------------------------------------------------//
/** 
* AUTHOR: A. Stevens
* CONTACT: paddy@physics.unc.edu
* FIRST SUBMISSION:
* 
* REVISION:
* 
*/
// --------------------------------------------------------------------------//

#ifndef _MGGENERATORPB210_HH
#define _MGGENERATORPB210_HH

//---------------------------------------------------------------------------//

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"

#include "TF1.h"
#include "TH1F.h"
#include "TRandom3.h"

#include "generators/MGVGenerator.hh"

//---------------------------------------------------------------------------//

class G4Event;
class G4Messenger;
class G4ParticleGun;
class G4Run;

class MGGeneratorPb210 : public MGVGenerator
{
public:
        enum EParticleType { kGamma = 0, kElectron = 1, kXRay = 2 };
public:

	//default constructor
	MGGeneratorPb210();

	//copy constructor
	MGGeneratorPb210(const MGGeneratorPb210 &);

	//destructor
	~MGGeneratorPb210();

	//public interface
	void BeginOfEventAction(G4Event *event);
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);
	void GeneratePrimaryVertex(G4Event *event);

	//this method is important for GSS
	void SetParticlePosition(G4ThreeVector pos) {fCurrentPosition = pos;}

	//function determines the direction of particle based on zenith angle
	void DirectionDecider();

	//energy/anglular distribution functions, passed to root function constructors
	G4double FirstOrderPhotonEnergyFormula(G4double *energy, G4double *parameters);
	G4double SecondOrderPhotonEnergyFormula(G4double *energy, G4double *parameters);
	G4double PhotonAngularDistributionFormula(G4double *angle, G4double *parameters);
	G4double FirstOrderElectronEnergyFormula(G4double *energy, G4double *parameters);
	G4double SecondOrderElectronEnergyFormula(G4double *energy, G4double *parameters);
	G4double ElectronAngularDistributionFormula(G4double *angle, G4double *parameters);
	G4double FOAngularDistQValue();	//specific to first order gammas/xrays
	G4double SOAngularDistQValue();	//specific to second order gammas/xrays
	G4double ElectronAngularDistRValue(); //for both orders
	//energy/angular distribution samplers
	void SampleFirstOrderEnergy();
	void SampleSecondOrderEnergy();
	void SampleAngularDistribution();

	//Control functions for which kind of particles to generate
	void GenerateSecondOrder(G4bool val=true)
	  { fGenerateSecondOrder = val; }
	void GenerateXRays(G4bool val=false)
	  { fGenerateXRays = val; }
	void GenerateElectrons(G4bool val=false)
	  { fGenerateElectrons = val; }

	//important for generator's ability to determine the zenith axis
	void SetShieldSurfaceVolume(G4String volumeName);
	G4LogicalVolume* GetShieldSurfaceVolume() {return fLogicalPb210Surface;} 

        void UseG4SurfaceSampler(G4bool aBool)
          { fUseG4SurfaceSampler = aBool; }
        void RejectPointsOutsideBox(G4ThreeVector vec)
          { if(fRejectBox) delete fRejectBox;
            fRejectBox = new G4ThreeVector(vec); }
        void SetRejectionOffset(G4ThreeVector vec)
          { if(fRejectionOffset) delete fRejectionOffset;
            fRejectionOffset = new G4ThreeVector(-1*vec); }
        //There's no G4UIcommand to supply a rotation matrix, so we get a vector
        //instead and pretend it's a set of Euler angles
        void SetRejectionRotation(G4ThreeVector rot)
          { fRejectionRotation->set(rot.x(), rot.y(), rot.z()); }
	//protected members
protected:

	//private  members
private:
	G4ParticleGun*	fParticleGun;

	//particle properties
	G4double	fCurrentEnergy;	// energy of current particle
	G4ThreeVector	fCurrentPosition; // current position of particle
	G4double	fZenithAngle; //angle between fDirection and zenith
	G4ThreeVector	fDirection;	// direction of momentum   

	//used to determine direction of normal axis
	G4LogicalVolume*	fLogicalPb210Surface;

	//Temporarily, fIsXRay is always false
	EParticleType fParticleType;	//true if current particle is an X-ray,
	//which affects angular distribution
	G4bool	fIsFirstOrder;	//true if current particle is
	//first order, false if second order
	// Generators to determine first or second order
	TRandom3 fUniformDistribution;
	G4bool fGenerateXRays;
	G4bool fGenerateElectrons;
	G4bool fGenerateSecondOrder;

        G4bool fUseG4SurfaceSampler;
        G4ThreeVector* fRejectBox;
        G4ThreeVector* fRejectSphere;
        G4RotationMatrix* fRejectionRotation;
        G4ThreeVector* fRejectionOffset;

	//energy/angular Distribution Functions
	TF1*	hFirstOrderPhotonEnergy;
	TF1*	hSecondOrderPhotonEnergy;
	TF1*	hFirstOrderElectronEnergy;
	TF1*	hSecondOrderElectronEnergy;
	TF1*	hAngularDistribution;
};
#endif

