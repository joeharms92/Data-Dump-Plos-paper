#include "ansiCNREventAction.hh"
#include "ansiCNRAnalysis.hh"
#include "ansiCNRPlaneSD.hh"
#include "ansiCNRPlaneHit.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"

#include "Randomize.hh"
#include <iomanip>

//------------------------------------------------------------------------------

ansiCNREventAction::ansiCNREventAction()
 : G4UserEventAction(),
   fPlaneHCID(-1)
{}

//------------------------------------------------------------------------------

ansiCNREventAction::~ansiCNREventAction()
{}


//------------------------------------------------------------------------------

void ansiCNREventAction::BeginOfEventAction(const G4Event*)
{}

//-------------------------------------------------

ansiCNRPlaneHitsCollection* ansiCNREventAction::GetHitsCollection(
                        G4int hcID, const G4Event* event) const
{
  ansiCNRPlaneHitsCollection* hitsCollection 
    = static_cast<ansiCNRPlaneHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("ansiCNREventAction::GetHitsCollection()",
      "GetHitsCollection", FatalException, msg);
  }  

  return hitsCollection;

}

//------------------------------------------------------------------------------


void ansiCNREventAction::EndOfEventAction(const G4Event* event)
{
  if (fPlaneHCID == -1 ) {
    fPlaneHCID = G4SDManager::GetSDMpointer()->
                           GetCollectionID("planeHitsCollection");
  }

  ansiCNRPlaneHitsCollection* fHitsCollection = GetHitsCollection(fPlaneHCID, event);
  //ansiCNRPlaneHit* planeHit = (*fHitsCollection)[fHitsCollection->entries()-1];

  ansiCNRAnalysis* myAna = ansiCNRAnalysis::GetAnalysis();
  for (G4int i = 0; i < 70; i++){
    if ( (*fHitsCollection)[i]->GetEdep(i) != 0){
      myAna->FillHisto(i, (*fHitsCollection)[i]->GetEdep(i));
    }
  }

}  