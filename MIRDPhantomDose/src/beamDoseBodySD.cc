#include "beamDoseBodySD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

beamDoseBodySD::beamDoseBodySD(const G4String& name,
                         const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name),
    collection(0)
{
 collectionName.insert(hitsCollectionName);
}

beamDoseBodySD::~beamDoseBodySD()
{}

void beamDoseBodySD::Initialize(G4HCofThisEvent* HCE)
{
  collection = new beamDoseBodyHitsCollection(
                                SensitiveDetectorName,collectionName[0]); 

  static G4int HCID = -1;
  if(HCID<0) HCID = GetCollectionID(0);

  HCE->AddHitsCollection( HCID, collection ); 

  collection->insert( new beamDoseBodyHit() );
}


G4bool beamDoseBodySD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{  
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep==0.) return false;

  beamDoseBodyHit* newHit = (*collection)[0];

  newHit->AddEdep(edep);
  
 return true;
}

void beamDoseBodySD::EndOfEvent(G4HCofThisEvent*)
{}
