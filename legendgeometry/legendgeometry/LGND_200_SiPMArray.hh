#ifndef _LGND_200_SIPMARRAY_HH
#define _LGND_200_SIPMARRAY_HH

#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4UIcommand.hh"

//---------------------------------------------------------------------------//
//
#include "io/MGLogger.hh"
#include "legendgeometry/LGND_Part.hh"
//

using namespace std;

class LGND_200_SiPMArray
{

  public:
    LGND_200_SiPMArray(G4String name,G4double placementRadius, G4double height);
    ~LGND_200_SiPMArray();

    void Place(G4ThreeVector* assemPosition, G4RotationMatrix* assemRotation,
                     G4LogicalVolume* motherLogical);
  private:
    G4double fPlacementRadius = 0;
    G4double fHeight = 0;
    G4String fName = "";
};
#endif
