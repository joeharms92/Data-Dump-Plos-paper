#include "beamDoseHumanPhantomHit.hh"
#include "G4UnitsTable.hh"


// THIS IS NECESSARY FOR MT MODE
G4ThreadLocal G4Allocator<beamDoseHumanPhantomHit>* beamDoseHumanPhantomHitAllocator=0;

beamDoseHumanPhantomHit::beamDoseHumanPhantomHit()
 : G4VHit(),
   edep(0.)
 {}

beamDoseHumanPhantomHit::~beamDoseHumanPhantomHit() {}

beamDoseHumanPhantomHit::beamDoseHumanPhantomHit(const beamDoseHumanPhantomHit& right)
  : G4VHit()
{
  edep = right.edep;
}

const beamDoseHumanPhantomHit& beamDoseHumanPhantomHit::operator=(const beamDoseHumanPhantomHit& right)
{
  edep  = right.edep;
  return *this;
}

G4int beamDoseHumanPhantomHit::operator==(const beamDoseHumanPhantomHit& right) const
{
  return (this==&right) ? 1 : 0;
}