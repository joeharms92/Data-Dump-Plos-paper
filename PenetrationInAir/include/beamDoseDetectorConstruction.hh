#ifndef beamDoseDetectorConstruction_h
#define beamDoseDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"

#include "G4NistManager.hh"

#include <map>

class G4VSolid;
class G4Box;
class G4Tubs;
class G4VPhysicalVolume;
class G4LogicalVolume;

class beamDoseMaterials;

class beamDoseDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    beamDoseDetectorConstruction(G4double);
    virtual ~beamDoseDetectorConstruction();
    static beamDoseDetectorConstruction* Instance();

  public:
    G4VPhysicalVolume* Construct();
    void ConstructSDandField();
    void BuildWorld();
    void BuildContainer();
    void BuildDetector();

    G4ThreeVector GetWorldSize() {return worldSize; };

  private:
    static beamDoseDetectorConstruction* fgInstance;
    beamDoseMaterials * materials;

    G4ThreeVector       containerSize;
    G4ThreeVector       innerContainerSize;
    G4ThreeVector       plateSize;
    G4ThreeVector       worldSize;
    G4ThreeVector       detSize;
    G4ThreeVector       detDummyElSize;
    G4ThreeVector       collimatorSize;
    G4ThreeVector       detVolumeSize;
    G4ThreeVector       containerPos;
    G4ThreeVector       detVolumePos;

    G4double reflThickness;
    G4double PMTLength;

    G4Box*             worldS;
    G4Box*             containerS;
    G4Box*             innerContainerS;
    G4Box*             plateS;
    G4Box*             detBlockS;
    G4Box*             collimatorS;
    G4VSolid*         reflS;
    G4VSolid*         detS;
    G4VSolid*         pmtS;

    G4LogicalVolume*    worldLV;
    G4LogicalVolume*    containerLV;
    G4LogicalVolume*    innerContainerLV;
    G4LogicalVolume*    plateLV;
    G4LogicalVolume*    detBlockLV;
    G4LogicalVolume*    collimatorLV;
    G4LogicalVolume*    reflLV;
    G4LogicalVolume*    detLV;
    G4LogicalVolume*    pmtLV;

    G4VPhysicalVolume*      worldPV;
    G4VPhysicalVolume*      containerPV;
    G4VPhysicalVolume*      innerContainerPV;
    G4VPhysicalVolume*      platePV;
    G4VPhysicalVolume*      detBlockPV;
    G4VPhysicalVolume*      collimator1PV;
    G4VPhysicalVolume*      collimator2PV;
    G4VPhysicalVolume*      reflPV;
    G4VPhysicalVolume*      detPV;
    G4VPhysicalVolume*      pmtPV;

  private:
    G4double fSteelZ;
    G4VPhysicalVolume* ConstructGeom();
};

//------------------------------------------------------------------------------

#endif

