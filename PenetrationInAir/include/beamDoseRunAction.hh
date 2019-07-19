#ifndef beamDoseRunAction_h
#define beamDoseRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class beamDoseRunAction : public G4UserRunAction
{
  public:
    beamDoseRunAction(G4String, G4double, G4int);
    ~beamDoseRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual G4Run* GenerateRun();
    virtual void EndOfRunAction(const G4Run*);

  private:
    G4String      fSource;
    G4double    fSteelZ;
    G4int           fRunID;

//------------------------------------------------------------------------------
};
#endif

