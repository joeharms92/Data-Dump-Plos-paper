#ifndef beamDoseRun_h
#define beamDoseRun_h 1

#include <G4Run.hh>

//Dummy class to show how to use MPI merging of
//user defined G4Run. The dummycounter it's a unique number among threads.
//Merge actually sums the dummyCounter so for the global run that is  Sum(i, 0<i<Nt)
class beamDoseRun : public G4Run {
  friend class RunMerger;
public:
  beamDoseRun();
  virtual ~beamDoseRun() {}
  void Merge(const G4Run*);
  G4int GetCounter() const { return aDummyCounter; }
private:
  G4int aDummyCounter;
};
#endif //RUN_HH