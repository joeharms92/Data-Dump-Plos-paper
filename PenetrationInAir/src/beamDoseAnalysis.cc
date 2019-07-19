#include "G4AutoDelete.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "beamDoseAnalysis.hh"

#include <string>

//Select format of output here
#include "g4root.hh"

G4ThreadLocal G4int beamDoseAnalysis::fincidentFlag = false;
G4ThreadLocal beamDoseAnalysis* the_analysis = 0;

//----------------------------------------------------------------

beamDoseAnalysis* beamDoseAnalysis::GetAnalysis()
{
  if (!the_analysis)
    {
      the_analysis = new beamDoseAnalysis();
      G4AutoDelete::Register(the_analysis);
    }
  return the_analysis;
}

beamDoseAnalysis::beamDoseAnalysis()
{}

beamDoseAnalysis::~beamDoseAnalysis()
{}

void beamDoseAnalysis::Book()
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  mgr->SetFirstHistoId(0);

  mgr->CreateH1("Spectrum", "", 15500, 0, 15.5);
  fluxCount = 0;
}

void beamDoseAnalysis::FillHist(G4double ke)
{
    G4AnalysisManager* mgr = G4AnalysisManager::Instance();
    mgr->FillH1(0, ke);
    fincidentFlag = true;
}

void beamDoseAnalysis::Update()
{
  return;
}

void beamDoseAnalysis::Clear()
{
  return;
}

void beamDoseAnalysis::Save(const G4String& fname)
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  mgr->OpenFile(fname.c_str());
  mgr->Write();
  return;
}

void beamDoseAnalysis::Close()
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  mgr->CloseFile();
  return;
}