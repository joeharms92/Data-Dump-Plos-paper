#ifndef ansiCNRActionInitialization_h
#define ansiCNRActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"


/// Action initialization class.
///
class ansiCNRDetectorConstruction;

class ansiCNRActionInitialization : public G4VUserActionInitialization
{
  public:
    ansiCNRActionInitialization(ansiCNRDetectorConstruction*, G4int, G4String, G4int);
    virtual ~ansiCNRActionInitialization();

    static ansiCNRActionInitialization* Instance();

    virtual void BuildForMaster() const;
    virtual void Build() const;

private:
    static ansiCNRActionInitialization*    fgInstance;
    ansiCNRDetectorConstruction*          fDetector;
    G4int                                              runIndicator;
    G4String                                        source;
    G4int                                              fSliceNum;
};

#endif

