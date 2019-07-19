#ifndef beamDoseActionInitialization_h
#define beamDoseActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"

/// Action initialization class.
///
class beamDoseDetectorConstruction;

class beamDoseActionInitialization : public G4VUserActionInitialization
{
  public:
    beamDoseActionInitialization(beamDoseDetectorConstruction*, G4String, G4double, G4int);
    virtual ~beamDoseActionInitialization();

    static beamDoseActionInitialization* Instance();
    virtual void BuildForMaster() const;
    virtual void Build() const;

private:
    static beamDoseActionInitialization* fgInstance;
    beamDoseDetectorConstruction* fDetector;
    G4String fSource;
    G4double fSteelZ;
    G4int fRunID;
};

#endif

