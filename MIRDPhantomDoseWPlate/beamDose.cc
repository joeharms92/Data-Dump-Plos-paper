#include "beamDoseDetectorConstruction.hh"
#include "beamDoseActionInitialization.hh"
#include "FTFP_BERT.hh"
#include "FTFP_BERT_HP.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_BERT.hh"

#include "globals.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIcommand.hh"

#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//------------------------------------------------------------------------------

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " brem [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
           << G4endl;
  }
}

//------------------------------------------------------------------------------

#include <fstream>
#include <sstream>

using namespace std;

ofstream outfile("/dev/fd/3", ios::out|ios::app);

//------------------------------------------------------------------------------

int main(int argc, char** argv)
{

  // Choose the Random engine
  
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
    long seeds[2];
    long systime;
    systime = time(NULL);
    seeds[0] = (long) systime;
    seeds[1] = (long) (systime*G4UniformRand());
    G4Random::setTheSeeds(seeds); 

  G4String macro;
  G4String session;
  G4String sessionUI;
  G4String beamType;
  G4int runID = 0;

  #ifdef G4MULTITHREADED
    G4int nThreads = 4;
  #endif
  for ( G4int i=1; i<argc; i=i+2 ) {
    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
    else if ( G4String(argv[i]) == "-run" ) runID = G4UIcommand::ConvertToInt(argv[i+1]);
    else if ( G4String(argv[i]) == "-beam" ) {
      beamType = argv[i+1];
    }
#ifdef G4MULTITHREADED
    else if ( G4String(argv[i]) == "-t" ) {nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
    }
#endif
    else {
      PrintUsage();
      return 1;
    }
  } 

#ifdef G4MULTITHREADED
  G4MTRunManager * runManager = new G4MTRunManager;
  if ( nThreads > 0 ) { 
    runManager->SetNumberOfThreads(nThreads);
  }  
#else
  G4RunManager * runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  beamDoseDetectorConstruction* detConstruction 
  = new beamDoseDetectorConstruction();
  
  runManager->SetUserInitialization(detConstruction);
  //runManager->SetUserInitialization(new QGSP_BERT);

  // put back to hp before submission to cluster
  //runManager->SetUserInitialization(new FTFP_BERT_HP);
  runManager->SetUserInitialization(new FTFP_BERT);
  
  beamDoseActionInitialization* actionInitialization
    = new beamDoseActionInitialization(detConstruction, beamType, runID);
  runManager->SetUserInitialization(actionInitialization);

  // Initialize G4 kernel
  runManager->Initialize();

#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( macro.size() ) {
    // batch mode
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+macro);
  }
  else  {  
    // interactive mode : define UI session
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv, sessionUI);
  
  #ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute vis.mac"); 
  #else
      UImanager->ApplyCommand("/control/execute beamDose.in"); 
  #endif
  
    if (ui->IsGUI())
      UImanager->ApplyCommand("/control/execute gui.mac");
   ui->SessionStart();
    delete ui;
#endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !

 #ifdef G4VIS_USE
   delete visManager;
  #endif
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
