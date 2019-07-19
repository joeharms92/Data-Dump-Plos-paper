#ifndef ansiCNRAnalysis_h
#define ansiCNRAnalysis_h

#include "G4ThreeVector.hh"
#include <tools/histo/h1d>
#include <tools/histo/h2d>

#include <string>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class ansiCNRAnalysis {
public:
  ~ansiCNRAnalysis();

  static ansiCNRAnalysis* GetAnalysis();

  void Book();
  void EndOfRun();

  void Update();
  void Clear();
  void Save(const G4String& fname);
  void Close();

  void FillHisto(G4int, G4double);

  void ClearIncidentFlag();

private:
  ansiCNRAnalysis();
  DISALLOW_COPY_AND_ASSIGN(ansiCNRAnalysis);

  std::string histTitle;

  //Histograms handlers
  G4int fSpectrum;

  static G4ThreadLocal G4int fincidentFlag;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void ansiCNRAnalysis::ClearIncidentFlag()
{
  fincidentFlag = false;
}

#endif