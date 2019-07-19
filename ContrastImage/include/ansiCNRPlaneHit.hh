#ifndef ansiCNRPlaneHit_h
#define ansiCNRPlaneHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

#include "tls.hh"

class ansiCNRPlaneHit : public G4VHit
{
  public: 
    ansiCNRPlaneHit();
    ansiCNRPlaneHit(const ansiCNRPlaneHit&);
    virtual ~ansiCNRPlaneHit();


    const ansiCNRPlaneHit& operator=(const ansiCNRPlaneHit&);
    G4int operator==(const ansiCNRPlaneHit&) const;

    inline void *operator new(size_t);
    inline void operator delete(void*);

    void AddHit(G4int, G4double);
    G4double GetEdep(G4int detID) {return energyDep[detID]; };

  private:
    G4double energyDep[70];

};


typedef G4THitsCollection<ansiCNRPlaneHit> ansiCNRPlaneHitsCollection;

extern G4ThreadLocal G4Allocator<ansiCNRPlaneHit>* ansiCNRPlaneHitAllocator;

inline void* ansiCNRPlaneHit::operator new(size_t)
{
  if(!ansiCNRPlaneHitAllocator)
    ansiCNRPlaneHitAllocator = new G4Allocator<ansiCNRPlaneHit>;
  void *hit;
  hit = (void *) ansiCNRPlaneHitAllocator->MallocSingle();
  return hit;
}

inline void ansiCNRPlaneHit::operator delete(void *hit)
{
  if (!ansiCNRPlaneHitAllocator)
    ansiCNRPlaneHitAllocator = new G4Allocator<ansiCNRPlaneHit>;
  ansiCNRPlaneHitAllocator->FreeSingle((ansiCNRPlaneHit*) hit);
}


#endif

