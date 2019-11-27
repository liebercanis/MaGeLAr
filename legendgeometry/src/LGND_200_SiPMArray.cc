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
// CLASS IMPLEMENTATION:  LGND_200_SiPMArray.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 This is a theortical alterantive light readout for L-1000 in which the fibers are removed and the Cu radon shroud is covered with SiPMs

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
#include "legendgeometry/LGND_200_SiPMArray.hh"
#include "legendgeometry/LGND_Part.hh"
#include "legendgeometry/LGND_FiberSiPM.hh"
#include "legendgeometry/LGND_200_OpticalSurfaces.hh"

//---------------------------------------------------------------------------//

using namespace CLHEP;

LGND_200_SiPMArray::LGND_200_SiPMArray(G4String name,G4double placementRadius,G4double height):
fName(name),fPlacementRadius(placementRadius),fHeight(height)
{
;

}


void LGND_200_SiPMArray::Place(G4ThreeVector* assemPosition,G4RotationMatrix* assemRotation, G4LogicalVolume* motherLogical)
{
  
  G4double xOffSet = assemPosition->x(),yOffSet = assemPosition->y(),zOffSet = assemPosition->z();
  //Placing SiPMs placing inwards towards some Cylinder of height fHeight and radius fPlacmentRadius
  //Looking 12 mm x 12 mm SiPMs from Hamamatsu S13371 ~23-24% QE at 175 nm and ~10-15?
  //construct the part to initialize dimenisions
  LGND_FiberSiPM *SiPMPart = new LGND_FiberSiPM(fName+"SiPMArray_","000-004",0.1*mm,6.*mm,"square");
  G4double length = 2*SiPMPart->GetRadius();
  G4double thickness = 2*SiPMPart->GetLength();

  double zCoverage = .10;
  int nSegments = floor(2*fHeight*zCoverage/length) + 1;
  G4double deltaZ = 2*fHeight/nSegments;
 
  double coverage = .50;//% SiPM coverage
  G4double rSpacing = (0.5)*length/coverage;
  //G4double deltaAngle = 2.*asin(sqrt(2)*rSpacing/(2*fPlacementRadius));
  G4double deltaAngle = 2*atan(rSpacing/(fPlacementRadius - rSpacing));
  //find the closest interger number of fibers given a certain coverage
  int nSiPMs = floor(2*pi/deltaAngle) + 1;
  //force spacing and placeent radius to match new number of fibers
  deltaAngle = 2*pi/nSiPMs;
  //fPlacementRadius = sqrt(2)*rSpacing/(2*sin(deltaAngle/2.));
  fPlacementRadius = rSpacing*(1/tan(deltaAngle/2)+1);
  //G4cout<<fHeight - deltaZ*j<<G4endl;

  //G4cout<<"SiPM dimension is "<<length/mm<<" mm x"<<length/mm<<" mm and "<<thickness<<" mm thick"<<G4endl; 
  MGLog(routine)<<"Placing "<<nSiPMs<<" per ring and placing "<<nSegments<<" rings on the side of the copper shroud"<<endl;
  for(int j = 0; j < nSegments ; j++){
  G4double placementAngle = 0;
    for(int i = 0; i < nSiPMs; i++){
      int stringNum = i + j*nSiPMs;
      //Thin cover to be placed behind the SiPM to block light from being collected from the back
      LGND_FiberSiPM* SiPMCover = new LGND_FiberSiPM(fName+"SiPMCover_"+to_string(stringNum),"000-004",0.001*mm,6*mm,"square");
      //Physical SiPM for light detection
      SiPMPart = new LGND_FiberSiPM(fName+"SiPMArry_"+to_string(stringNum),"000-004",0.1*mm,6*mm,"square");
      G4RotationMatrix* rotationSiPM = new G4RotationMatrix();
      rotationSiPM->rotateZ(-placementAngle);
      rotationSiPM->rotateY(pi/2);
      G4double x1 = 0, y1 = 0,z1 = 0;
      x1 = fPlacementRadius*cos(placementAngle) + xOffSet;
      y1 = fPlacementRadius*sin(placementAngle) + yOffSet;
      z1 = fHeight - deltaZ*j + zOffSet;
      SiPMPart->Place(new G4ThreeVector(x1,y1,z1),rotationSiPM,motherLogical);
      G4VPhysicalVolume* SiPMPhysical = SiPMPart->GetPhysicalVolume();
      //SiPMPhysical->CheckOverlaps(1000,0,true);
      
      //Place SiPM covers behind SiPMs
      G4double x2 =0,y2 = 0,z2 = 0;
      x2 = (fPlacementRadius + SiPMCover->GetRadius())*cos(placementAngle) + xOffSet;
      y2 = (fPlacementRadius + SiPMCover->GetRadius())*sin(placementAngle) + yOffSet;
      z2 = fHeight - deltaZ*j + zOffSet;
      SiPMCover->Place(new G4ThreeVector(x2,y2,z2),rotationSiPM,motherLogical);
      G4VPhysicalVolume* SiPMCoverPhysical = SiPMCover->GetPhysicalVolume();
      //SiPMCoverPhysical->CheckOverlaps(1000,0,true);

      placementAngle += deltaAngle;
      //G4cout<<"/vis/scene/add/volume "<<SiPMPhysical->GetName()<<G4endl;
      //if(i > 10) break;
    }
  }

  //place bottom disk
  G4double deltaR = 10*length;
  G4double bottomR = deltaR;
  deltaAngle = 2*atan(rSpacing/(deltaR - rSpacing));
  int nBot = floor(fPlacementRadius/deltaR) ;
  nSiPMs = floor(2*pi/deltaAngle) + 1;
  deltaAngle = 2*pi/(nSiPMs - 1);
  deltaR = rSpacing*(1/tan(deltaAngle/2)+1);
   
  int SiPMCounter = 0;
  for(int j = 0; j < nBot;j++){
    double placementAngle = 0;
    for(int i = 0; i < nSiPMs; i++){
      //Thin cover to be placed behind the SiPM to block light from being collected from the back
      LGND_FiberSiPM* SiPMCover = new LGND_FiberSiPM(fName+"SiPMCoverBottom_"+to_string(SiPMCounter),"000-004",0.001*mm,6*mm,"square");
      //Physical SiPM for light detection
      SiPMPart = new LGND_FiberSiPM(fName+"SiPMArryBottom_"+to_string(SiPMCounter),"000-004",0.1*mm,6*mm,"square");
      G4RotationMatrix* rotationSiPM = new G4RotationMatrix();
      rotationSiPM->rotateZ(-placementAngle);
      G4double x1 = 0, y1 = 0,z1 = 0;
      x1 = bottomR*cos(placementAngle) + xOffSet;
      y1 = bottomR*sin(placementAngle) + yOffSet;
      z1 = -fHeight + zOffSet;
      //G4cout<<"R "<<bottomR/mm<<", ("<<x1<<","<<y1<<","<<z1<<"), nSiPMs "<<nSiPMs<<", nBot "<<j<<G4endl;
      SiPMPart->Place(new G4ThreeVector(x1,y1,z1),rotationSiPM,motherLogical);
      G4VPhysicalVolume* SiPMPhysical = SiPMPart->GetPhysicalVolume();
      //SiPMPhysical->CheckOverlaps(1000,0,true);
      //
      //Place SiPM covers behind SiPMs
      G4double x2 =0,y2 = 0,z2 = 0;
      x2 = (bottomR )*cos(placementAngle) + xOffSet;
      y2 = (bottomR )*sin(placementAngle) + yOffSet;
      z2 = fHeight - deltaZ*j + zOffSet + SiPMCover->GetRadius();
      SiPMCover->Place(new G4ThreeVector(x2,y2,z2),rotationSiPM,motherLogical);
      G4VPhysicalVolume* SiPMCoverPhysical = SiPMCover->GetPhysicalVolume();
      //SiPMCoverPhysical->CheckOverlaps(1000,0,true);
      placementAngle += deltaAngle;
      //G4cout<<"/vis/scene/add/volume "<<SiPMPhysical->GetName()<<G4endl;

      SiPMCounter++;
    }
    bottomR += deltaR;
    deltaAngle = 2.*atan(rSpacing/(bottomR - rSpacing));
    nSiPMs = floor(2*pi/deltaAngle) + 1;
    deltaAngle = 2*pi/(nSiPMs - 1);
    //re-calculate the placement radius to the radius that will
    //exactly fit nSiPMs
    bottomR = rSpacing*(1./tan(deltaAngle/2.)+1.);
  }

  MGLog(routine)<<"Placing "<<SiPMCounter<<" on the bottom of the copper shroud"<<endl;

}



