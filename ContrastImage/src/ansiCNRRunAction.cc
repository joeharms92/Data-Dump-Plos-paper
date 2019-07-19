#include "ansiCNRRunAction.hh"
#include "ansiCNRRun.hh"
#include "ansiCNRAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"


//------------------------------------------------------------------------------

ansiCNRRunAction::ansiCNRRunAction(G4int runID, G4int sliceID, G4String source)
 : G4UserRunAction(),
   fRunID(runID),
   fSliceNum(sliceID),
   fSource(source)
{}

//------------------------------------------------------------------------------

ansiCNRRunAction::~ansiCNRRunAction()
{}

//------------------------------------------------------------------------------

void ansiCNRRunAction::BeginOfRunAction(const G4Run*)
{
  ansiCNRAnalysis* myAna = ansiCNRAnalysis::GetAnalysis();
  myAna->Clear();
  myAna->Book();
}

//------------------------------------------------------------------------------

G4Run* ansiCNRRunAction::GenerateRun()
{ 
  return new ansiCNRRun;
}

//------------------------------------------------------------------------------

void ansiCNRRunAction::EndOfRunAction(const G4Run*)
{
  ansiCNRAnalysis* myAna = ansiCNRAnalysis::GetAnalysis();

  myAna->Save("Slice" + std::to_string(fSliceNum) + "_run"+std::to_string(fRunID) + "_" + fSource + ".root");

 }


