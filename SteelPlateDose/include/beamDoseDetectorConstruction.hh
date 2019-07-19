#ifndef beamDoseDetectorConstruction_h
#define beamDoseDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"

#include "G4NistManager.hh"
class G4Box;
class G4Tubs;
class G4VPhysicalVolume;
class G4LogicalVolume;

class beamDoseMaterials;

class beamDoseDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    beamDoseDetectorConstruction();
    virtual ~beamDoseDetectorConstruction();
    static beamDoseDetectorConstruction* Instance();

  public:
    G4VPhysicalVolume* Construct();
    void ConstructSDandField();
    void BuildWorld();
    void BuildContainer();

    G4ThreeVector GetWorldSize() {return worldSize; };

  private:
    static beamDoseDetectorConstruction* fgInstance;
    beamDoseMaterials * materials;

    G4ThreeVector       containerSize;
    G4ThreeVector       innerContainerSize;
    G4ThreeVector       plateSize;
    G4ThreeVector       worldSize;
    G4ThreeVector       containerPos;

    G4Box*             worldS;
    G4Box*             containerS;
    G4Box*             innerContainerS;
    G4Box*             plateS;

    G4LogicalVolume*    worldLV;
    G4LogicalVolume*    containerLV;
    G4LogicalVolume*    innerContainerLV;
    G4LogicalVolume*    plateLV;

    G4VPhysicalVolume*      worldPV;
    G4VPhysicalVolume*      containerPV;
    G4VPhysicalVolume*      innerContainerPV;
    G4VPhysicalVolume*      platePV;


  private:
    G4VPhysicalVolume* ConstructGeom();
};

//------------------------------------------------------------------------------

#endif

