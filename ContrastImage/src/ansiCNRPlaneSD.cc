#include "ansiCNRPlaneSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ansiCNRPlaneSD::ansiCNRPlaneSD(
                          const G4String& name, 
                          const G4String& hitsCollectionName,
                          G4int numDets)
  : G4VSensitiveDetector(name),
    fansiCNRPlaneHitsCollection(0),
    fNumDets(numDets)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ansiCNRPlaneSD::~ansiCNRPlaneSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ansiCNRPlaneSD::Initialize(G4HCofThisEvent* hitsCE)
{
  // Create hits collection
  fansiCNRPlaneHitsCollection 
    = new ansiCNRPlaneHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hitsCE->AddHitsCollection( hcID, fansiCNRPlaneHitsCollection ); 

  // Create hits
  for (G4int i = 0; i < fNumDets; i++){
    fansiCNRPlaneHitsCollection->insert(new ansiCNRPlaneHit());
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool ansiCNRPlaneSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4Track* aTrack = aStep->GetTrack();


  if(aTrack->GetDefinition() != G4Gamma::GammaDefinition()) return false;

  G4TouchableHistory* touchable
      = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());

  G4int detID = touchable->GetReplicaNumber(1);
  ansiCNRPlaneHit* hit = (*fansiCNRPlaneHitsCollection)[detID];

  //ansiCNRPlaneHit* hitTotal = (*fansiCNRPlaneHitsCollection)[1];

  hit->AddHit(detID, aTrack->GetKineticEnergy());

  aTrack->SetTrackStatus(fStopAndKill);

  return true;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ansiCNRPlaneSD::EndOfEvent(G4HCofThisEvent*)
{}

//------------------------------------------------------------------------------