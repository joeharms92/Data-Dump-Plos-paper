#include "beamDoseEventAction.hh"
#include "beamDoseAnalysis.hh"
#include "beamDosePlateSD.hh"
#include "beamDosePlateHit.hh"

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
{  
/*  beamDoseAnalysis* myAna = beamDoseAnalysis::GetAnalysis();
  myAna->ClearIncidentFlag();

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if (fDetHCID<0)
    fDetHCID = SDman->GetCollectionID("DetCollection");  */
}


//------------------------------------------------------------------------------

void beamDoseEventAction::BeginOfEventAction(const G4Event*)
{}

//-------------------------------------------------

beamDosePlateHitsCollection* beamDoseEventAction::GetWaterHitsCollection(
                        G4int hcID, const G4Event* event) const
{
  beamDosePlateHitsCollection* hitsCollection 
    = static_cast<beamDosePlateHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("beamDoseEventAction::GetHitsCollection()",
      "GetHitsCollection", FatalException, msg);
  }  

  return hitsCollection;

}

//------------------------------------------------------------------------------

void beamDoseEventAction::EndOfEventAction(const G4Event* event)
{

  if (fDetHCID == -1) {
    fDetHCID = G4SDManager::GetSDMpointer()->
                            GetCollectionID("DetCollection");
  }
  beamDosePlateHitsCollection* fHitsCollection = 
                                    GetWaterHitsCollection(fDetHCID, event);

  beamDosePlateHit* DetHit = (*fHitsCollection)[0];

  G4double detEdep = DetHit->GetEdep();
  if (detEdep != 0){
    beamDoseAnalysis* ana = beamDoseAnalysis::GetAnalysis();
    ana->FillHisto(detEdep);
  }

}  

