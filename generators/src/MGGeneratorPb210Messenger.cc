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
// $Id: MGGeneratorPb210Messenger.cc,v 1.0 2009/5/17
//      
// CLASS IMPLEMENTATION:  MGGeneratorPb210Messenger.cc
//
//---------------------------------------------------------------------------//
/**
* SPECIAL NOTES:
* 
*
*/
// 
//---------------------------------------------------------------------------//
/**
* AUTHOR: A. Stevens.
* CONTACT: austisnt@physics.unc.edu
* FIRST SUBMISSION:
* 
* REVISION:
*
* 
*/
//---------------------------------------------------------------------------//
//

#include "globals.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIdirectory.hh"

#include "generators/MGGeneratorPb210.hh"

//---------------------------------------------------------------------------//

#include "generators/MGGeneratorPb210Messenger.hh"

//---------------------------------------------------------------------------//

MGGeneratorPb210Messenger::MGGeneratorPb210Messenger(MGGeneratorPb210 *generator) : fPb210Generator(generator)
{
	// /MG/generator/Pb210
	fPb210Directory = new G4UIdirectory("/MG/generator/Pb210/");
	fPb210Directory->SetGuidance("Lead shield decay generator control.");

	// MG/generator/Pb210/shieldSurface
	fSetSurfaceVolumeCmd = new G4UIcmdWithAString("/MG/generator/Pb210/shieldSurface", this);
	fSetSurfaceVolumeCmd->SetGuidance("Volume representing the surface of the lead shield");
	fSetSurfaceVolumeCmd->SetParameterName("VolumeName", false);
	fSetSurfaceVolumeCmd->AvailableForStates(G4State_Idle);

	// /MG/generator/Pb210/generateSecondOrder
        fGenerateSecondOrderCmd = new G4UIcmdWithABool("/MG/generator/Pb210/generateSecondOrder", this);
	fGenerateSecondOrderCmd->SetGuidance("Set this flag to true if you want to generate second order particles from the shield. Default is true.");
	fGenerateSecondOrderCmd->SetParameterName("GenerateSecondOrderCmd", true);
	fGenerateSecondOrderCmd->AvailableForStates(G4State_Idle);

	// /MG/generator/Pb210/generateXRays
        fGenerateXRaysCmd = new G4UIcmdWithABool("/MG/generator/Pb210/generateXRays", this);
	fGenerateXRaysCmd->SetGuidance("Set this flag to true if you want to generate XRays from the shield. Default is false.");
	fGenerateXRaysCmd->SetParameterName("GenerateXRaysCmd", false);
	fGenerateXRaysCmd->AvailableForStates(G4State_Idle);

	// /MG/generator/Pb210/generateElectrons
        fGenerateElectronsCmd = new G4UIcmdWithABool("/MG/generator/Pb210/generateElectrons", this);
	fGenerateElectronsCmd->SetGuidance("Set this flag to true if you want to generate electrons from the shield. Default is false.");
	fGenerateElectronsCmd->SetParameterName("GenerateElectronsCmd", false);
	fGenerateElectronsCmd->AvailableForStates(G4State_Idle);

        // /MG/generator/Pb210/useG4SurfaceSampler
        fUseG4SurfaceSamplerCmd = new G4UIcmdWithABool("/MG/generator/Pb210/useG4SurfaceSampler", this);
        fUseG4SurfaceSamplerCmd->SetGuidance("Set this flag to true if you want to use the built-in G4 surface sampler instead of the general surface sampler. For simple shield shapes it is much faster than GSS.");
        fUseG4SurfaceSamplerCmd->SetParameterName("UseG4SurfaceSampler", false);
        fUseG4SurfaceSamplerCmd->AvailableForStates(G4State_Idle);

        // /MG/generator/Pb210/rejectBox
        fRejectBoxCmd = new G4UIcmdWith3VectorAndUnit("/MG/generator/Pb210/rejectBox",this);
        fRejectBoxCmd->SetGuidance("Set XYZ coordinates beyond which to reject points on the surface of the Pb shield. Rejects points based on absolute value.");
        fRejectBoxCmd->SetParameterName("X","Y","Z",true,true);
        fRejectBoxCmd->SetDefaultUnit("mm");
        fRejectBoxCmd->SetUnitCategory("Length");
        fRejectBoxCmd->SetUnitCandidates("micrometer um mm cm m");

        // /MG/generator/Pb210/rejectionOffset
        fRejectionOffsetCmd = new G4UIcmdWith3VectorAndUnit("/MG/generator/Pb210/rejectionOffset",this);
        fRejectionOffsetCmd->SetGuidance("Set XYZ coordinates for offset of box rejection region.");
        fRejectionOffsetCmd->SetParameterName("X","Y","Z",true,true);
        fRejectionOffsetCmd->SetDefaultUnit("mm");
        fRejectionOffsetCmd->SetUnitCategory("Length");
        fRejectionOffsetCmd->SetUnitCandidates("micrometer um mm cm m");

        // /MG/generator/Pb210/rejectionRotation
        fRejectionRotationCmd = new G4UIcmdWith3VectorAndUnit("/MG/generator/Pb210/rejectionRotation",this);
        fRejectionRotationCmd->SetGuidance("Set PhiThetaPsi coordinates for rotation of box rejection region. This is currently implemented as the inverse of the supplied rotation.");
        fRejectionRotationCmd->SetParameterName("Phi","Theta","Psi",true,true);
        fRejectionRotationCmd->SetDefaultUnit("radian");
        fRejectionRotationCmd->SetUnitCategory("Angle");
        fRejectionRotationCmd->SetUnitCandidates("radian rad degree");
}

