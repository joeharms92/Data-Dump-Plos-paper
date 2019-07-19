#ifndef beamDoseBodyHit_h
#define beamDoseBodyHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh" // FOR MT

class beamDoseBodyHit : public G4VHit
{
public:

  beamDoseBodyHit();
  beamDoseBodyHit(const beamDoseBodyHit&);
  virtual ~beamDoseBodyHit();

  const beamDoseBodyHit& operator=(const beamDoseBodyHit&);
  G4int operator==(const beamDoseBodyHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  inline void AddEdep (G4double de) { edep += de; };
      
  G4double GetEdep()    { return edep; };      
      
private:
  G4double edep;    
};



typedef G4THitsCollection<beamDoseBodyHit> beamDoseBodyHitsCollection;

extern G4ThreadLocal G4Allocator<beamDoseBodyHit>* beamDoseBodyHitAllocator;

inline void* beamDoseBodyHit::operator new(size_t)
{
  if(!beamDoseBodyHitAllocator)
      beamDoseBodyHitAllocator = new G4Allocator<beamDoseBodyHit>;
  return (void *) beamDoseBodyHitAllocator->MallocSingle();
}

inline void beamDoseBodyHit::operator delete(void *aHit)
{
  beamDoseBodyHitAllocator -> FreeSingle((beamDoseBodyHit*) aHit);
}

#endif
