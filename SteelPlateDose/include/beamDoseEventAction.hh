#ifndef beamDoseEventAction_h
#define beamDoseEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "beamDosePlateHit.hh"

class beamDoseEventAction : public G4UserEventAction
{
  public:
    beamDoseEventAction();
    ~beamDoseEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

  private:
    beamDosePlateHitsCollection* GetWaterHitsCollection(G4int, const G4Event*) const;
    G4int fDetHCID;

};
                     
//------------------------------------------------------------------------------

#endif

    