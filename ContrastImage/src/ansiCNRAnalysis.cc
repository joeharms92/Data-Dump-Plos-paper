#include "G4AutoDelete.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "ansiCNRAnalysis.hh"

#include <string>

//Select format of output here
#include "g4root.hh"

G4ThreadLocal G4int ansiCNRAnalysis::fincidentFlag = false;
G4ThreadLocal ansiCNRAnalysis* the_analysis = 0;

//----------------------------------------------------------------

ansiCNRAnalysis* ansiCNRAnalysis::GetAnalysis()
{
  if (!the_analysis)
    {
      the_analysis = new ansiCNRAnalysis();
      G4AutoDelete::Register(the_analysis);
    }
  return the_analysis;
}

//----------------------------------------------------------------

ansiCNRAnalysis::ansiCNRAnalysis()
{}

//----------------------------------------------------------------

ansiCNRAnalysis::~ansiCNRAnalysis()
{}

//----------------------------------------------------------------

void ansiCNRAnalysis::Book()
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  //mgr->OpenFile("ansiCNRCherenkov.root");
  mgr->SetFirstHistoId(0);

  for (G4int i = 0; i < 70; i++){
    mgr->CreateH1("Det"+std::to_string(i)+"", "",1500,0.35,15.5);
  }
}

//----------------------------------------------------------------

void ansiCNRAnalysis::FillHisto(G4int id, G4double energy)
{
  //if (!fincidentFlag)
    //{
      G4AnalysisManager* mgr = G4AnalysisManager::Instance();
      mgr->FillH1(id, energy);
      fincidentFlag = true;
    //}
}

//----------------------------------------------------------------
void ansiCNRAnalysis::Update()
{
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ansiCNRAnalysis::Clear()
{
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ansiCNRAnalysis::Save(const G4String& fname)
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  //if (fname != "master")
    mgr->OpenFile(fname.c_str());
  //else
    //mgr->OpenFile(outputFile.c_str());

  mgr->Write();
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ansiCNRAnalysis::Close()
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  mgr->CloseFile();
  return;
}
