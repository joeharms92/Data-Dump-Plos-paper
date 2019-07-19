#include "ansiCNRRun.hh"
#include "ansiCNRAnalysis.hh"
#include "G4Run.hh"
#include "G4Event.hh"


ansiCNRRun::ansiCNRRun()
{}

ansiCNRRun::~ansiCNRRun()
{}

void ansiCNRRun::RecordEvent(const G4Event* evt)
{
/*  G4int photonCount[8];
  for (G4int i=0;i<8;i++){
    photonCount[i] = fAnalysis->GetNPhotons(i);
  }
*/
  G4Run::RecordEvent(evt);
}

void ansiCNRRun::Merge(const G4Run* aRun)
{
//  const ansiCNRRun* localRun = static_cast<const ansiCNRRun*> (aRun);
  G4Run::Merge(aRun);
}
