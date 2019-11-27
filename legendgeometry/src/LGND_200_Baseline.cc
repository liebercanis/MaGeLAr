//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
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
// $Id: MJcodeTemplate.cc,v 1.3 2005-02-15 23:26:55 akbarm Exp $
//
// CLASS IMPLEMENTATION:  LGND_200_Baseline.cc
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
 * AUTHOR: Matthew Green
 * CONTACT: matthew_green@ncsu.edu
 * FIRST SUBMISSION: May 25 2017
 *
 * REVISION:
 * 05-25-2017, Created, M. Green
 *
 */
//---------------------------------------------------------------------------//
//


//---------------------------------------------------------------------------//

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"


//#include <cmath>//floor() function
#include <math.h>       

#include "legendgeometry/LGND_200_Baseline.hh"
#include "legendgeometry/LGND_Part.hh"
#include "legendgeometry/LGND_Assembly.hh"
#include "legendgeometry/LGND_200_Cryostat.hh"
#include "legendgeometry/LGND_200_ArrayAssembly.hh"
#include "legendgeometry/LGND_200_19String_FiberArrayAssembly.hh"
#include "legendgeometry/LGND_CopperShroud.hh"
#include "legendgeometry/LGND_200_OpticalSurfaces.hh"

#include "legendgeometry/LGND_200_CalibrationAssembly.hh"
#include "legendio/LGND_JSONReader.hh"

#include "geometry/MGGeometryGlobals.hh"
#include "io/MGLogger.hh"

#include "legendgeometry/LGND_200_BaselineMessenger.hh"


//---------------------------------------------------------------------------//

using namespace CLHEP;


LGND_200_Baseline::LGND_200_Baseline(G4String version):
     MGGeometryDetector(version),
     fMessenger(0),
		 fCalibrationOn(0),
     fArgonSensitive(true),
     fGermaniumSensitive(true),
     fFiberCoreSensitive(false),
     fSiPMSensitive(false)
{
	fMessenger = new LGND_200_BaselineMessenger(this);
}

//---------------------------------------------------------------------------//

LGND_200_Baseline::~LGND_200_Baseline()
{
  delete fMessenger;
}

//---------------------------------------------------------------------------//

