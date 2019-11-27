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
// CLASS IMPLEMENTATION:  LGND_200_14String_FiberArrayAssembly.cc
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
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4UIcommand.hh"


//---------------------------------------------------------------------------//

#include "io/MGLogger.hh"
#include "legendgeometry/LGND_200_14String_FiberArrayAssembly.hh"
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

LGND_200_14String_FiberArrayAssembly::LGND_200_14String_FiberArrayAssembly(G4String name, G4String serialNumber, G4double length,G4double placementRadius,G4String shape) :
   fLength(length*mm), fName(name), fShape(shape), fPlacementRadius(placementRadius*mm)
{
  //intialize parts so that dimensions and strings can be passed in Place()
  fFiberCore = new LGND_FiberCore(fName+"FiberCore_","000-001",fLength,fShape);
  fFiberCladdingInner = new LGND_FiberCladding(fName+"FiberCladdingInner_","000-002",fLength,fShape,"PMMA");
  fFiberCladdingOuter = new LGND_FiberCladding(fName+"FiberCladdingOuter_","000-002",fLength,fShape,"Fluor-acrylic");
  fFiberWLSCoating = new LGND_FiberWLSCoating(fName+"FiberWLSCoating_","000-003",fLength,fShape);
  //note SiPM have different length than fibers
  fFiberSiPMTop = new LGND_FiberSiPM(fName+"FiberSiPMTop_","000-004",0.1*mm,fShape);
  fFiberSiPMBot = new LGND_FiberSiPM(fName+"FiberSiPMBot_","000-004",0.1*mm,fShape);
  fFiberReflector = new LGND_FiberSiPM(fName+"FiberRelfector_","000-005",0.1*mm,fShape);

  fFiberCoreCurved = new LGND_FiberCoreCurved(fName+"FiberCoreCurved_","000-006",placementRadius,fShape,0.5*pi);
  fFiberCladdingInnerCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingInnerCurved_","000-007",placementRadius,fShape,"PMMA",0.5*pi);
  fFiberCladdingOuterCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingOuterCurved_","000-008",placementRadius,fShape,"Fluor-acrylic",0.5*pi);
  fFiberWLSCoatingCurved = new LGND_FiberWLSCoatingCurved(fName+"FiberWLSCoatingCurved_","000-009",placementRadius,fShape,0.5*pi);

}


LGND_200_14String_FiberArrayAssembly::~LGND_200_14String_FiberArrayAssembly()
{
  UnallocateParts();
}

void LGND_200_14String_FiberArrayAssembly::AllocateParts()
{
}

void LGND_200_14String_FiberArrayAssembly::UnallocateParts()
{
  delete fFiberCore;
  delete fFiberCladdingInner;
  delete fFiberCladdingOuter;
  delete fFiberWLSCoating;
  delete fFiberSiPMTop;
  delete fFiberSiPMBot;
  delete fFiberReflector;

  delete fFiberCoreCurved;
  delete fFiberCladdingInnerCurved;
  delete fFiberCladdingOuterCurved;
  delete fFiberWLSCoatingCurved;
}

