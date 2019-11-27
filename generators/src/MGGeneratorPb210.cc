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
//                                                          
// $Id:
//      
// CLASS IMPLEMENTATION:  MGGeneratorPb210.cc
//
//---------------------------------------------------------------------------//
/**
* SPECIAL NOTES:
*/
// 
//---------------------------------------------------------------------------//
/**
* AUTHOR: A. Stevens
* CONTACT: austinst@physics.unc.edu
* FIRST SUBMISSION: 
* 
* REVISION:
*
*
*/
//---------------------------------------------------------------------------//

#include "Randomize.hh"

#include<vector>
#include<utility> //pair
#include<algorithm> //upper_bound

#include "G4ios.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4ParticleGun.hh"
#include "G4Run.hh"

#include "G4PhysicalVolumeStore.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4AffineTransform.hh"

#include "TMath.h"

#include "generators/MGGeneratorPb210Messenger.hh"
#include "io/MGLogger.hh"

//---------------------------------------------------------------------------//

#include "generators/MGGeneratorPb210.hh" 

//---------------------------------------------------------------------------//

using namespace CLHEP;

MGGeneratorPb210::MGGeneratorPb210()
{
	fGeneratorName = "Pb210";
	fG4Messenger = new MGGeneratorPb210Messenger(this);
	fParticleGun = new G4ParticleGun(1);


	fParticleType = kGamma;
	fIsFirstOrder = true;
	fGenerateXRays = false;
	fGenerateElectrons = false;
	fGenerateSecondOrder = false;
        fUseG4SurfaceSampler = false;
        fRejectBox = nullptr;
        fRejectSphere = nullptr;
        fRejectionRotation = new G4RotationMatrix(0, 0, 0);
        fRejectionOffset = new G4ThreeVector(0, 0, 0);
        fUniformDistribution.SetSeed(0);
}

//---------------------------------------------------------------------------//

MGGeneratorPb210::MGGeneratorPb210(const MGGeneratorPb210 & other) : MGVGenerator(other)
{;}

//---------------------------------------------------------------------------//

MGGeneratorPb210::~MGGeneratorPb210()
{
	delete fG4Messenger;
	delete fParticleGun;
        delete fRejectionRotation;
        delete fRejectionOffset;
        if(fRejectBox) delete fRejectBox;
}

//---------------------------------------------------------------------------//

void MGGeneratorPb210::BeginOfRunAction(const G4Run*)
{
	G4double energyMin = 40*keV;
	G4double energyMax = 1161*keV;

	hFirstOrderPhotonEnergy = new TF1("hFirstOrderPhotonEnergy", this, 
	&MGGeneratorPb210::FirstOrderPhotonEnergyFormula,
	energyMin/keV, energyMax/keV, 0,
	"MGGeneratorPb210",
	"FirstOrderPhotonEnergyFormula");

	hSecondOrderPhotonEnergy = new TF1("hSecondOrderPhotonEnergy", this,
	&MGGeneratorPb210::SecondOrderPhotonEnergyFormula,
	energyMin/keV, energyMax/keV, 0,
	"MGGeneratorPb210",
	"SecondOrderPhotonEnergyFormula");

	hFirstOrderElectronEnergy = new TF1("hFirstOrderElectronEnergy", this, 
	&MGGeneratorPb210::FirstOrderElectronEnergyFormula,
	energyMin/keV, energyMax/keV, 0,
	"MGGeneratorPb210",
	"FirstOrderElectronEnergyFormula");

	hSecondOrderElectronEnergy = new TF1("hSecondOrderElectronEnergy", this,
	&MGGeneratorPb210::SecondOrderElectronEnergyFormula,
	energyMin/keV, energyMax/keV, 0,
	"MGGeneratorPb210",
	"SecondOrderElectronEnergyFormula");

	//Note that the Angular Distribution function depends on the current
	//energy, so hAngularDistribution must be re-created at each event, not
	//each run.
}	

//---------------------------------------------------------------------------//

