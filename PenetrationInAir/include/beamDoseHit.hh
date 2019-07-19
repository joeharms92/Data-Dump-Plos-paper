#ifndef beamDoseHit_h
#define beamDoseHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh" // FOR MT

class beamDoseHit : public G4VHit
{
public:

  beamDoseHit();
  beamDoseHit(const beamDoseHit&);
  virtual ~beamDoseHit();

  const beamDoseHit& operator=(const beamDoseHit&);
  G4int operator==(const beamDoseHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  inline void AddKE (G4double de) { ke += de; };
      
  G4double GetKE()    { return ke; };      
      
private:
  G4double ke;    
};



typedef G4THitsCollection<beamDoseHit> beamDoseHitsCollection;

extern G4ThreadLocal G4Allocator<beamDoseHit>* beamDoseHitAllocator;

inline void* beamDoseHit::operator new(size_t)
{
  if(!beamDoseHitAllocator)
      beamDoseHitAllocator = new G4Allocator<beamDoseHit>;
  return (void *) beamDoseHitAllocator->MallocSingle();
}

inline void beamDoseHit::operator delete(void *aHit)
{
  beamDoseHitAllocator -> FreeSingle((beamDoseHit*) aHit);
}

#endif
