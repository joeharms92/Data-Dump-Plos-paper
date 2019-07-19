#include "beamDoseActionInitialization.hh"
#include "beamDoseRunAction.hh"
#include "beamDoseEventAction.hh"
#include "beamDoseDetectorConstruction.hh"
#include "beamDosePrimaryGeneratorAction.hh"

#include "G4RunManager.hh"

//------------------------------------------------------------------------------

beamDoseActionInitialization* beamDoseActionInitialization::fgInstance = 0;

//------------------------------------------------------------------------------

beamDoseActionInitialization::beamDoseActionInitialization(beamDoseDetectorConstruction* detector,
                                      G4String sourceType, G4int runID)
 : G4VUserActionInitialization(),
   fDetector(detector),
   fSource(sourceType),
   fRunID(runID)
{
  fgInstance = this;
}

//------------------------------------------------------------------------------

beamDoseActionInitialization::~beamDoseActionInitialization()
{
  fgInstance = 0;
}

//------------------------------------------------------------------------------

beamDoseActionInitialization* beamDoseActionInitialization::Instance()
{
  return fgInstance;
}

void beamDoseActionInitialization::BuildForMaster() const
{
  SetUserAction(new beamDoseRunAction(fSource, fRunID));
}

//------------------------------------------------------------------------------

void beamDoseActionInitialization::Build() const
{
  beamDosePrimaryGeneratorAction* primaryGenerator = 
                                  new beamDosePrimaryGeneratorAction(fDetector, fSource);
  SetUserAction(primaryGenerator);

  beamDoseRunAction* runAction = new beamDoseRunAction(fSource, fRunID);
  SetUserAction(runAction);

  beamDoseEventAction* eventAction = new beamDoseEventAction();
  SetUserAction(eventAction);
}  

//------------------------------------------------------------------------------
