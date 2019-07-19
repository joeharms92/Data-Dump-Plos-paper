#include "beamDoseEventAction.hh"
#include "beamDoseAnalysis.hh"
#include "beamDoseSD.hh"
#include "beamDoseHit.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include "G4ios.hh"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <math.h>


//------------------------------------------------------------------------------

beamDoseEventAction::beamDoseEventAction()
 : G4UserEventAction(), 
   fDetHCID(-1)
{}

//------------------------------------------------------------------------------

beamDoseEventAction::~beamDoseEventAction()
{}


//------------------------------------------------------------------------------

void beamDoseEventAction::BeginOfEventAction(const G4Event*)
{
  beamDoseAnalysis* myAna = beamDoseAnalysis::GetAnalysis();
  myAna->ClearIncidentFlag();

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if (fDetHCID<0)
    fDetHCID = SDman->GetCollectionID("DetCollection");  
}

void beamDoseEventAction::EndOfEventAction(const G4Event* event)
{

  if (fDetHCID == -1) {
    fDetHCID = G4SDManager::GetSDMpointer()->
                            GetCollectionID("DetCollection");
  }

    beamDoseHitsCollection* fHitsCollection = 
                                      GetHitsCollection(fDetHCID, event);
    beamDoseHit* DetHit = (*fHitsCollection)[0];

    G4double ke = DetHit->GetKE();
    if (ke){
      beamDoseAnalysis* ana = beamDoseAnalysis::GetAnalysis();
      ana->FillHist(ke);
    } 

}  

//-------------------------------------------------

beamDoseHitsCollection* beamDoseEventAction::GetHitsCollection(
                        G4int hcID, const G4Event* event) const
{
  beamDoseHitsCollection* hitsCollection 
    = static_cast<beamDoseHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("beamDoseEventAction::GetHitsCollection()",
      "GetHitsCollection", FatalException, msg);
  }  

  return hitsCollection;

}