void MGGeneratorPb210::EndOfRunAction(const G4Run*)
{
	delete hFirstOrderPhotonEnergy;
	delete hSecondOrderPhotonEnergy;
	delete hFirstOrderElectronEnergy;
	delete hSecondOrderElectronEnergy;
}

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::FirstOrderPhotonEnergyFormula(G4double *pEnergy, G4double*)
{	//Units are keV for energy and energyMax
	G4double energy = pEnergy[0];
	G4double temp = 0;
	G4double energyMax = 1161;
	G4double eps = (energy/energyMax); //eps is epsilon

	if (energy < 40)
	temp = 0;

	else if (energy >= 40 && energy < 78.5)
	temp = 2.757 - 180.1*eps + 4107*eps*eps - 27044*eps*eps*eps;

	else if (energy >= 78.5 && energy < 100)
	temp = 7.763 - 143.9*eps + 656.0*eps*eps;

	else if (energy >= 100 && energy <= 1161)
	temp = 1705*eps*eps*eps
		* TMath::Exp(-18.79*eps + 11.82*eps*eps - 11.07*eps*eps*eps);

	else if (energy > 1161)
	temp = 0;

	return temp;
} 

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::SecondOrderPhotonEnergyFormula(G4double *pEnergy, G4double*)
{	//Units are keV for energy and energyMax
	G4double energy = pEnergy[0];
	G4double temp = 0;
	G4double energyMax = 1161;
	G4double eps = (energy/energyMax);	//eps is epsilon

	if (energy < 40)
	temp = 0;

	else if (energy >= 40 && energy < 100)
	temp = 0.8835 * (1 + 10.91*eps - 205.5*eps*eps);

	else if (energy >= 100 && energy <= 1161)
	// Have to multiply by extra factor on next line to match
	// proportions in table 1. For some reason only the 2nd order
	// gammas require this extra factor (everything else is
	// normalized correctly in the paper).
	temp = 3.012*TMath::Exp(-eps/0.07812) * 0.38789;

	else if (energy > 1161)
	temp = 0;

	return temp;
} 

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::FirstOrderElectronEnergyFormula(G4double *pEnergy, G4double*)
{	//Units are keV for energy and energyMax
	G4double energy = pEnergy[0];
	G4double temp = 0;
	G4double energyMax = 1161;
	G4double eps = (energy/energyMax); //eps is epsilon

	if (energy < 40)
	temp = 0;

	else if (energy >= 40 && energy < 100)
	temp = 15.16 * eps - 55.12 * eps * eps;
	else if (energy >= 100 && energy <= 1161)
	temp = 4.321 * TMath::Power(1 - eps, 3) * TMath::Sqrt(eps*(eps + 0.7917));
	else if (energy > 1161)
	temp = 0;

	return temp;
} 

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::SecondOrderElectronEnergyFormula(G4double *pEnergy, G4double*)
{	//Units are keV for energy and energyMax
	G4double energy = pEnergy[0];
	G4double temp = 0;
	G4double energyMax = 1161;
	G4double eps = (energy/energyMax);	//eps is epsilon

	if (energy < 40)
	temp = 0;

	else if (energy >= 40 && energy < 1161)
	temp = 1.715 * TMath::Exp(-eps/0.06388); 

	else if (energy > 1161)
	temp = 0;

	return temp;
} 

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::PhotonAngularDistributionFormula(G4double *pAngle, 
	G4double *par)
{
	G4double angle = pAngle[0];
	G4double energy = par[0] / keV;
	G4double qValue = par[1];
	G4double normalization;
	G4double temp;

        if (energy >= 40 && energy <= 1161) {
	  normalization = TMath::Sin(TMath::ATan(1/TMath::Sqrt(qValue)))
                   * TMath::Power(TMath::Cos(TMath::ATan(1/TMath::Sqrt(qValue))),
	                          qValue);

	  temp = (1 / normalization)
	  * TMath::Power(TMath::Cos(angle), qValue) * TMath::Sin(angle);
	}
	else temp = 0;
	return temp;
} 

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::ElectronAngularDistributionFormula(G4double *pAngle, 
	G4double *par)
{
	G4double angle = pAngle[0];
	G4double energy = par[0] / keV;
	G4double qValue = par[1];
	G4double normalization;
	G4double temp;

        if (energy >= 40 && energy <= 1161) {
	  if(qValue<0) normalization = 1;
	  else {
	    normalization = 0.705 + 0.4657 * qValue
                            + 0.325/TMath::Power(1 + qValue, 2.162);
	  }
	    temp = 1/normalization * (1+qValue*TMath::Power(TMath::Cos(angle),
                                                            1.207))
                   * TMath::Sin(angle);
	}
	else temp = 0;
	return temp;
} 

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::ElectronAngularDistRValue()
{
	G4double energy = fCurrentEnergy / keV;

        //Linear interpolation between these values
        std::vector<std::pair<G4double, G4double>> interp_vals =
          {{40, -0.1046}, {120, -0.0287}, {200, 0.1096}, {280, 0.2838},
           {360, 0.4675}, {440, 0.6297}, {520, 0.8550}, {600, 1.0922},
           {680, 1.2834}, {760, 1.5793}, {840, 1.8319}, {920, 2.2245},
           {1000, 2.7900}, {1080, 5.5404}, {1161, 8.3252}};

        auto up = std::upper_bound(interp_vals.begin(), interp_vals.end(), std::make_pair(energy, 0.0));
        auto low = up - 1;
        G4double x1 = low->first;
        G4double x2 = up->first;
        G4double y1 = low->second;
        G4double y2 = up->second;
        return (y2 - y1)/(x2 - x1)*energy + (y1*x2 - y2*x1)/(x2 - x1);
}

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::FOAngularDistQValue()
{	//energy and energyMax are in keV
	G4double energy = fCurrentEnergy / keV;
	G4double qValue = 0;
	G4double energyMax = 1161;
	G4double eps = (energy/energyMax); //eps is epsilon

	if (fParticleType == kXRay)
	qValue = 1.191;

	else if (fParticleType == kGamma)
	{	
	if (energy < 40)
	qValue = 0;

	else if (energy >= 40 && energy < 100)
	qValue =	1.045;

	else if (energy >= 100 && energy <= 1161)
	qValue =	1.016 + 0.1057 * TMath::Exp( -( eps - 0.06634)/0.1570);

	else if (energy > 1161)
	{
	qValue = 0;
	MGLog(error) << "FOAngularDistQValue: Energy not within 40-1161 keV"
	<< " range, qValue set to 0." << endlog;
	}
	}
        else //fParticleType == kElectron
        {
        qValue = ElectronAngularDistRValue();
        }
	return qValue;
}

