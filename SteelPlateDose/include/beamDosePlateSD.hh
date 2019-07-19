#ifndef beamDosePlateSD_h
#define beamDosePlateSD_h 1

#include "G4VSensitiveDetector.hh"
#include "beamDosePlateHit.hh"

class G4Step;

class beamDosePlateSD : public G4VSensitiveDetector
{
  public:
      beamDosePlateSD(const G4String& name, 
                       const G4String& hitsCollectionName);
     virtual ~beamDosePlateSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
 
 private:
      beamDosePlateHitsCollection* collection;
};
#endif

