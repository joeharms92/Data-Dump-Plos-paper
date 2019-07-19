#include "beamDoseBodyHit.hh"
#include "G4UnitsTable.hh"


// THIS IS NECESSARY FOR MT MODE
G4ThreadLocal G4Allocator<beamDoseBodyHit>* beamDoseBodyHitAllocator=0;

beamDoseBodyHit::beamDoseBodyHit()
 : G4VHit(),
   edep(0.)
 {}

beamDoseBodyHit::~beamDoseBodyHit() {}

beamDoseBodyHit::beamDoseBodyHit(const beamDoseBodyHit& right)
  : G4VHit()
{
  edep = right.edep;
}

const beamDoseBodyHit& beamDoseBodyHit::operator=(const beamDoseBodyHit& right)
{
  edep  = right.edep;
  return *this;
}

G4int beamDoseBodyHit::operator==(const beamDoseBodyHit& right) const
{
  return (this==&right) ? 1 : 0;
}