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
// CLASS IMPLEMENTATION:  LGND_200_19String_FiberArrayAssembly.cc
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
 *
 * REVISION:
 *
 */
//---------------------------------------------------------------------------//
//

#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Tubs.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SubtractionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"

//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "legendgeometry/LGND_200_19String_FiberArrayAssembly.hh"
#include "legendgeometry/LGND_FiberCore.hh"
#include "legendgeometry/LGND_FiberCladding.hh"
#include "legendgeometry/LGND_FiberWLSCoating.hh"
#include "legendgeometry/LGND_Part.hh"
#include "legendgeometry/LGND_FiberSiPM.hh"

#include "legendgeometry/LGND_FiberCoreCurved.hh"
#include "legendgeometry/LGND_FiberCladdingCurved.hh"
#include "legendgeometry/LGND_FiberWLSCoatingCurved.hh"

#include "legendgeometry/LGND_200_OpticalSurfaces.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;

LGND_200_19String_FiberArrayAssembly::LGND_200_19String_FiberArrayAssembly(G4String name, G4String serialNumber, G4double length,G4double placementRadius,G4String shape) :
   fLength(length*mm), fName(name), fShape(shape), fPlacementRadius(placementRadius*mm)
{
  //intialize parts so that dimensions and strings can be passed in Place()
  fFiberCore = new LGND_FiberCore(fName+"FiberCore","000-001",fLength,fShape);
  fFiberCladdingInner = new LGND_FiberCladding(fName+"FiberCladdingInner","000-002",fLength,fShape,"PMMA");
  fFiberCladdingOuter = new LGND_FiberCladding(fName+"FiberCladdingOuter","000-002",fLength,fShape,"Fluor-acrylic");
  fFiberWLSCoating = new LGND_FiberWLSCoating(fName+"FiberWLSCoating","000-003",fLength,fShape);
  //note SiPM have different length than fibers
  fFiberSiPM = new LGND_FiberSiPM(fName+"FiberSiPM","000-004",0.1*mm,fShape);
  fFiberReflector = new LGND_FiberSiPM(fName+"FiberRelfector","000-005",0.1*mm,fShape);

  fFiberCoreCurved = new LGND_FiberCoreCurved(fName+"FiberCoreCurved","000-006",placementRadius,fShape,pi);
  fFiberCladdingInnerCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingInnerCurved","000-007",placementRadius,fShape,"PMMA",pi);
  fFiberCladdingOuterCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingOuterCurved","000-008",placementRadius,fShape,"Fluor-acrylic",pi);
  fFiberWLSCoatingCurved = new LGND_FiberWLSCoatingCurved(fName+"FiberWLSCoatingCurved","000-009",placementRadius,fShape,pi);

}


LGND_200_19String_FiberArrayAssembly::~LGND_200_19String_FiberArrayAssembly()
{
  UnallocateParts();
}

void LGND_200_19String_FiberArrayAssembly::AllocateParts()
{
}

void LGND_200_19String_FiberArrayAssembly::UnallocateParts()
{
  delete fFiberCore;
  delete fFiberCladdingInner;
  delete fFiberCladdingOuter;
  delete fFiberWLSCoating;
  delete fFiberSiPM;
  delete fFiberReflector;

  delete fFiberCoreCurved;
  delete fFiberCladdingInnerCurved;
  delete fFiberCladdingOuterCurved;
  delete fFiberWLSCoatingCurved;
}

