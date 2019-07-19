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

//----------------------------------------------------------------

beamDoseAnalysis::beamDoseAnalysis()
{}

//----------------------------------------------------------------

beamDoseAnalysis::~beamDoseAnalysis()
{}

//----------------------------------------------------------------

void beamDoseAnalysis::Book()
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  //mgr->OpenFile("beamDoseCherenkov.root");
  mgr->SetFirstHistoId(0);

  mgr->CreateH1("BodyDose", "",1550,0,15.5);
}

//----------------------------------------------------------------

void beamDoseAnalysis::FillHisto(G4double energy)
{
  //if (!fincidentFlag)
    //{
      G4AnalysisManager* mgr = G4AnalysisManager::Instance();
      mgr->FillH1(0, energy);
      fincidentFlag = true;
    //}
}

//----------------------------------------------------------------
void beamDoseAnalysis::Update()
{
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void beamDoseAnalysis::Clear()
{
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void beamDoseAnalysis::Save(const G4String& fname)
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
void beamDoseAnalysis::Close()
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  mgr->CloseFile();
  return;
}
