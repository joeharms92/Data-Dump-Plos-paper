#ifndef beamDoseHumanPhantomSD_h
#define beamDoseHumanPhantomSD_h 1

#include "G4VSensitiveDetector.hh"
#include "beamDoseHumanPhantomHit.hh"

class G4Step;

class beamDoseHumanPhantomSD : public G4VSensitiveDetector
{
  public:
      beamDoseHumanPhantomSD(const G4String& name, 
                       const G4String& hitsCollectionName);
     virtual ~beamDoseHumanPhantomSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
 
 private:
      beamDoseHumanPhantomHitsCollection* collection;
};
#endif