void LGND_200_19String_FiberArrayAssembly::Place(G4ThreeVector* assemPosition,G4RotationMatrix* assemRotation, G4LogicalVolume* motherLogical)
{
  LGND_200_OpticalSurfaces *opticalSurfaces = new LGND_200_OpticalSurfaces();

  //Place Fiber Array
  G4double deltaAngle = 0.; 
  G4double rotationAngle = 0;  
  //G4double placement_radius = 0.295*m;//intial guess
  G4double placement_radius =  fPlacementRadius;
  //TODO-what is the real spacing?
  G4double fiber_spacing = 0.;
  G4ThreeVector* fiberPosition = new G4ThreeVector(0);
  G4int nFibers;
  if(fFiberCore->GetShape() == "circle"){
    //cord between two cirlces of fiber is radius1+radius2 or 2*radius if circles are the same
    //cord = 2*R*sin(theta/2)
    //Also FibberCladding is one class to GetRadius returns total thickness
    fiber_spacing = 2.0*(fFiberCore->GetRadius() + fFiberCladdingInner->GetRadius() + fFiberWLSCoating->GetRadius() );
    //G4cout<<fiber_spacing<<"  !!!!!!!!!!!!!!!"<<fFiberCore->GetRadius()<<" "<<fFiberCladding->GetRadius()<<" "<<fFiberWLSCoating->GetRadius()<<G4endl;
    deltaAngle = 2.*asin(fiber_spacing/(2.*placement_radius));
    nFibers =floor(2*pi/deltaAngle);
    //make sure that the last fiber does not overlap with the first
    deltaAngle = 2*pi/nFibers;
    placement_radius = fiber_spacing/(2.*sin(deltaAngle/2.));
    fiberPosition = new G4ThreeVector(placement_radius,0.*m,0.*m);
    fiberPosition->setX(fiberPosition->x() + assemPosition->x());
    fiberPosition->setY(fiberPosition->y() + assemPosition->y());
    fiberPosition->setZ(fiberPosition->z() + assemPosition->z());
    MGLog(routine) << "placing "<< nFibers <<" fibers" << " at angle "<<deltaAngle<<endlog;
  }
  else if (fFiberCore->GetShape() == "square"){
    fiber_spacing = 2.0*(fFiberCore->GetRadius() + fFiberCladdingInner->GetRadius() + fFiberWLSCoating->GetRadius() );
    //What kind of coverage are we talking about?
    double coverage = 0.80;
    fiber_spacing /= coverage;
    //deltaAngle = 4.*asin(sqrt(2)*fiber_spacing/(2*placement_radius));
    deltaAngle = 2.*asin(sqrt(2)*fiber_spacing/(2*placement_radius));
    //make sure that the last fiber does not overlap with the first
    nFibers = floor(2*pi/deltaAngle) + 1;
    deltaAngle = 2*pi/nFibers;
    //placement_radius = sqrt(2)*fiber_spacing/(2*sin(deltaAngle/4.));
    placement_radius = sqrt(2)*fiber_spacing/(2*sin(deltaAngle/2.));
    fiberPosition = new G4ThreeVector(placement_radius,0.*m,0.*m);
    fiberPosition->setX(fiberPosition->x() + assemPosition->x());
    fiberPosition->setY(fiberPosition->y() + assemPosition->y());
    fiberPosition->setZ(fiberPosition->z() + assemPosition->z());
    MGLog(routine) << "placing "<< nFibers <<" fibers" << " at angle "<<deltaAngle<<endlog;

  }
  
  if(fiber_spacing == 0){
    MGLog(fatal)<< "fiber spacing is zero! Shape is "<<fFiberCore->GetShape()<<"..."<<endlog;
    return;
  }

    //
  int num = 0;
  do{
    //No copies, each solid has to have an individual name
    //creating unique names
    fFiberCore = new LGND_FiberCore(fName+"FiberCore_"+to_string(num),"000-001",fLength,fShape);
    fFiberCladdingInner = new LGND_FiberCladding(fName+"FiberCladdingInner_"+to_string(num),"000-002",fLength,fShape,"PMMA");
    fFiberCladdingOuter = new LGND_FiberCladding(fName+"FiberCladdingOuter_"+to_string(num),"000-002",fLength,fShape,"Fluor-acrylic");
    fFiberWLSCoating = new LGND_FiberWLSCoating(fName+"FiberWLSCoating_"+to_string(num),"000-003",fLength,fShape);
    fFiberSiPM = new LGND_FiberSiPM(fName+"FiberSiPM_"+to_string(num),"000-004",0.1*mm,fShape);
    fFiberReflector = new LGND_FiberSiPM(fName+"FiberReflector_"+to_string(num),"000-005",0.1*mm,fShape);

    fFiberCoreCurved = new LGND_FiberCoreCurved(fName+"FiberCoreCurved"+to_string(num),"000-006",std::fabs(placement_radius*cos(rotationAngle)),fShape,pi);
    fFiberCladdingInnerCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingInnerCurved"+to_string(num),"000-007",std::fabs(placement_radius*cos(rotationAngle)),fShape,"PMMA",pi);
    fFiberCladdingOuterCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingOuterCurved"+to_string(num),"000-008",std::fabs(placement_radius*cos(rotationAngle)),fShape,"Fluor-acrylic",pi);
    fFiberWLSCoatingCurved = new LGND_FiberWLSCoatingCurved(fName+"FiberWLSCoatingCurved"+to_string(num),"00-009",std::fabs(placement_radius*cos(rotationAngle)),fShape,pi);
    
    //G4cout<<"/vis/scene/add/volume "<<fName+"FiberCore_"+to_string(num)<<endl;
    //for vis
    /*
    if(num%10 == 0){
    G4cout<<"/vis/scene/add/volume "<<fName+"FiberCore_"+to_string(num)<<endl;
    G4cout<<"/vis/scene/add/volume "<<fName+"FiberCladdingInner_"+to_string(num)<<endl;
    G4cout<<"/vis/scene/add/volume "<<fName+"FiberCladdingOuter_"+to_string(num)<<endl;
    G4cout<<"/vis/scene/add/volume "<<fName+"FiberWLSCoating_"+to_string(num)<<endl;
    G4cout<<"/vis/scene/add/volume "<<fName+"FiberSiPM_"+to_string(num)<<endl;
    G4cout<<"/vis/scene/add/volume "<<fName+"FiberReflector_"+to_string(num)<<endl;
    }
    */
    num++;
    if(num > 1e5){
      MGLog(error)<<" Stuck in fiber placement loop"<<endlog;
      MGLog(fatal)<<endlog;
    }

    G4double rotationAngleDegree = rotationAngle*180./pi;
    G4ThreeVector * r = fiberPosition;
    //Inner fiber array covers 44 degrees with 16 degree gaps for calibration sources
    if(fName.contains("Inner")&&
        ((rotationAngleDegree > 0   && rotationAngleDegree < 22 ) || (rotationAngleDegree > 38  && rotationAngleDegree < 82 ) || (rotationAngleDegree > 98  && rotationAngleDegree < 142) || 
         (rotationAngleDegree > 158 && rotationAngleDegree < 202) || (rotationAngleDegree > 218 && rotationAngleDegree < 262) || (rotationAngleDegree > 278 && rotationAngleDegree < 322) ||
         (rotationAngleDegree > 338 && rotationAngleDegree < 360)))
    {
      G4RotationMatrix* rotationFiber = new G4RotationMatrix();
      //rotation is for square fibers to create maximum coverage
      //keeping it for circular fibers too since rotating a circle does nothing
      //Don't rotate fiber if Curved fibers are added to the bottom
      rotationFiber->rotateZ(-rotationAngle-pi/4);
      fFiberWLSCoating->Place(fiberPosition,rotationFiber,motherLogical);
      G4VPhysicalVolume* wlsPhysical = fFiberWLSCoating->GetPhysicalVolume();

      fFiberCladdingInner->Place(fiberPosition,rotationFiber,motherLogical);
      G4VPhysicalVolume* claddingInnerPhysical = fFiberCladdingInner->GetPhysicalVolume();

      fFiberCladdingOuter->Place(fiberPosition,rotationFiber,motherLogical);
      G4VPhysicalVolume* claddingOuterPhysical = fFiberCladdingOuter->GetPhysicalVolume();

      fFiberCore->Place(fiberPosition,rotationFiber,motherLogical);
      G4VPhysicalVolume* corePhysical = fFiberCore->GetPhysicalVolume();

      //corePhysical->CheckOverlaps(1000000, 0, true);
      r->setZ(r->getZ() + fLength +fFiberSiPM->GetLength());
      fFiberSiPM->Place(r,rotationFiber,motherLogical);
      G4VPhysicalVolume* SiPMPhysical = fFiberSiPM->GetPhysicalVolume();

      new G4LogicalBorderSurface("SiPM_core_logical_border"+to_string(r->getX()),corePhysical,SiPMPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
      new G4LogicalBorderSurface("SiPM_claddingInner_logical_border"+to_string(r->getX()),claddingInnerPhysical,SiPMPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
      new G4LogicalBorderSurface("SiPM_claddingOuter_logical_border"+to_string(r->getX()),claddingOuterPhysical,SiPMPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
      new G4LogicalBorderSurface("SiPM_TPB_logical_border"+to_string(r->getX()),wlsPhysical,SiPMPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
        
      //Place reflector for inner array
      r->setZ(-1.*r->getZ());
      fFiberReflector->Place(r,rotationFiber,motherLogical);
      G4VPhysicalVolume* reflectorPhysical = fFiberReflector->GetPhysicalVolume();
      new G4LogicalBorderSurface("Reflector_core_logical_border"+to_string(r->getX()),corePhysical,reflectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberEndToLAr"));
      new G4LogicalBorderSurface("Reflector_claddingInner_logical_border"+to_string(r->getX()),claddingInnerPhysical,reflectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberEndToLAr"));
      new G4LogicalBorderSurface("Reflector_claddingOuter_logical_border"+to_string(r->getX()),claddingOuterPhysical,reflectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberEndToLAr"));
      new G4LogicalBorderSurface("Reflector_tpb_logical_border"+to_string(r->getX()),wlsPhysical,reflectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberEndToLAr"));
    }
    else if(fName.contains("Outer")){
      G4RotationMatrix* rotationFiber = new G4RotationMatrix();
      //rotation is for square fibers to create maximum coverage
      //keeping it for circular fibers too since rotating a circle does nothing
      //Don't rotate fiber if Curved fibers are added to the bottom
      //rotationFiber->rotateZ(-rotationAngle-pi/4);

      fFiberWLSCoating->Place(fiberPosition,rotationFiber,motherLogical);
      G4VPhysicalVolume* wlsPhysical = fFiberWLSCoating->GetPhysicalVolume();

      fFiberCladdingInner->Place(fiberPosition,rotationFiber,motherLogical);
      G4VPhysicalVolume* claddingInnerPhysical = fFiberCladdingInner->GetPhysicalVolume();

      fFiberCladdingOuter->Place(fiberPosition,rotationFiber,motherLogical);
      G4VPhysicalVolume* claddingOuterPhysical = fFiberCladdingOuter->GetPhysicalVolume();

      fFiberCore->Place(fiberPosition,rotationFiber,motherLogical);
      G4VPhysicalVolume* corePhysical = fFiberCore->GetPhysicalVolume();

      //corePhysical->CheckOverlaps(1000000, 0, true);
      r->setZ(r->getZ() + fLength +fFiberSiPM->GetLength());
      fFiberSiPM->Place(r,rotationFiber,motherLogical);
      G4VPhysicalVolume* SiPMPhysical = fFiberSiPM->GetPhysicalVolume();

      new G4LogicalBorderSurface("SiPM_core_logical_border"+to_string(r->getX()),corePhysical,SiPMPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
      new G4LogicalBorderSurface("SiPM_claddingInner_logical_border"+to_string(r->getX()),claddingInnerPhysical,SiPMPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
      new G4LogicalBorderSurface("SiPM_claddingOuter_logical_border"+to_string(r->getX()),claddingOuterPhysical,SiPMPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
      new G4LogicalBorderSurface("SiPM_TPB_logical_border"+to_string(r->getX()),wlsPhysical,SiPMPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
      
      //place semi-cirlce fibers for have the array (connecting fiber_n to fiber_2n for 2n <= nFibers)
      if(rotationAngle < pi ){
        G4ThreeVector* bottomPosition = new G4ThreeVector();
        bottomPosition->setX(assemPosition->x());
        double sign = 1;
        if(rotationAngle > pi/2) sign = -1;
        bottomPosition->setY(assemPosition->y() + placement_radius*sin(rotationAngle)*sign);
        bottomPosition->setZ(assemPosition->z() - fLength);
        //G4cout<<"("<<bottomPosition->x()<<","<<bottomPosition->y()<<","<<bottomPosition->z()<<")"<<G4endl;
        G4RotationMatrix* curveRotation = new G4RotationMatrix();
        curveRotation->rotateX(pi/2);
        //Core
        fFiberCoreCurved->Place(bottomPosition,curveRotation,motherLogical);
        G4VPhysicalVolume* fiberCoreCurvedPhysical = fFiberCoreCurved->GetPhysicalVolume();
        //fiberCoreCurvedPhysical->CheckOverlaps(100000,0,true);
        //Inner Cladding
        fFiberCladdingInnerCurved->Place(bottomPosition,curveRotation,motherLogical);
        G4VPhysicalVolume* fiberCladdingInnerCurvedPhysical = fFiberCladdingInnerCurved->GetPhysicalVolume();
        //fiberCladdingInnerCurvedPhysical->CheckOverlaps(100000,0,true);
        //Outer Cladding
        fFiberCladdingOuterCurved->Place(bottomPosition,curveRotation,motherLogical);
        G4VPhysicalVolume* fiberCladdingOuterCurvedPhysical = fFiberCladdingOuterCurved->GetPhysicalVolume();
        //fiberCladdingOuterCurvedPhysical->CheckOverlaps(100000,0,true);
        //TPB Coating
        fFiberWLSCoatingCurved->Place(bottomPosition,curveRotation,motherLogical);
        G4VPhysicalVolume* fiberWLSCoatingCurvedPhysical = fFiberWLSCoatingCurved->GetPhysicalVolume();
        //fiberWLSCoatingCurvedPhysical->CheckOverlaps(100000,0,true);
        //if(num%1 == 0)G4cout<<"/vis/scene/add/volume "<<fName+"FiberCoreCurved"+to_string(num)<<G4endl;
      }
    }
    r->setZ(0.);
    rotationAngle += deltaAngle;
    fiberPosition->setX(placement_radius*cos(rotationAngle));fiberPosition->setY(placement_radius*sin(rotationAngle));fiberPosition->setZ(0.);
    fiberPosition->setX(fiberPosition->x() + assemPosition->x());
    fiberPosition->setY(fiberPosition->y() + assemPosition->y());
    fiberPosition->setZ(fiberPosition->z() + assemPosition->z());
    MGLog(debugging)<<"core position"<<fFiberCore->GetPartPosition()<<"... ("<<assemPosition->getX()<<","<<assemPosition->getY()<<","<<assemPosition->getZ()<<")"<<endlog;
  } while (rotationAngle < 2.*pi);
}
