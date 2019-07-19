#include "ansiCNRPlaneHit.hh"

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"

#include "G4ios.hh"
#include <iomanip>

G4ThreadLocal G4Allocator<ansiCNRPlaneHit>* ansiCNRPlaneHitAllocator = 0;

//-------------------------------------------------

ansiCNRPlaneHit::ansiCNRPlaneHit()
  : G4VHit()
{
  for (G4int i = 0; i < 70; i++){
    energyDep[i] = 0;
  }
}

//-------------------------------------------------

ansiCNRPlaneHit::~ansiCNRPlaneHit()
{}

//-------------------------------------------------

ansiCNRPlaneHit::ansiCNRPlaneHit(const ansiCNRPlaneHit& right)
: G4VHit()
{
  for (G4int i = 0; i < 70; i++){
    energyDep[i] = right.energyDep[i];
  }
}

//-------------------------------------------------

const ansiCNRPlaneHit& ansiCNRPlaneHit::operator=(const ansiCNRPlaneHit& right)
{
  for (G4int i = 0; i < 70; i++){
    energyDep[i] = right.energyDep[i];
  }

  return *this;
}

//-------------------------------------------------

G4int ansiCNRPlaneHit::operator==(const ansiCNRPlaneHit& right) const
{
  return ( this == &right) ? 1 : 0;
}

//-------------------------------------------------

void ansiCNRPlaneHit::AddHit(G4int detNum, G4double energy) 
{
  energyDep[detNum]+=energy;
}