//---------------------------------------------------------------------------//

G4double MGGeneratorPb210::SOAngularDistQValue()
{	//Units for energy and energyMax are keV
	G4double energy = fCurrentEnergy/keV;
	G4double qValue = 0;	
	G4double energyMax = 1161;
	G4double eps = (energy/energyMax); //eps is epsilon

	if (fParticleType == kXRay)
	qValue = 0.4416;

	else if (fParticleType == kGamma)
	{
	if (energy < 40)
	qValue = 0;

	else if (energy >= 40 && energy < 203)
	qValue =	0.9133 - 1.757 * eps;

	else if (energy >= 203 && energy <= 1161)
	qValue =	0.6063;

	else if (energy > 1161)
	{
	qValue = 0;
	MGLog(error) << "SOAngularDistQValue: Energy not within 40-1161 keV"
			<< " range, qValue set to 0." << endlog;
	}
	}
        else //fParticleType == kElectron
        {
        qValue = ElectronAngularDistRValue();
        }

	return qValue;
}

//---------------------------------------------------------------------------//

void MGGeneratorPb210::SampleFirstOrderEnergy()
{	
	if(fParticleType == kElectron)
	  fCurrentEnergy = (hFirstOrderElectronEnergy->GetRandom() * keV);
	else
	  fCurrentEnergy = (hFirstOrderPhotonEnergy->GetRandom() * keV);
} 

//---------------------------------------------------------------------------//

void MGGeneratorPb210::SampleSecondOrderEnergy()
{	
	if(fParticleType == kElectron)
	  fCurrentEnergy = (hSecondOrderElectronEnergy->GetRandom() * keV);
	else
	  fCurrentEnergy = (hSecondOrderPhotonEnergy->GetRandom() * keV);
} 

//---------------------------------------------------------------------------//

void MGGeneratorPb210::SampleAngularDistribution()
{	
	fZenithAngle = (hAngularDistribution->GetRandom());
} 

//---------------------------------------------------------------------------//

void MGGeneratorPb210::DirectionDecider()
{
	if(fLogicalPb210Surface == NULL)
	MGLog(error) << "fLogicalPb210Surface not defined for generator; zenithAxis"
	<< "cannot be found.  Use /MG/generator/Pb210/shieldSurface "
	<< "and enter the name of the physical volume sampled by GSS."
	<< endlog;	

	G4double rotationAngle = G4UniformRand() * 2 * TMath::Pi();
	G4ThreeVector zenithAxis;


	zenithAxis = fLogicalPb210Surface->GetSolid()->SurfaceNormal(fCurrentPosition);


	//ensures photons are generated going inward
        if(!fUseG4SurfaceSampler) zenithAxis = zenithAxis * -1;

	/*
	//NOTE: the above line (zenith = zenith*-1) works fine as long as you are 
	//sampling the entire volume that is inside of the lead shield.  If you are
	//sampling a thin dummy volume that just covers the surface of the shield, you
	//may want to use the following line instead:
	if ((fCurrentPosition+zenithAxis).mag() > (fCurrentPosition-zenithAxis).mag())
	zenithAxis = zenithAxis * -1;
	//This should work for simpler geometries (box, box with coldfinger hole, etc)
	//but more complicated dummy surfaces may require this to be rethought.
	*/


	fDirection = zenithAxis;
	fDirection.rotate(fZenithAngle, zenithAxis.orthogonal());
	fDirection.rotate(rotationAngle, zenithAxis);
}

