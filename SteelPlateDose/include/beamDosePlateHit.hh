#ifndef beamDosePlateHit_h
#define beamDosePlateHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh" // FOR MT

class beamDosePlateHit : public G4VHit
{
public:

  beamDosePlateHit();
  beamDosePlateHit(const beamDosePlateHit&);
  virtual ~beamDosePlateHit();

  const beamDosePlateHit& operator=(const beamDosePlateHit&);
  G4int operator==(const beamDosePlateHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  inline void AddEdep (G4double de) { edep += de; };
      
  G4double GetEdep()    { return edep; };      
      
private:
  G4double edep;    
};



typedef G4THitsCollection<beamDosePlateHit> beamDosePlateHitsCollection;

extern G4ThreadLocal G4Allocator<beamDosePlateHit>* beamDosePlateHitAllocator;

inline void* beamDosePlateHit::operator new(size_t)
{
  if(!beamDosePlateHitAllocator)
      beamDosePlateHitAllocator = new G4Allocator<beamDosePlateHit>;
  return (void *) beamDosePlateHitAllocator->MallocSingle();
}

inline void beamDosePlateHit::operator delete(void *aHit)
{
  beamDosePlateHitAllocator -> FreeSingle((beamDosePlateHit*) aHit);
}

#endif
