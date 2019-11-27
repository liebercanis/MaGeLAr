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
// $Id: MGcodeTemplate.cc,v 1.1 2004-12-09 08:58:35 pandola Exp $
//
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Neil McFadden
 * CONTACT: nmcfadde@unm.edu
 * FIRST SUBMISSION: 
 Luigi Perdorti
 *
 * REVISION:
 *
 */
//---------------------------------------------------------------------------//
//


#include "legendgeometry/LGND_200_OpticalSurfaces.hh"
#include "io/MGLogger.hh"

// Geant4
#include "globals.hh"
#include "G4Material.hh"

using namespace CLHEP;
const G4double LGND_200_OpticalSurfaces::LambdaE = twopi *1.973269602e-16 * m * GeV;

std::map<std::string, G4OpticalSurface*> LGND_200_OpticalSurfaces::fOpticalSurfaces;

LGND_200_OpticalSurfaces::LGND_200_OpticalSurfaces() {

  MGLog(routine) << "Initializing optical surfaces" << endlog;


  /////////////////////////////////
  // Initialize optical surfaces //
  /////////////////////////////////

  G4String               name;
  G4OpticalSurfaceModel  model;
  G4OpticalSurfaceFinish finish;
  G4SurfaceType          surface_type;
  G4double               smoothness;

  std::string surf_name;

  // interface between TPB and LAr =======================================================================
  surf_name = "LArToTPB";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_dielectric,
      smoothness   = .5
    )
  );

  // interface between TPB and Nylon =======================================================================
  surf_name = "TPBToNylon";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
      G4Material::GetMaterial("TPBOnNylon")->GetMaterialPropertiesTable());
  
  surf_name = "Nylon";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Nylon")->GetMaterialPropertiesTable());
  
  // interface between Teflon and LAr ====================================================================
  surf_name = "LArToTeflon";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Teflon")->GetMaterialPropertiesTable());

  // interface between VM2000 and TPB ====================================================================
  surf_name = "TPBToVM2000";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = polishedfrontpainted, // only specular spike reflection
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("VM2000")->GetMaterialPropertiesTable());

  // interface between VM2000 and LAr ====================================================================
  surf_name = "LArToVM2000";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = polishedfrontpainted, // only specular spike reflection
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("VM2000")->GetMaterialPropertiesTable());

  // interface between Tetratex and TPB ====================================================================
  surf_name = "TPBToTetratex";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = groundfrontpainted, // only lambertian spike reflection
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Tetratex")->GetMaterialPropertiesTable());

  // Fiber reflective end =============================================================================
  // The reflective end will be a reflective surface between the fibers and the lower shroud
  surf_name = "FiberEndToLAr";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal
    )
  );

  const G4int num = 4;
  G4double Wavelength            [num] = {100, 200, 301, 650};
  G4double ReflFiberPhotonEnergy [num];
  G4double ReflFiberReflectivity [num];
  G4double ReflFiberEfficiency   [num];

  MGLog(debugging) << "Fiber reflective surface : " << endlog;
  for (G4int i=0; i < num; i++) {
    // Assume similar reflectivity as the VM2000
    ReflFiberPhotonEnergy[i] = LambdaE/(Wavelength[(num-1)-i]*nm);
    // Set the reflectivity in the fibers to zero,
    // otherwise 99.999 % is reflected due to index of refraction
    ReflFiberReflectivity[i] = 0.98;
    ReflFiberEfficiency[i]   = 0.0;

    MGLog(debugging) << "WL " << Wavelength[(num-1)-i]
                     << " nm En " << ReflFiberPhotonEnergy[i]/MeV
                     << " MeV Refl : " << ReflFiberReflectivity[i]
                     << " Eff " << ReflFiberEfficiency[i] << endlog;
  }

  auto MPTable = new G4MaterialPropertiesTable();
  MPTable->AddProperty("REFLECTIVITY", ReflFiberPhotonEnergy, ReflFiberReflectivity, num);
  MPTable->AddProperty("EFFICIENCY",   ReflFiberPhotonEnergy, ReflFiberEfficiency,   num);

  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(MPTable);
  
  // "Black" surface =============================================================================
  // Nice to have to make sure optical surfaces are behaving
  surf_name = "Black";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal
    )
  );

  G4double BlackPhotonEnergy [num];
  G4double BlackReflectivity [num];
  G4double BlackEfficiency   [num];

  MGLog(debugging) << "Fiber reflective surface : " << endlog;
  for (G4int i=0; i < num; i++) {
    BlackPhotonEnergy[i] = LambdaE/(Wavelength[(num-1)-i]*nm);
    BlackReflectivity[i] = 0.0;
    BlackEfficiency[i]   = 0.0;

    MGLog(debugging) << "WL " << Wavelength[(num-1)-i]
                     << " nm En " << BlackPhotonEnergy[i]/MeV
                     << " MeV Refl : " << BlackReflectivity[i]
                     << " Eff " << BlackEfficiency[i] << endlog;
  }

  auto BlackTable = new G4MaterialPropertiesTable();
  BlackTable->AddProperty("REFLECTIVITY", BlackPhotonEnergy, BlackReflectivity, num);
  BlackTable->AddProperty("EFFICIENCY",   BlackPhotonEnergy, BlackEfficiency,   num);

  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(BlackTable);

  // interface between SiPM and fibers ====================================================================
  // SiPM "sensitive" surface.. this will be a border surface between the fibers and the upper shroud
  // Set sensitivity to 100% to collect all photons and correct for Q.E. off line 
  // -N. McFadden 
  surf_name = "FiberToSiPM";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal
    )
  );
   const G4int npoints_eff = 10;
  G4double SiPMWL[npoints_eff] = {100.*nm,280.*nm,310.*nm,350.*nm,400.*nm,435.*nm,505.*nm,525.*nm,595.*nm,670.*nm};
  G4double SiPMEfficiency[npoints_eff] =   {0.0,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00};
  G4double SiPMReflectivity[npoints_eff];// = {0.0,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00};
  G4double SiPMPhotonEnergy[npoints_eff];
  for (G4int ji=0; ji < npoints_eff; ji++){
    // Zero reflectivity and 1.0 efficiency means that the
    // photons are all "absorbed and identified as hits"
    SiPMPhotonEnergy[ji] = LambdaE/(SiPMWL[(npoints_eff-1)-ji]);
    SiPMReflectivity[ji] = 0.0; // Set the reflectivity in the fibers to zero, otherwise 99.999 % is reflected due to index of refraction
    SiPMEfficiency[ji] = SiPMEfficiency[(npoints_eff-1)-ji]; // Quantum efficiency of the SiPM. 
    MGLog(debugging) << "WL " << SiPMEfficiency[(npoints_eff-1)-ji]
                     << " nm En " << SiPMPhotonEnergy[ji]/MeV << " MeV Refl : "
                     << SiPMReflectivity[ji] << " Eff " << SiPMEfficiency[ji] << endlog;

  }
  auto sipmOptTable = new G4MaterialPropertiesTable();
  sipmOptTable->AddProperty("EFFICIENCY",SiPMPhotonEnergy,SiPMEfficiency,npoints_eff);
  sipmOptTable->AddProperty("REFLECTIVITY",SiPMPhotonEnergy,SiPMReflectivity,npoints_eff);
  
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(sipmOptTable);


  // Interface between LAr and Detectors =============================================================================
  surf_name = "LArToGe";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = groundfrontpainted,
      surface_type = dielectric_metal,
      smoothness   = 0.5
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Germanium-Enr")->GetMaterialPropertiesTable());

  // Interface between LAr and copper ================================================================================
  surf_name = "LArToCu";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal,
      smoothness   = 0.5
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Copper-EF")->GetMaterialPropertiesTable());

  // Interface between LAr and silicon ================================================================================
  surf_name = "LArToSi";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal,
      smoothness   = 0.7
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Silicon")->GetMaterialPropertiesTable());
}


LGND_200_OpticalSurfaces::~LGND_200_OpticalSurfaces() {
  // delete all instances stored in the arrays
  for (auto _s : fOpticalSurfaces) delete _s.second;
}

G4OpticalSurface* LGND_200_OpticalSurfaces::GetOpticalSurface(std::string name) {
  auto search = fOpticalSurfaces.find(name);
  if (search == fOpticalSurfaces.end()) {
    MGLog(error) << "Optical surface " << name << " not found! Returning nullptr." << endlog;
    return nullptr;
  }

  return search->second;
}

std::vector<std::string> LGND_200_OpticalSurfaces::GetListOfSurfaces() {
  std::vector<std::string> v;
  for (auto& _s : fOpticalSurfaces) v.push_back(_s.first);
  return v;
}



