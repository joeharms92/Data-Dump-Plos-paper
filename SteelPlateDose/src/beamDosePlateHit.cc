#include "beamDosePlateHit.hh"
#include "G4UnitsTable.hh"


// THIS IS NECESSARY FOR MT MODE
G4ThreadLocal G4Allocator<beamDosePlateHit>* beamDosePlateHitAllocator=0;

beamDosePlateHit::beamDosePlateHit()
 : G4VHit(),
   edep(0.)
 {}

beamDosePlateHit::~beamDosePlateHit() {}

beamDosePlateHit::beamDosePlateHit(const beamDosePlateHit& right)
  : G4VHit()
{
  edep = right.edep;
}

const beamDosePlateHit& beamDosePlateHit::operator=(const beamDosePlateHit& right)
{
  edep  = right.edep;
  return *this;
}

G4int beamDosePlateHit::operator==(const beamDosePlateHit& right) const
{
  return (this==&right) ? 1 : 0;
}