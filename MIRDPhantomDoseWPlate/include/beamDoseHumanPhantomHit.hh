#ifndef beamDoseHumanPhantomHit_h
#define beamDoseHumanPhantomHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh" // FOR MT

class beamDoseHumanPhantomHit : public G4VHit
{
public:

  beamDoseHumanPhantomHit();
  beamDoseHumanPhantomHit(const beamDoseHumanPhantomHit&);
  virtual ~beamDoseHumanPhantomHit();

  const beamDoseHumanPhantomHit& operator=(const beamDoseHumanPhantomHit&);
  G4int operator==(const beamDoseHumanPhantomHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  inline void AddEdep (G4double de) { edep += de; };
      
  G4double GetEdep()    { return edep; };      
      
private:
  G4double edep;    
};



typedef G4THitsCollection<beamDoseHumanPhantomHit> beamDoseHumanPhantomHitsCollection;

extern G4ThreadLocal G4Allocator<beamDoseHumanPhantomHit>* beamDoseHumanPhantomHitAllocator;

inline void* beamDoseHumanPhantomHit::operator new(size_t)
{
  if(!beamDoseHumanPhantomHitAllocator)
      beamDoseHumanPhantomHitAllocator = new G4Allocator<beamDoseHumanPhantomHit>;
  return (void *) beamDoseHumanPhantomHitAllocator->MallocSingle();
}

inline void beamDoseHumanPhantomHit::operator delete(void *aHit)
{
  beamDoseHumanPhantomHitAllocator -> FreeSingle((beamDoseHumanPhantomHit*) aHit);
}

#endif
