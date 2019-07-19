#include "beamDosePlateSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

beamDosePlateSD::beamDosePlateSD(const G4String& name,
                         const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name),
    collection(0)
{
 collectionName.insert(hitsCollectionName);
}

beamDosePlateSD::~beamDosePlateSD()
{}

void beamDosePlateSD::Initialize(G4HCofThisEvent* HCE)
{
  collection = new beamDosePlateHitsCollection(
                                SensitiveDetectorName,collectionName[0]); 

  static G4int HCID = -1;
  if(HCID<0) HCID = GetCollectionID(0);

  HCE->AddHitsCollection( HCID, collection ); 

  collection->insert( new beamDosePlateHit() );
}


G4bool beamDosePlateSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{  
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep==0.) return false;

  beamDosePlateHit* newHit = (*collection)[0];

  newHit->AddEdep(edep);
  
 return true;
}

void beamDosePlateSD::EndOfEvent(G4HCofThisEvent*)
{}
