#ifndef beamDoseAnalysis_h
#define beamDoseAnalysis_h

#include "G4ThreeVector.hh"
#include <tools/histo/h1d>
#include <tools/histo/h2d>


#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class beamDoseAnalysisMessenger;

class beamDoseAnalysis {
public:
  ~beamDoseAnalysis();

  static beamDoseAnalysis* GetAnalysis();

  void Book();
  void EndOfRun();

  void Update();
  void Clear();
  void Save(const G4String&);
  void Close();

  void FillHisto(G4double);

  void ClearIncidentFlag();

private:
  beamDoseAnalysis();
  DISALLOW_COPY_AND_ASSIGN(beamDoseAnalysis);

  //Histograms handlers


  static G4ThreadLocal G4int fincidentFlag;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void beamDoseAnalysis::ClearIncidentFlag()
{
  fincidentFlag = false;
}

#endif