//---------------------------------------------------------------------------//

void MGGeneratorPb210::GeneratePrimaryVertex(G4Event *event)
{
        if(!fUseG4SurfaceSampler) {
          //By the time this is called, MGGeneratorPrimary has already set
          //fCurrentPosition to a random point on the lead shield surface
          //using GSS, as long as a GSS file was set in the macro.  See
          //SampleGenerators.mac.
          if(fCurrentPosition == G4ThreeVector(0,0,0))
          MGLog(error) << "fCurrentPosition is zero.	Check GSS file." << endlog;
        }

        if(fUseG4SurfaceSampler) {
          //Since the Pb shield shape is pretty simple, use built-in G4 surface
          //sampler to generate primary vertices.
          if(fLogicalPb210Surface==nullptr)
          MGLog(error) << "fLogicalPb210Surface not defined for generator; zenithAxis"
          << "cannot be found.  Use /MG/generator/Pb210/shieldSurface "
          << "and enter the name of the physical volume sampled by GSS."
          << endlog;

          G4ThreeVector tempPosition = fLogicalPb210Surface->GetSolid()->GetPointOnSurface();
          if(fRejectBox) {
            //Reject points on the outside of the lead shield. First apply any
            //shift and rotation specified.
            G4AffineTransform* rejectionTransform = new G4AffineTransform(*fRejectionRotation, *fRejectionOffset);
            G4ThreeVector transformedTemp = rejectionTransform->TransformPoint(tempPosition);
            while(    abs(transformedTemp.x())>fRejectBox->x()
                   || abs(transformedTemp.y())>fRejectBox->y()
                   || abs(transformedTemp.z())>fRejectBox->z() ) {
              tempPosition = fLogicalPb210Surface->GetSolid()->GetPointOnSurface();
              transformedTemp = rejectionTransform->TransformPoint(tempPosition);
            }
          }
          else if(fRejectSphere)
            MGLog(error) << "fRejectSphere is not implemented!" << endlog;
          fCurrentPosition = tempPosition;
        }

        //determine first or second order and particle type, and set
        // energy if particle is XRay
        G4double first_order_prob = 1;
        if(fGenerateSecondOrder) first_order_prob = 0.97975;
        G4double FOGamma_prob = first_order_prob * 0.36159;
        G4double FOElectron_prob = 0;
        if(fGenerateElectrons) FOElectron_prob = first_order_prob * 0.58048;
        G4double FOKa2_prob = 0;
        G4double FOKa1_prob = 0;
        G4double FOKb3_prob = 0;
        G4double FOKb1_prob = 0;
        G4double FOKb2a_prob = 0;
        G4double FOKb2b_prob = 0;
        if(fGenerateXRays) {
          FOKa2_prob = first_order_prob * 0.01646;
          FOKa1_prob = first_order_prob * 0.02996;
          FOKb3_prob = first_order_prob * 0.00327;
          FOKb1_prob = first_order_prob * 0.00616;
          FOKb2a_prob = first_order_prob * 0.00069;
          FOKb2b_prob = first_order_prob * 0.00139;
        }
        G4double SOGamma_prob = 0;
        G4double SOElectron_prob = 0;
        G4double SOKa2_prob = 0;
        G4double SOKa1_prob = 0;
        G4double SOKb3_prob = 0;
        G4double SOKb1_prob = 0;
        G4double SOKb2a_prob = 0;
        G4double SOKb2b_prob = 0;
        if(fGenerateSecondOrder) {
            G4double second_order_prob = 1 - first_order_prob;
            SOGamma_prob = second_order_prob * 0.72563;
            if(fGenerateElectrons) SOElectron_prob = second_order_prob * 0.19615;
            if(fGenerateXRays) {
              SOKa2_prob = second_order_prob * 0.02366;
              SOKa1_prob = second_order_prob * 0.04338;
              SOKb3_prob = second_order_prob * 0.00308;
              SOKb1_prob = second_order_prob * 0.00590;
              SOKb2a_prob = second_order_prob * 0.00094;
              SOKb2b_prob = second_order_prob * 0.00126;
            }
        }
        G4double divisor = FOGamma_prob + FOElectron_prob + FOKa2_prob
                        + FOKa1_prob + FOKb3_prob + FOKb1_prob + FOKb2a_prob
                        + FOKb2b_prob + SOGamma_prob + SOElectron_prob
                        + SOKa2_prob + SOKa1_prob + SOKb3_prob + SOKb1_prob
                        + SOKb2a_prob + SOKb2b_prob;
        FOGamma_prob /= divisor;
        FOElectron_prob /= divisor;
        FOKa2_prob /= divisor;
        FOKa1_prob /= divisor;
        FOKb3_prob /= divisor;
        FOKb1_prob /= divisor;
        FOKb2a_prob /= divisor;
        FOKb2b_prob /= divisor;
        SOGamma_prob /= divisor;
        SOElectron_prob /= divisor;
        SOKa2_prob /= divisor;
        SOKa1_prob /= divisor;
        SOKb3_prob /= divisor;
        SOKb1_prob /= divisor;
        SOKb2a_prob /= divisor;
        SOKb2b_prob /= divisor;
        G4double FOGamma_thresh = FOGamma_prob;
        G4double FOElectron_thresh = FOGamma_thresh + FOElectron_prob;
        G4double FOKa2_thresh = FOElectron_thresh + FOKa2_prob;
        G4double FOKa1_thresh = FOKa2_thresh + FOKa1_prob;
        G4double FOKb3_thresh = FOKa1_thresh + FOKb3_prob;
        G4double FOKb1_thresh = FOKb3_thresh + FOKb1_prob;
        G4double FOKb2a_thresh = FOKb1_thresh + FOKb2a_prob;
        G4double FOKb2b_thresh = FOKb2a_thresh + FOKb2b_prob;
        G4double SOGamma_thresh = FOKb2b_thresh + SOGamma_prob;
        G4double SOElectron_thresh = SOGamma_thresh + SOElectron_prob;
        G4double SOKa2_thresh = SOElectron_thresh + SOKa2_prob;
        G4double SOKa1_thresh = SOKa2_thresh + SOKa1_prob;
        G4double SOKb3_thresh = SOKa1_thresh + SOKb3_prob;
        G4double SOKb1_thresh = SOKb3_thresh + SOKb1_prob;
        G4double SOKb2a_thresh = SOKb1_thresh + SOKb2a_prob;
        G4double SOKb2b_thresh = SOKb2a_thresh + SOKb2b_prob;

        G4double rand_uniform = fUniformDistribution.Rndm();
        fCurrentEnergy = 0;
        if(rand_uniform<FOGamma_thresh) {
          fIsFirstOrder = true;
          fParticleType = kGamma;
        }
        else if(rand_uniform>FOGamma_thresh && rand_uniform<FOElectron_thresh) {
          fIsFirstOrder = true;
          fParticleType = kElectron;
        }
        else if(rand_uniform>FOElectron_thresh && rand_uniform<FOKa2_thresh) {
          fIsFirstOrder = true;
          fParticleType = kXRay;
          fCurrentEnergy = 72.804 * keV;
        }
        else if(rand_uniform>FOKa2_thresh && rand_uniform<FOKa1_thresh) {
          fIsFirstOrder = true;
          fParticleType = kXRay;
          fCurrentEnergy = 74.696 * keV;
        }
        else if(rand_uniform>FOKa1_thresh && rand_uniform<FOKb3_thresh) {
          fIsFirstOrder = true;
          fParticleType = kXRay;
          fCurrentEnergy = 84.450 * keV;
        }
        else if(rand_uniform>FOKb3_thresh && rand_uniform<FOKb1_thresh) {
          fIsFirstOrder = true;
          fParticleType = kXRay;
          fCurrentEnergy = 84.938 * keV;
        }
        else if(rand_uniform>FOKb1_thresh && rand_uniform<FOKb2a_thresh) {
          fIsFirstOrder = true;
          fParticleType = kXRay;
          fCurrentEnergy = 87.241 * keV;
        }
        else if(rand_uniform>FOKb2a_thresh && rand_uniform<FOKb2b_thresh) {
          fIsFirstOrder = true;
          fParticleType = kXRay;
          fCurrentEnergy = 87.360 * keV;
        }
        else if(rand_uniform>FOKb2b_thresh && rand_uniform<SOGamma_thresh) {
          fIsFirstOrder = false;
          fParticleType = kGamma;
        }
        else if(rand_uniform>SOGamma_thresh && rand_uniform<SOElectron_thresh) {
          fIsFirstOrder = false;
          fParticleType = kElectron;
        }
        else if(rand_uniform>SOElectron_thresh && rand_uniform<SOKa2_thresh) {
          fIsFirstOrder = false;
          fParticleType = kXRay;
          fCurrentEnergy = 72.804 * keV;
        }
        else if(rand_uniform>SOKa2_thresh && rand_uniform<SOKa1_thresh) {
          fIsFirstOrder = false;
          fParticleType = kXRay;
          fCurrentEnergy = 74.696 * keV;
        }
        else if(rand_uniform>SOKa1_thresh && rand_uniform<SOKb3_thresh) {
          fIsFirstOrder = false;
          fParticleType = kXRay;
          fCurrentEnergy = 84.450 * keV;
        }
        else if(rand_uniform>SOKb3_thresh && rand_uniform<SOKb1_thresh) {
          fIsFirstOrder = false;
          fParticleType = kXRay;
          fCurrentEnergy = 84.938 * keV;
        }
        else if(rand_uniform>SOKb1_thresh && rand_uniform<SOKb2a_thresh) {
          fIsFirstOrder = false;
          fParticleType = kXRay;
          fCurrentEnergy = 87.241 * keV;
        }
        else if(rand_uniform>SOKb2a_thresh && rand_uniform<SOKb2b_thresh) {
          fIsFirstOrder = false;
          fParticleType = kXRay;
          fCurrentEnergy = 87.360 * keV;
        }
        else {
          MGLog(error) << "Unable to determine type of particle generated!" << endlog;
        }

	//set particle definition
	if (fParticleType == kElectron)
	  fParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());
	else
	  fParticleGun->SetParticleDefinition(G4Gamma::GammaDefinition());

	//determine particle energy
        if (fParticleType != kXRay) {
  	  if (fIsFirstOrder == true) {
              SampleFirstOrderEnergy();
          }
	  else {
              SampleSecondOrderEnergy();
          }
        }

	//determine particle zenith angle
	G4double angleMin = 0;
	G4double angleMax = TMath::Pi()/2;
	if (fParticleType == kElectron)
	  hAngularDistribution = new TF1("hAngularDistribution", this,
	  &MGGeneratorPb210::ElectronAngularDistributionFormula,
	  angleMin, angleMax, 2,
	  "MGGeneratorPb210",
	  "ElectronAngularDistributionFormula");
	else
	  hAngularDistribution = new TF1("hAngularDistribution", this,
	  &MGGeneratorPb210::PhotonAngularDistributionFormula,
	  angleMin, angleMax, 2,
	  "MGGeneratorPb210",
	  "PhotonAngularDistributionFormula");
	G4double qValue;	
	if (fIsFirstOrder == true) qValue = FOAngularDistQValue();
	else qValue = SOAngularDistQValue();	
	hAngularDistribution->SetParameters(fCurrentEnergy, qValue);
	hAngularDistribution->SetParNames("EnergyOfParticle","qValue");

	SampleAngularDistribution();
	delete hAngularDistribution;

	//determine particle momentum direction
	DirectionDecider();

	//particle direction, position, and energy sent to ParticleGun
	fParticleGun->SetParticlePosition(fCurrentPosition);
	fParticleGun->SetParticleMomentumDirection(fDirection);
	fParticleGun->SetParticleEnergy(fCurrentEnergy);

	//vertex generated by ParticleGun
	fParticleGun->GeneratePrimaryVertex(event);
}

//---------------------------------------------------------------------------//

void MGGeneratorPb210::SetShieldSurfaceVolume(G4String volumeName)
{
	G4PhysicalVolumeStore* volStore = G4PhysicalVolumeStore::GetInstance();
	bool found = false;
	for(size_t n = 0; n < volStore->size(); n++)
	{
	if((*volStore)[n]->GetName() == volumeName)
	{
	fLogicalPb210Surface = ((*volStore)[n])->GetLogicalVolume();
	found = true;
	}
	}
	if(!found)
	MGLog(error) << "Volume: " << volumeName << " not found in "
	<< "G4PhysicalVolumeStore.  Input the physical volume "
	<< "corresponding to what fLogicalPb210Surface should be."
	<< endlog;
}

