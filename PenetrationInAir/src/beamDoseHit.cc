#include "beamDoseHit.hh"
#include "G4UnitsTable.hh"


// THIS IS NECESSARY FOR MT MODE
G4ThreadLocal G4Allocator<beamDoseHit>* beamDoseHitAllocator=0;

beamDoseHit::beamDoseHit()
 : G4VHit(),
   ke(0.)
 {}

beamDoseHit::~beamDoseHit() {}

beamDoseHit::beamDoseHit(const beamDoseHit& right)
  : G4VHit()
{
  ke = right.ke;
}

const beamDoseHit& beamDoseHit::operator=(const beamDoseHit& right)
{
  ke  = right.ke;
  return *this;
}

G4int beamDoseHit::operator==(const beamDoseHit& right) const
{
  return (this==&right) ? 1 : 0;
}