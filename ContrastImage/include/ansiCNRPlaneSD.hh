#ifndef ansiCNRPlaneSD_h
#define ansiCNRPlaneSD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "ansiCNRPlaneHit.hh"

class G4HCofThisEvent;
class G4Step;

class ansiCNRPlaneSD : public G4VSensitiveDetector {
public:
  ansiCNRPlaneSD(const G4String&, const G4String&, G4int);
  virtual ~ansiCNRPlaneSD();

  virtual void Initialize(G4HCofThisEvent*);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void EndOfEvent(G4HCofThisEvent*);

private:
  ansiCNRPlaneHitsCollection* fansiCNRPlaneHitsCollection;
  G4int fNumDets;

};

#endif