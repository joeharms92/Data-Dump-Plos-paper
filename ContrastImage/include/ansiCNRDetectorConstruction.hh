#ifndef ansiCNRDetectorConstruction_h
#define ansiCNRDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"

class G4Box;
class G4Tubs;
class G4Trap;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class ansiCNRMaterials;

class ansiCNRDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    ansiCNRDetectorConstruction(G4int, G4int);
    virtual ~ansiCNRDetectorConstruction();
    static ansiCNRDetectorConstruction* Instance();

    G4ThreeVector GetWorldDims() { return worldSize; };

  public:

    G4VPhysicalVolume* Construct();
    void BuildWorld();
    void Buildcontainer();
    void BuildTestObject();
    void BuildPlane();
    void AssignVisualization();
    void ConstructSDandField();

  private:
    static ansiCNRDetectorConstruction* fgInstance;
    ansiCNRMaterials *materials;

// Dimensions
    G4int                       fSliceNum;
    const G4int             numSlices = 220;
    const G4int             numDets = 70;
    G4ThreeVector       containerSize;
    G4ThreeVector       detElSize;
    G4ThreeVector       detDummySize;
    G4ThreeVector       detSize;
    G4ThreeVector       detPos;
    G4ThreeVector       worldSize;
    G4ThreeVector       containerInteriorSize;
    G4double                waterRad;
    G4double                waterZ;
    G4double                rodRad;
    G4double                rodZ;
    G4ThreeVector       containerPos;

// Initializing Volumes

    // Solid volumes
    G4VSolid*      containerS;
    G4VSolid*      containerInteriorS;
    G4Tubs*         quartzS;
    G4Tubs*         waterS;
    G4Tubs*         rodS;
    G4Box*           worldS;
    G4Box*           detPlaneS;
    G4Box*           elementS;

    // Logical volumes
    G4LogicalVolume*    worldLV;
    G4LogicalVolume*    containerLV;
    G4LogicalVolume*    containerInteriorLV;
    G4LogicalVolume*    waterLV;
    G4LogicalVolume*    carbonLV;
    G4LogicalVolume*    alLV;
    G4LogicalVolume*    ironLV;
    G4LogicalVolume*    copperLV;
    G4LogicalVolume*    tungstenLV;
    G4LogicalVolume*    leadLV;
    G4LogicalVolume*    detPlaneLV;
    G4LogicalVolume*    elementLV;
    G4LogicalVolume*    crystalLV;

    // Physical volumes
    G4VPhysicalVolume*      worldPV;
    G4VPhysicalVolume*      containerPV;
    G4VPhysicalVolume*      containerInteriorPV;  
    G4VPhysicalVolume*      waterPV;
    G4VPhysicalVolume*      carbonPV;
    G4VPhysicalVolume*      alPV;
    G4VPhysicalVolume*      ironPV;
    G4VPhysicalVolume*      copperPV;
    G4VPhysicalVolume*      tungstenPV;
    G4VPhysicalVolume*      leadPV;
    G4VPhysicalVolume*      detPlanePV;
    G4VPhysicalVolume*      elementPV;
    G4VPhysicalVolume*      crystalPV;

};

//------------------------------------------------------------------------------

#endif

