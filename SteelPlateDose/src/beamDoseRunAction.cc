#include "beamDoseAnalysis.hh"
#include "beamDoseRunAction.hh"
#include "beamDoseRun.hh"

#include "G4Run.hh"
#include "G4MTRunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"
#include "G4Threading.hh"

#include <stdio.h>
#include <iostream>
#include "G4ios.hh"

using namespace std;

//------------------------------------------------------------------------------
beamDoseRunAction::beamDoseRunAction(G4String beam, G4int runID)
: G4UserRunAction(),
  fSource(beam),
  fRunID(runID)
{}

//------------------------------------------------------------------------------

beamDoseRunAction::~beamDoseRunAction()
{}

//------------------------------------------------------------------------------

void beamDoseRunAction::BeginOfRunAction(const G4Run*)
{
  beamDoseAnalysis* myAna = beamDoseAnalysis::GetAnalysis();
  myAna->Clear();
  myAna->Book();
}

//------------------------------------------------------------------------------

G4Run* beamDoseRunAction::GenerateRun()
{ 
  return new beamDoseRun;
}

//------------------------------------------------------------------------------

void beamDoseRunAction::EndOfRunAction(const G4Run*)
{
  beamDoseAnalysis* myAna = beamDoseAnalysis::GetAnalysis();
  G4String fileTitle = "BodyDose" + fSource + "_run" + to_string(fRunID);
  myAna->Save(fileTitle + ".root");
}

