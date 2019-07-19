#include "beamDoseSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

beamDoseSD::beamDoseSD(const G4String& name,
                         const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name),
    collection(0)
{
 collectionName.insert(hitsCollectionName);
}

beamDoseSD::~beamDoseSD()
{}

void beamDoseSD::Initialize(G4HCofThisEvent* HCE)
{
  collection = new beamDoseHitsCollection(
                                SensitiveDetectorName,collectionName[0]); 

  static G4int HCID = -1;
  if(HCID<0) HCID = GetCollectionID(0);

  HCE->AddHitsCollection( HCID, collection ); 

  collection->insert( new beamDoseHit() );
}


G4bool beamDoseSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{  
  G4double energy = aStep->GetTrack()->GetKineticEnergy();
  beamDoseHit* newHit = (*collection)[0];
  newHit->AddKE(energy);
  
 return true;
}

void beamDoseSD::EndOfEvent(G4HCofThisEvent*)
{}
