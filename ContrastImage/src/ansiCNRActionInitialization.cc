#include "ansiCNRActionInitialization.hh"
#include "ansiCNRPrimaryGeneratorAction.hh"
#include "ansiCNRDetectorConstruction.hh"

#include "ansiCNRRunAction.hh"
#include "ansiCNREventAction.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

//------------------------------------------------------------------------------

ansiCNRActionInitialization* ansiCNRActionInitialization::fgInstance = 0;

//------------------------------------------------------------------------------

ansiCNRActionInitialization::ansiCNRActionInitialization(
                    ansiCNRDetectorConstruction* detector, G4int runID, G4String sourceType, 
                    G4int sliceNo)
 : G4VUserActionInitialization(),
   fDetector(detector),
   runIndicator(runID),
   source(sourceType),
   fSliceNum(sliceNo)
{}

//------------------------------------------------------------------------------

ansiCNRActionInitialization::~ansiCNRActionInitialization()
{
  fgInstance = 0;
}

//------------------------------------------------------------------------------

ansiCNRActionInitialization* ansiCNRActionInitialization::Instance()
{
  return fgInstance;
}

//------------------------------------------------------------------------------


void ansiCNRActionInitialization::BuildForMaster() const
{
  SetUserAction(new ansiCNRRunAction(runIndicator, fSliceNum, source));
}

//------------------------------------------------------------------------------

void ansiCNRActionInitialization::Build() const
{
  //default source

  ansiCNRPrimaryGeneratorAction* primaryGenerator = new ansiCNRPrimaryGeneratorAction(
                            fDetector, source, fSliceNum);                        
  SetUserAction(primaryGenerator);

  ansiCNRRunAction* runAction = new ansiCNRRunAction(runIndicator, fSliceNum, source);
  SetUserAction(runAction);

  ansiCNREventAction* eventAction = new ansiCNREventAction();
  SetUserAction(eventAction);
}  

//------------------------------------------------------------------------------
