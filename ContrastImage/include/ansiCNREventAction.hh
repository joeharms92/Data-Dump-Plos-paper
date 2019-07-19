#ifndef ansiCNREventAction_h
#define ansiCNREventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "ansiCNRPlaneHit.hh"

class ansiCNREventAction : public G4UserEventAction
{
  public:
    ansiCNREventAction();
    virtual ~ansiCNREventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

private:
    G4int FindSlice(G4double);

    ansiCNRPlaneHitsCollection* GetHitsCollection(G4int, const G4Event*) const;
    G4int fPlaneHCID;
};
                     
//------------------------------------------------------------------------------

#endif

    
