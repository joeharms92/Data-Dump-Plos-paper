#ifndef beamDoseBodySD_h
#define beamDoseBodySD_h 1

#include "G4VSensitiveDetector.hh"
#include "beamDoseBodyHit.hh"

class G4Step;

class beamDoseBodySD : public G4VSensitiveDetector
{
  public:
      beamDoseBodySD(const G4String& name, 
                       const G4String& hitsCollectionName);
     virtual ~beamDoseBodySD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
 
 private:
      beamDoseBodyHitsCollection* collection;
};
#endif