void LGND_200_Baseline::ConstructDetector()
{

  //LGND_200_OpticalSurfaces *opticalSurfaces = new LGND_200_OpticalSurfaces();

  G4Material *argon = G4Material::GetMaterial("Argon-Liq");
  //G4Material *argon = OpticalMaterials->Get_ArgonLiquid();
  G4Box* exptBox = new G4Box("exptBox", 100.*m, 100.*m, 100.*m);
  G4VisAttributes* ArVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0,0.01)); // magenta, 1% opaque
  ArVisAtt->SetForceWireframe( true );
  theDetectorLogical = new G4LogicalVolume(exptBox, argon, "theDetectorLogical");
  theDetectorLogical->SetVisAttributes(ArVisAtt);
  //theDetectorPhysical->CheckOverlaps(1000000, 0, true);
  //G4VPhysicalVolume* theDetectorPhysical = new G4PVPlacement(0,G4ThreeVector(0,0,0),theDetectorLogical,"Detector",0,false,0,false);

  G4Material *rock = G4Material::GetMaterial("Rock");
  G4Box* outerBox = new G4Box("outerBox", 99.9999*m, 99.9999*m, 99.9999*m);
  G4Box* innerBox = new G4Box("innerBox", 20.0*m, 20.0*m, 20.0*m);
  G4SubtractionSolid *cavern = new G4SubtractionSolid("cavern", outerBox, innerBox);
  G4VisAttributes* rockVisAtt = new G4VisAttributes(G4Colour(0.64, 0.64, 0.64, 0.1));//gray, 10% opaque
  G4LogicalVolume* cavernLog = new G4LogicalVolume(cavern, rock, "CavernRockLogical");
  rockVisAtt->SetForceWireframe( true );
  cavernLog->SetVisAttributes(rockVisAtt);
  /*G4PVPlacement* cavernPhys =*/ new G4PVPlacement(0, G4ThreeVector(0,0,0), cavernLog, "cavern", theDetectorLogical, false, 0);

  G4Material *air = G4Material::GetMaterial("Air");
  G4Box* airboundary = new G4Box("airboundary", 19.9999*m, 19.9999*m, 19.9999*m);
  G4Tubs* cryostatvoid = new G4Tubs("cryostatvoid", 0, 2.0001*m, 2.0001*m, 0, 2*pi);
  G4SubtractionSolid *airspace = new G4SubtractionSolid("airspace", airboundary, cryostatvoid);
  G4VisAttributes* airVisAtt = new G4VisAttributes(G4Colour(0.64, 0.64, 0.64, 0.01));//gray, 1% opaque
  G4LogicalVolume* airLog = new G4LogicalVolume(airspace, air, "LabAirLogical");
  airVisAtt->SetForceWireframe(true);
  airLog->SetVisAttributes(airVisAtt);
  /*G4PVPlacement* airSpacePhys =*/ new G4PVPlacement(0, G4ThreeVector(0,0,0), airLog, "airSpace", theDetectorLogical, false, 0);

  LGND_200_Cryostat* cryostat1 = new LGND_200_Cryostat("Cryostat_001", "867-5309");
  G4ThreeVector* positionA = new G4ThreeVector(0);
  G4RotationMatrix* rotationA = new G4RotationMatrix();
  cryostat1->Place(positionA, rotationA, theDetectorLogical);

  LGND_200_19String_FiberArrayAssembly * fiberArrayOuter = new LGND_200_19String_FiberArrayAssembly("FiberArrayOuter_","000-001",0.50*m,0.290*m, "square");
  G4RotationMatrix* rotationFiber = new G4RotationMatrix();
  G4ThreeVector* fiberPosition = new G4ThreeVector(0,0,400.0*mm);
  fiberArrayOuter->Place(fiberPosition,rotationFiber,theDetectorLogical);
 
  //Center String 
  //LGND_200_19String_FiberArrayAssembly * fiberArrayInner = new LGND_200_19String_FiberArrayAssembly("FiberArrayInner_","000-002",1*m,0.0549*m, fFiberShape);
  //Middle string for fiber array
  LGND_200_19String_FiberArrayAssembly * fiberArrayInner = new LGND_200_19String_FiberArrayAssembly("FiberArrayInner_","000-002",0.50*m,160.5*mm, "square");
  fiberArrayInner->Place(fiberPosition,rotationFiber,theDetectorLogical);
  G4cout<<"Placing inner fibers at "<<0.290*m<<", placing outer fibers at "<<160.5*mm<<G4endl;
  
  ///*
  //Insert disks every 10 mm, disk at (0,0,0) has 60 cm radius rather than 30 cm
  //Use for estimating dimensions of array
  for(int i = 1; i < 20; i++){
    G4Tubs *diskSolid;
    if(i!=10)
      diskSolid = new G4Tubs("disk"+to_string(i),0,30.*cm,1.*cm,0,2*pi);
    else 
      diskSolid = new G4Tubs("disk"+to_string(i),0,60.*cm,1.*cm,0,2*pi);
    G4LogicalVolume* diskLogical = new G4LogicalVolume(diskSolid,G4Material::GetMaterial("Copper-EF"),"logicalDisk"+to_string(i));
    G4VisAttributes* diskVisAtt = new G4VisAttributes(G4Colour(1., 0.0, 0.));
    diskLogical->SetVisAttributes(diskVisAtt);
    new G4PVPlacement(0,G4ThreeVector(0,0,-1.0*m+10*i*cm),diskLogical,"disk"+to_string(i),theDetectorLogical,false,0);
    G4cout<<"/vis/scene/add/volume logicalDisk"+to_string(i)<<endl;
  }
  //*/


  //Radon Shield
  G4ThreeVector* positionShroud = new G4ThreeVector(0,0,200.0*mm);
  G4RotationMatrix* rotationShroud = new G4RotationMatrix();
  //Stefan say it should be 300 cm
  //open on top and closed on bottom
  G4double shroudHalfHeight = 1.5*m;
  if(fShroudRadius == 0){
    MGLog(warning)<<"Radon Shield Radius was not set...use:  /MG/L200/RadonShroudRadius to set radius"<<endl;
    G4cout<<"\t Setting radius to 700 mm (1400 mm OD)"<<endl;
    fShroudRadius = 700. *mm;
  }
  else
    MGLog(routine)<<"Radon Shield Radius is set to "<<fShroudRadius<<endl;
  
  LGND_CopperShroud * copperShroud = new LGND_CopperShroud("CopperShroud","1234-4321",shroudHalfHeight,fShroudRadius,"Copper-EF"); 
  copperShroud->Place(positionShroud,rotationShroud,theDetectorLogical);
  LGND_CopperShroud * WLSShroud = new LGND_CopperShroud("WLSShroud","34-4321",shroudHalfHeight,fShroudRadius,"TPBOnTetratex");
  WLSShroud->Place(positionShroud,rotationShroud,theDetectorLogical);
 
  // assign surface surface properties between WLS and LAr
  new G4LogicalBorderSurface("WLSShourd_LAr_In ",theDetectorPhysical,WLSShroud->GetPhysicalVolume(),LGND_200_OpticalSurfaces::GetOpticalSurface("LArToTPB"));
  new G4LogicalBorderSurface("WLSShourd_LAr_Out",WLSShroud->GetPhysicalVolume(),theDetectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToTPB"));
  // assign Tetratex reflective surface
  new G4LogicalSkinSurface("Tetratex_surface",WLSShroud->GetPartLogical(),LGND_200_OpticalSurfaces::GetOpticalSurface("TPBToTetratex"));
  // assign Copper-EF reflective surface
  new G4LogicalSkinSurface("Copper-EF_surface",copperShroud->GetPartLogical(),LGND_200_OpticalSurfaces::GetOpticalSurface("LArToCu"));

  WLSShroud->GetPhysicalVolume()->CheckOverlaps(1000, 0, true);
  copperShroud->GetPhysicalVolume()->CheckOverlaps(1000, 0, true);

  //Place Ge Detector Array
  std::vector<G4String> cryostatList;
  LGND_JSONReader* reader = new LGND_JSONReader("LGND_200.json");
  cryostatList = reader->ReadCryostats("LGND200");
  delete reader;
  if(cryostatList.size()){
    LGND_200_ArrayAssembly* detArray1 = new LGND_200_ArrayAssembly("DetectorArray_001", cryostatList.at(0));
    G4ThreeVector* positionB = new G4ThreeVector(0, 0, 400.0*mm);
    G4RotationMatrix* rotationB = new G4RotationMatrix();
    detArray1->Place(positionB, rotationB, theDetectorLogical);
  }

  //get physical volumes by name for optical boundries
  //Some physical boundries are between the LAr, while some are between optical fiber components
  //LAr boundaries defined here,
  //Fiber/SiPM boundaries defined in Fiber Builder
  G4PhysicalVolumeStore* volumeStore = G4PhysicalVolumeStore::GetInstance();
  G4int nVolumes = (G4int) volumeStore->size();
  G4String candidateList;
  for(G4int i=0;i<nVolumes;i++) {
    candidateList = (*volumeStore)[i]->GetName();
    G4VPhysicalVolume* phys_vol = (*volumeStore)[i];
    if(candidateList.contains("MiniShroud")){
      new G4LogicalBorderSurface("WLSshroud_LAr_logical_border"+to_string(i),theDetectorPhysical,phys_vol,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToTPB"));
      new G4LogicalBorderSurface("LAr_WLSshroud_logical_border"+to_string(i),phys_vol,theDetectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToTPB"));
      new G4LogicalSkinSurface("WLSMini-ShroudSkin_"+to_string(i),phys_vol->GetLogicalVolume(),LGND_200_OpticalSurfaces::GetOpticalSurface("TPBToNylon"));
    }
    else if(candidateList.contains("SiPlate")){
      new G4LogicalBorderSurface("SiPlate_LAr_logical_border"+to_string(i),theDetectorPhysical,phys_vol,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToSi"));
      new G4LogicalBorderSurface("LAr_SiPlate_logical_border"+to_string(i),phys_vol,theDetectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToSi"));
      new G4LogicalSkinSurface("SiliconSkin_"+to_string(i),phys_vol->GetLogicalVolume(),LGND_200_OpticalSurfaces::GetOpticalSurface("LArToSi"));
    }
    else if(candidateList.contains("ActiveDet")){
      new G4LogicalBorderSurface("LAr_Germanium_logical_border"+to_string(i),theDetectorPhysical,phys_vol,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToGe"));
      new G4LogicalBorderSurface("Germanium_LAr_logical_border"+to_string(i),phys_vol,theDetectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToGe"));
      new G4LogicalSkinSurface("GermaniumSkin_"+to_string(i),phys_vol->GetLogicalVolume(),LGND_200_OpticalSurfaces::GetOpticalSurface("LArToGe"));
    }
    else if(phys_vol->GetLogicalVolume()->GetMaterial()->GetName() == "Copper-EF"){
      new G4LogicalBorderSurface("LAr_"+phys_vol->GetName()+"_logical_border"+to_string(i),theDetectorPhysical,phys_vol,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToCu"));
      new G4LogicalBorderSurface( phys_vol->GetName()+"_LAr_logical_border"+to_string(i),phys_vol,theDetectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToCu"));
      new G4LogicalSkinSurface("Cu-EFSkin_"+to_string(i),phys_vol->GetLogicalVolume(),LGND_200_OpticalSurfaces::GetOpticalSurface("LArToCu"));
    }
    else if(candidateList.contains("FiberWLSCoating")){
      new G4LogicalBorderSurface("WLSshroud_LAr_logical_border"+to_string(i),theDetectorPhysical,phys_vol,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToTPB"));
      new G4LogicalBorderSurface("LAr_WLSshroud_logical_border"+to_string(i),phys_vol,theDetectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("LArToTPB"));
      new G4LogicalSkinSurface("fiberWLSLogicalSkinSurface"+to_string(i),phys_vol->GetLogicalVolume(),LGND_200_OpticalSurfaces::GetOpticalSurface("LArToTPB"));
    }
  }

	LGND_200_CalibrationAssembly* calAssembly = new LGND_200_CalibrationAssembly("CalibrationAssembly","000-0000"); //no idea what serialnumber		
	if(fCalibrationOn){
		//replace !!
		calAssembly->SetSourceNumber(fCalibrationSourceNumber);
		calAssembly->SetSourcePosition(fCalibrationSourcePosition);
		calAssembly->SetAbsorber(fCalibrationAbs);	
		
		MGLog(routine) << "Calibration Sources used" << endlog;	
 	 	G4ThreeVector* positionC = new G4ThreeVector(0, 0, 400*mm);
  	G4RotationMatrix* rotationC = new G4RotationMatrix();
		calAssembly->Place(positionC, rotationC, theDetectorLogical);
	}
}
//---------------------------------------------------------------------------//

int LGND_200_Baseline::GetSensitiveVolumeID(const string& volName)
{
  int sensVolID = 0;

  G4PhysicalVolumeStore *storePtr = G4PhysicalVolumeStore::GetInstance();
  G4VPhysicalVolume* pVol = storePtr->GetVolume(volName, false);
  G4String material = pVol->GetLogicalVolume()->GetMaterial()->GetName();
  //Sensitive volumes are set by including:
  ///MG/io/MCOpticalRun/SetSensitiveIDLabelScheme askGeom
  //or..
  ///MG/io/MCORun/SetSensitiveIDLabelScheme askGeom
  //then including which flags you want
  //default is to have Germanium and Argon be sensitive detectors

  //Detector is LAr volume
  if(fArgonSensitive){
    if (volName == "Detector" ){
      return 201;
    }
  }
  //Germanium Detectors
  if(fGermaniumSensitive){
    size_t found = volName.find("Active");
    //Removed to add in optical sensitiveVolumes
    //if(found == string::npos) return 0;

    if (material == "Germanium-Enr" || material == "Germanium-Nat"){
      sensVolID = 1000000;
      MGLog(debugging) << "Germanium Crystal:" << endlog;
      found = volName.find("DetectorArray_");
      if (found != string::npos){
        MGLog(debugging) << "Array No: " << volName.substr(found+14, 3) << endlog;
        sensVolID += atoi(volName.substr(found+14, 3).c_str()) * 10000;
      }
      found = volName.find("StringAssembly_");
      if (found != string::npos) {
        MGLog(debugging) << "String No: " << volName.substr(found+15, 3) << endlog;
        sensVolID += atoi(volName.substr(found+15, 3).c_str()) * 100;
      }
      found = volName.find("DetUnit_");
      if (found != string::npos) {
        MGLog(debugging) << "Crystal No: " << volName.substr(found+16, 3) << endlog;
        sensVolID += atoi(volName.substr(found+8, 3).c_str()) * 1;
      }
    }
  }
  //Fiber Core
  if(fFiberCoreSensitive){
    if( volName.find("FiberCore") != string::npos){
      sensVolID = 100000;
      size_t found = volName.find("FiberCore_");
      sensVolID += atoi(volName.substr(found+10).c_str());
    }
  }
  //SiPM
  if(fSiPMSensitive){
    if( volName.find("FiberArrayInner_FiberSiPM") != string::npos){
      sensVolID = 1000;
      size_t found = volName.find("SiPM_");
      sensVolID += atoi(volName.substr(found+5).c_str());
    }

    if( volName.find("FiberArrayOuter_FiberSiPM") != string::npos){
      sensVolID = 10000;
      size_t found = volName.find("SiPM_");
      sensVolID += atoi(volName.substr(found+5).c_str());
    }
  }

  return sensVolID;
}
//---------------------------------------------------------------------------//

void LGND_200_Baseline::SetTest(G4String dummy){
	MGLog(debugging) << "//////////////////////////" << endlog;
	MGLog(debugging) << "this is your test string :" << endlog;
	MGLog(debugging) << dummy << endlog;
	MGLog(debugging) << "//////////////////////////" << endlog;
	return;
}

//---------------------------------------------------------------------------//