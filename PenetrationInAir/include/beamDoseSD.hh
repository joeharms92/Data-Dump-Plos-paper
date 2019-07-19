#ifndef beamDoseSD_h
#define beamDoseSD_h 1

#include "G4VSensitiveDetector.hh"
#include "beamDoseHit.hh"

class G4Step;

class beamDoseSD : public G4VSensitiveDetector
{
  public:
      beamDoseSD(const G4String& name, 
                       const G4String& hitsCollectionName);
     virtual ~beamDoseSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
 
 private:
      beamDoseHitsCollection* collection;
};
#endif

