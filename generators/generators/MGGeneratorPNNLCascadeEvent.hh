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
// $Id: MGGeneratorPNNLCascadeEvent.hh,v 1.1 2004-12-07 08:45:48 pandola Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// File:        MGGeneratorPNNLCascadeEvent.hh
// Description: Simple cascade parameter storage class for PNNL radiactive 
//              decay model
// Version:     1.0
// Created:     2004-04-23
// Author:      David Jordan
// mail:        david.jordan@pnl.gov
// phone:       509-376-0115

#ifndef MGGeneratorPNNLCascadeEvent_h
#define MGGeneratorPNNLCascadeEvent_h 1

#include "generators/MGGeneratorPNNLCascade.hh"
#include "generators/MGGeneratorPNNLLookup.hh"
#include "globals.hh"

// DVJ 24-Apr-04
// Storage class for kinematic parameters relevant to a single "cascade event"
// as generated by the DoCascadeEvent() method of an object of type 
// MGGeneratorPNNLCascade.  A "CascadeEvent" object is distinguished from the
// "Cascade" object that generates it in that the Event consists of a 
// specific value of the charged particle energy as sampled (for example) from
// a beta spectrum.  The "Cascade" object contains all parameters relevant
// to setting up and sampling from the spectrum.  Coming along for the ride
// are the number of gammas contained in the cascade and their energies, 
// which are simply retrieved from the Cascade object and stored in the
// CascadeEvent object.  Accesor methods are available for retrieving all
// of the relevant energies and the index number of the cascade.  The latter
// refers to the (zero-offset) order of the cascade in a list of Cascade
// objects contained in a single MGGeneratorPNNLRadioisotope object.  This
// index can be used for diagnostic checks on operation of the cascade
// sampling in the Radioisotope object.
//
// Currently all of the "action" is in the Set and Get methods.  Constructors
// are trivial, and just set the values of the member variables.


class MGGeneratorPNNLCascadeEvent 
{
  public:
    MGGeneratorPNNLCascadeEvent();
    MGGeneratorPNNLCascadeEvent(G4int indx_cascade, 
				G4double E_charged_particle, 
				G4int num_gammas, G4double* pGammaList);
    MGGeneratorPNNLCascadeEvent(const MGGeneratorPNNLCascadeEvent& 
				CascadeEvent);
    ~MGGeneratorPNNLCascadeEvent();
    void operator=(const MGGeneratorPNNLCascadeEvent& CascadeEvent);

    void SetCascadeIndex(G4int index_cascade) {
                                        fIndex_cascade = index_cascade; };
    void SetChargedParticleE(G4double E_charged_particle)  
                            {fE_charged_particle = E_charged_particle;  };
    void SetNumGammas(G4int num_gammas)     {fNum_gammas = num_gammas;  };
    void SetGammaList(G4double* pGammaList) {f_pGammaList = pGammaList; };

    G4int      GetCascadeIndex()     const {return fIndex_cascade;      };
    G4double   GetChargedParticleE() const {return fE_charged_particle; };
    G4int      GetNumGammas()        const {return fNum_gammas;         };
    G4double*  GetGammaList()        const {return f_pGammaList;        };
 
  private:
    G4int     fIndex_cascade;
    G4double  fE_charged_particle;
    G4int     fNum_gammas;
    G4double* f_pGammaList;
};

#endif