//---------------------------------------------------------------------------//

MGGeneratorPb210Messenger::MGGeneratorPb210Messenger(const MGGeneratorPb210Messenger & other) : G4UImessenger(other)
{;}

//---------------------------------------------------------------------------//

MGGeneratorPb210Messenger::~MGGeneratorPb210Messenger()
{
	delete fSetSurfaceVolumeCmd;
	delete fPb210Directory;
        delete fGenerateSecondOrderCmd;
        delete fGenerateXRaysCmd;
        delete fGenerateElectronsCmd;
        delete fUseG4SurfaceSamplerCmd;
        delete fRejectBoxCmd;
        delete fRejectionOffsetCmd;
        delete fRejectionRotationCmd;
}

//---------------------------------------------------------------------------//

void MGGeneratorPb210Messenger::SetNewValue(G4UIcommand *cmd, G4String str)
{
	if( cmd == fSetSurfaceVolumeCmd )
	fPb210Generator->SetShieldSurfaceVolume(str);

        else if( cmd == fGenerateSecondOrderCmd )
        fPb210Generator->GenerateSecondOrder(fGenerateSecondOrderCmd->GetNewBoolValue(str));

        else if( cmd == fGenerateXRaysCmd )
        fPb210Generator->GenerateXRays(fGenerateXRaysCmd->GetNewBoolValue(str));

        else if( cmd == fGenerateElectronsCmd )
        fPb210Generator->GenerateElectrons(fGenerateElectronsCmd->GetNewBoolValue(str));

        else if( cmd == fUseG4SurfaceSamplerCmd )
        fPb210Generator->UseG4SurfaceSampler(fUseG4SurfaceSamplerCmd->GetNewBoolValue(str));

        else if( cmd == fRejectBoxCmd )
        fPb210Generator->RejectPointsOutsideBox(fRejectBoxCmd->GetNew3VectorValue(str));

        else if( cmd == fRejectionOffsetCmd )
        fPb210Generator->SetRejectionOffset(fRejectionOffsetCmd->GetNew3VectorValue(str));

        else if( cmd == fRejectionRotationCmd )
        fPb210Generator->SetRejectionRotation(fRejectionRotationCmd->GetNew3VectorValue(str));
}
