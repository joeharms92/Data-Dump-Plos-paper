#ifndef ansiCNRRun_h
#define ansiCNRRun_h 1
#include "G4Run.hh"
#include "globals.hh"

class G4Run;
class ansiCNRAnalysis;
class G4Event;


class ansiCNRRun: public G4Run
{
  public:
    ansiCNRRun();
    virtual ~ansiCNRRun();
    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);

  private:
//    ansiCNRAnalysis* fAnalysis;

};

#endif