void LGND_200_14String_FiberArrayAssembly::Place(G4ThreeVector* assemPosition,G4RotationMatrix* assemRotation, G4LogicalVolume* motherLogical)
{

  //Placing fibers on a 60 sides polygon
  //for Outer array
  //Inner array placed below
  int nSides = 60;
  double phi = (180-360./nSides);
  double theta = (90-phi/2);
  //keep the angles in radians
  phi = 2*pi*phi/360.;
  theta = 2*pi*theta/360.;

  G4double R = fPlacementRadius;
  G4double fiberRadius = 200*mm;
  G4double curvedR = fPlacementRadius - fiberRadius-0.25*mm;
  int nFibers = 1620;//972 for inner
  //Skip one fiber per side in order to fit them all
  //add in the fibers to the total number
  nFibers += nSides;
  double deltaTheta = 2*pi/nFibers;
  if(fName.contains("Outer")){
    G4cout<<nSides<<" sides polygon has interior angle of "<<phi<<", and outward facing angle of "<<theta<<G4endl;
    G4cout<<"Placing "<<nFibers-nSides<<" fibers"<<G4endl;
  }

  double placementAngle = 0,placementTheta = 0;
  bool debugBool = false;
  //Nth side of the N-gon
  int N = 0;
  for(int i = 0; i < nFibers && fName.contains("Outer"); i++){
    G4double x1 = 0,y1 = 0,z1 = 0,r1 = 0,fiberLength = 0;
    G4double deltaZ = 10*mm;
    if((N+3)%4 == 0) deltaZ = 3.33*mm;
    else if((N+2)%4 == 0) deltaZ = -3.33*mm;
    else if((N+1)%4 == 0) deltaZ = -10*mm;

    fiberLength = fLength - deltaZ/2.;

    //declare part to be placed
    fFiberCore = new LGND_FiberCore(fName+"FiberCore_"+to_string(i),"000-001",fiberLength,fShape);
    fFiberCladdingInner = new LGND_FiberCladding(fName+"FiberCladdingInner_"+to_string(i),"000-002",fiberLength,fShape,"PMMA");
    fFiberCladdingOuter = new LGND_FiberCladding(fName+"FiberCladdingOuter_"+to_string(i),"000-002",fiberLength,fShape,"Fluor-acrylic");
    fFiberWLSCoating = new LGND_FiberWLSCoating(fName+"FiberWLSCoating_"+to_string(i),"000-003",fiberLength,fShape);
    //note SiPM have different length than fibers
    fFiberSiPMTop = new LGND_FiberSiPM(fName+"FiberSiPMTop_"+to_string(i),"000-004",0.1*mm,fShape);

    fFiberCoreCurved = new LGND_FiberCoreCurved(fName+"FiberCoreCurved_"+to_string(i),"000-006",fiberRadius,fShape,0.5*pi);
    fFiberCladdingInnerCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingInnerCurved_"+to_string(i),"000-007",fiberRadius,fShape,"PMMA",0.5*pi);
    fFiberCladdingOuterCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingOuterCurved_"+to_string(i),"000-008",fiberRadius,fShape,"Fluor-acrylic",0.5*pi);
    fFiberWLSCoatingCurved = new LGND_FiberWLSCoatingCurved(fName+"FiberWLSCoatingCurved_"+to_string(i),"000-009",fiberRadius,fShape,0.5*pi);
    fFiberSiPMBot = new LGND_FiberSiPM(fName+"FiberSiPMBot_"+to_string(i),"000-004",0.1*mm,fShape);

    G4ThreeVector * placementVector = new G4ThreeVector(0);
    G4ThreeVector * placementCurvedVector = new G4ThreeVector(0);
    G4RotationMatrix* rotationFiber = new G4RotationMatrix();

    rotationFiber->rotateZ(-placementTheta-theta);
    //Rotate the fiber down,
    //orginally the fiber lays in the x-y plane
    //Calculate the slope and intercept of the the Nth side of the polygon
    double m;
    if(placementAngle <= 2*theta)
      m = (sin(2*theta)-sin(0))/(cos(2*theta)-cos(0));
    else
      m = (sin(2*theta+placementTheta)-sin(placementTheta))/(cos(2*theta+placementTheta)-cos(placementTheta));
    double b = R*(sin(placementTheta)-m*cos(placementTheta));
    //Straight fiber coordiantes
    //Convert a line into R and theta coordiantes
    //Fibers are not place uniformly on polygon side,
    //because we are using R and theta, maybe there is a generalize coordinate for polygons?
    r1 = b/(sin(placementAngle)-m*cos(placementAngle));
    x1 = r1*cos(placementAngle);
    y1 = r1*sin(placementAngle);
    z1 += deltaZ;

    fFiberCore->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* corePhysical = fFiberCore->GetPhysicalVolume();
    if(debugBool) corePhysical->CheckOverlaps(1000,0,true);
    //if(i%10 == 0) G4cout<<"/vis/scene/add/volume "<<corePhysical->GetName()<<G4endl;

    fFiberCladdingInner->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* claddingInnerPhysical = fFiberCladdingInner->GetPhysicalVolume();
    if(debugBool) claddingInnerPhysical->CheckOverlaps(1000,0,true);

    fFiberCladdingOuter->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* claddingOuterPhysical = fFiberCladdingOuter->GetPhysicalVolume();
    if(debugBool) claddingOuterPhysical->CheckOverlaps(1000,0,true);

    fFiberWLSCoating->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* wlsPhysical = fFiberWLSCoating->GetPhysicalVolume();
    if(debugBool) wlsPhysical->CheckOverlaps(1000,0,true);
    
    z1 += fiberLength+fFiberSiPMTop->GetLength();
    fFiberSiPMTop->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* SiPMTopPhysical = fFiberSiPMTop->GetPhysicalVolume();
    if(debugBool) SiPMTopPhysical->CheckOverlaps(1000,0,true);

    //Curved Fiber Coordiantes
    //We do not want lines radial to the N-Gon side, rather we want lines perpendicular to the N-gon side
    G4double x2 = 0,y2 = 0,z2 = 0,r2 = 0;
    //Intercept for inner radius polygon side
    double c = curvedR*(sin(placementTheta)-m*cos(placementTheta));
    //equation for line perpendicular to the N-gon side
    //slope is -1/m, intercept is y1-x1/(-m)
    double m_1 = -1./m;
    double d = y1 +x1/m;
    //remember that rotation is not communaticative
    G4RotationMatrix* rotationCurvedFiber = new G4RotationMatrix();
    rotationCurvedFiber->rotateZ(-placementTheta-theta);
    rotationCurvedFiber->rotateX(pi/2);

    //Where does the perpendicular line intercept the inner polygon line?
    x2 = (c-d)/(m_1-m);
    y2 = x2*m+c;
    z2 = -fiberLength+deltaZ;
    //z2 = -fiberLength;
    fFiberCoreCurved->Place(new G4ThreeVector(x2,y2,z2),rotationCurvedFiber,motherLogical);
    G4VPhysicalVolume* curvedPhysical = fFiberCoreCurved->GetPhysicalVolume();
    if(debugBool) curvedPhysical->CheckOverlaps(1000,0,true);
    //if(i%10 == 0) G4cout<<"/vis/scene/add/volume "<<curvedPhysical->GetName()<<G4endl;

    fFiberCladdingInnerCurved->Place(new G4ThreeVector(x2,y2,z2),rotationCurvedFiber,motherLogical);
    G4VPhysicalVolume* claddingInnerCurvedPhysical = fFiberCladdingInnerCurved->GetPhysicalVolume();
    if(debugBool) claddingInnerCurvedPhysical->CheckOverlaps(1000,0,true);

    fFiberCladdingOuterCurved->Place(new G4ThreeVector(x2,y2,z2),rotationCurvedFiber,motherLogical);
    G4VPhysicalVolume* claddingOuterCurvedPhysical = fFiberCladdingOuterCurved->GetPhysicalVolume();
    if(debugBool) claddingOuterCurvedPhysical->CheckOverlaps(1000,0,true);

    fFiberWLSCoatingCurved->Place(new G4ThreeVector(x2,y2,z2),rotationCurvedFiber,motherLogical); 
    G4VPhysicalVolume* wlsCurvedPhysical = fFiberWLSCoatingCurved->GetPhysicalVolume();
    if(debugBool) wlsCurvedPhysical->CheckOverlaps(1000,0,true);
    
    G4RotationMatrix* rotationSiPM = new G4RotationMatrix();
    rotationSiPM->rotateZ(-placementTheta-theta);
    rotationSiPM->rotateY(pi/2);
    //find a point down the perpendicular line that is half the SiPM length down the line
    G4double l = fFiberSiPMBot->GetLength();
    double sign = -1;
    //if(m > 0) sign = 1;
    if(placementAngle > pi/2 && placementAngle < 3*pi/2) sign = 1;
    //if(placementAngle > 3*pi/2 && placementAngle < 2*pi) sign = 1;
    G4double x3 = (sign*sqrt(l*l*(m_1*m_1+1))+m_1*m_1*x2+x2)/(m_1*m_1+1);
    G4double y3 = x3*m_1+d;
    fFiberSiPMBot->Place(new G4ThreeVector(x3,y3,z2-fiberRadius),rotationSiPM,motherLogical);
    G4VPhysicalVolume* SiPMBotPhysical = fFiberSiPMBot->GetPhysicalVolume();
    if(debugBool) SiPMBotPhysical->CheckOverlaps(1000,0,true);
  
    placementAngle += deltaTheta;
    if(placementAngle > (2*theta+placementTheta) && placementAngle > 2*theta){
      //skip a fiber placement
      placementTheta += 2*theta;
      placementAngle += deltaTheta;
      i++;
      N++;
    }
    //Setup LogicalBorderSurfaces
    //...
    //Top SiPM borders
    new G4LogicalBorderSurface("SiPMTop_core_"+to_string(x1),corePhysical,SiPMTopPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMTop_claddingInner_"+to_string(x1),claddingInnerPhysical,SiPMTopPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMTop_claddingOuter_"+to_string(x1),claddingOuterPhysical,SiPMTopPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMTop_TPB_"+to_string(x1),wlsPhysical,SiPMTopPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));

    //Bottom SiPM borders
    new G4LogicalBorderSurface("SiPMBot_core_"+to_string(x1),curvedPhysical,SiPMBotPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMBot_claddingInner_"+to_string(x1),claddingInnerCurvedPhysical,SiPMBotPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMBot_claddingOuter_"+to_string(x1),claddingOuterCurvedPhysical,SiPMBotPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMBot_TPB_"+to_string(x1),wlsCurvedPhysical,SiPMBotPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
  }

  //Placing fibers on a 36 sides polygon
  //for Inner array
  //Inner array placed below
  if(fName.contains("Outer")) return;
  nSides = 36;
  phi = (180-360./nSides);
  theta = (90-phi/2);
  G4cout<<nSides<<" sides polygon has interior angle of "<<phi<<", and outward facing angle of "<<theta<<G4endl;
  //keep the angles in radians
  phi = 2*pi*phi/360.;
  theta = 2*pi*theta/360.;

  //972 -> 27 fibers per side
  nFibers = 936;//26 fibers per side...Need an even amount since fibers wrap around
  deltaTheta = 2*pi/nFibers;
  G4cout<<"Placing "<<nFibers<<" fibers in the Inner Radius"<<G4endl;

  placementAngle = 0,placementTheta = 0;

  debugBool = false;//true;
  //Nth side of the N-gon
  G4double xPrev = 0,yPrev = 0,zPrev = 0,rPrev = 0;
  for(int i = 0; i < nFibers && fName.contains("Inner"); i++){
    //declare part to be placed
    fFiberCore = new LGND_FiberCore(fName+"FiberCore_"+to_string(i),"000-001",fLength,fShape);
    fFiberCladdingInner = new LGND_FiberCladding(fName+"FiberCladdingInner_"+to_string(i),"000-002",fLength,fShape,"PMMA");
    fFiberCladdingOuter = new LGND_FiberCladding(fName+"FiberCladdingOuter_"+to_string(i),"000-002",fLength,fShape,"Fluor-acrylic");
    fFiberWLSCoating = new LGND_FiberWLSCoating(fName+"FiberWLSCoating_"+to_string(i),"000-003",fLength,fShape);
    //note SiPM have different length than fibers
    fFiberSiPMTop = new LGND_FiberSiPM(fName+"FiberSiPMTop_"+to_string(i),"000-004",0.1*mm,fShape);
    fFiberReflector = new LGND_FiberSiPM(fName+"FiberSiPMBot_"+to_string(i),"000-005",0.1*mm,fShape);

    G4ThreeVector * placementVector = new G4ThreeVector(0);
    G4RotationMatrix* rotationFiber = new G4RotationMatrix();

    rotationFiber->rotateZ(-placementTheta-theta);
    //Rotate the fiber down,
    //orginally the fiber lays in the x-y plane

    G4double x1 = 0,y1 = 0,z1 = 0,r1 = 0;
    //Calculate the slope and intercept of the the Nth side of the polygon
    double m;
    if(placementAngle <= 2*theta)
      m = (sin(2*theta)-sin(0))/(cos(2*theta)-cos(0));
    else
      m = (sin(2*theta+placementTheta)-sin(placementTheta))/(cos(2*theta+placementTheta)-cos(placementTheta));
    double b = R*(sin(placementTheta)-m*cos(placementTheta));
    //Straight fiber coordiantes
    //Convert a line into R and theta coordiantes
    //Fibers are not place uniformly on polygon side,
    //because we are using R and theta, maybe there is a generalize coordinate for polygons?
    r1 = b/(sin(placementAngle)-m*cos(placementAngle));
    x1 = r1*cos(placementAngle);
    y1 = r1*sin(placementAngle);

    fFiberCore->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* corePhysical = fFiberCore->GetPhysicalVolume();
    if(debugBool) corePhysical->CheckOverlaps(1000,0,true);
    //if(i%10 == 0) G4cout<<"/vis/scene/add/volume "<<corePhysical->GetName()<<G4endl;

    fFiberCladdingInner->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* claddingInnerPhysical = fFiberCladdingInner->GetPhysicalVolume();
    if(debugBool) claddingInnerPhysical->CheckOverlaps(1000,0,true);

    fFiberCladdingOuter->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* claddingOuterPhysical = fFiberCladdingOuter->GetPhysicalVolume();
    if(debugBool) claddingOuterPhysical->CheckOverlaps(1000,0,true);

    fFiberWLSCoating->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* wlsPhysical = fFiberWLSCoating->GetPhysicalVolume();
    if(debugBool) wlsPhysical->CheckOverlaps(1000,0,true);
    
    z1 += fLength+fFiberSiPMTop->GetLength();
    fFiberSiPMTop->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* SiPMTopPhysical = fFiberSiPMTop->GetPhysicalVolume();

    z1 = -fLength-fFiberSiPMTop->GetLength();
    //fFiberReflector->Place(new G4ThreeVector(x1,y1,z1),rotationFiber,motherLogical);
    G4VPhysicalVolume* ReflectorPhysical = fFiberReflector->GetPhysicalVolume();
    if(debugBool) ReflectorPhysical->CheckOverlaps(1000,0,true);

    //if(debugBool) SiPMTopPhysical->CheckOverlaps(1000,0,true);

    //place curved fiber on the odd numbered fiber
    //Curved fibers do not work when paired to the nearest neighbor because
    //the radius is much to tight
    if((i+1)%2 == 0){
      G4double x2 = 0,y2 =0,z2 = 0,r2 = 0;
      //center of fiber is the mid point between the previous fiber and the current fiber
      x2 = (x1+xPrev)/2;
      y2 = m*x2+b;
      z2 = -fLength;
      //Spacing between fibers changes because x1,y1 are sampled uniformly from a circle rather than polygon
      //thus...need to calculate spacing (r2) for each curved fiber
      r2 = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
      fFiberCoreCurved = new LGND_FiberCoreCurved(fName+"FiberCoreCurved_"+to_string(i),"000-006",r2,fShape,pi);
      fFiberCladdingInnerCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingInnerCurved_"+to_string(i),"000-007",r2,fShape,"PMMA",pi);
      fFiberCladdingOuterCurved = new LGND_FiberCladdingCurved(fName+"FiberCladdingOuterCurved_"+to_string(i),"000-008",r2,fShape,"Fluor-acrylic",pi);
      fFiberWLSCoatingCurved = new LGND_FiberWLSCoatingCurved(fName+"FiberWLSCoatingCurved_"+to_string(i),"000-009",r2,fShape,pi);
      
      G4RotationMatrix* rotationCurvedFiber = new G4RotationMatrix();
      rotationCurvedFiber->rotateZ(-placementTheta-theta+pi/2);
      rotationCurvedFiber->rotateX(pi/2);

      fFiberCoreCurved->Place(new G4ThreeVector(x2,y2,z2),rotationCurvedFiber,motherLogical);
      G4VPhysicalVolume* curvedPhysical = fFiberCoreCurved->GetPhysicalVolume();
      if(debugBool) curvedPhysical->CheckOverlaps(1000,0,true);
      //if((i+1)%10 == 0) G4cout<<"/vis/scene/add/volume "<<curvedPhysical->GetName()<<G4endl;
     
      fFiberCladdingInnerCurved->Place(new G4ThreeVector(x2,y2,z2),rotationCurvedFiber,motherLogical);
      G4VPhysicalVolume* claddingInnerCurvedPhysical = fFiberCladdingInnerCurved->GetPhysicalVolume();
      if(debugBool) claddingInnerCurvedPhysical->CheckOverlaps(1000,0,true);

      fFiberCladdingOuterCurved->Place(new G4ThreeVector(x2,y2,z2),rotationCurvedFiber,motherLogical);
      G4VPhysicalVolume* claddingOuterCurvedPhysical = fFiberCladdingOuterCurved->GetPhysicalVolume();
      if(debugBool) claddingOuterCurvedPhysical->CheckOverlaps(1000,0,true);
      
      fFiberWLSCoatingCurved->Place(new G4ThreeVector(x2,y2,z2),rotationCurvedFiber,motherLogical); 
      G4VPhysicalVolume* wlsCurvedPhysical = fFiberWLSCoatingCurved->GetPhysicalVolume();
      if(debugBool) wlsCurvedPhysical->CheckOverlaps(1000,0,true);
    }
    xPrev = x1;
    yPrev = y1;
    zPrev = z1;
    placementAngle += deltaTheta;
    if(placementAngle > (2*theta+placementTheta) && placementAngle > 2*theta){
      placementTheta += 2*theta;
      N++;
    }
    
    //Top SiPM borders
    new G4LogicalBorderSurface("SiPMTop_core_"+to_string(x1),corePhysical,SiPMTopPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMTop_claddingInner_"+to_string(x1),claddingInnerPhysical,SiPMTopPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMTop_claddingOuter_"+to_string(x1),claddingOuterPhysical,SiPMTopPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));
    new G4LogicalBorderSurface("SiPMTop_TPB_"+to_string(x1),wlsPhysical,SiPMTopPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberToSiPM"));

    /*
    //Bot Reflector borders
    new G4LogicalBorderSurface("Reflector_core_"+to_string(x1),
        corePhysical,ReflectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberEndToLAr"));
    new G4LogicalBorderSurface("Reflector_claddingInner_"+to_string(x1),
        claddingInnerPhysical,ReflectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberEndToLAr"));
    new G4LogicalBorderSurface("Reflector_claddingOuter_"+to_string(x1),
        claddingOuterPhysical,ReflectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberEndToLAr"));
    new G4LogicalBorderSurface("Reflector_TPB_"+to_string(x1),
        wlsPhysical,ReflectorPhysical,LGND_200_OpticalSurfaces::GetOpticalSurface("FiberEndToLAr"));
    */
  }

  
}
