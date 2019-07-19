#ifndef ansiCNRRunAction_h
#define ansiCNRRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class ansiCNRRunAction : public G4UserRunAction
{
 public:
    ansiCNRRunAction(G4int, G4int, G4String);
    virtual ~ansiCNRRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    G4Run* GenerateRun();
    virtual void   EndOfRunAction(const G4Run*);


private:

  G4int fRunID;
  G4int fSliceNum;
  G4String fSource;

//------------------------------------------------------------------------------
};
#endif

