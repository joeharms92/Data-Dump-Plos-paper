#include "beamDoseRun.hh"
#include <atomic>

namespace {
  std::atomic_int g_ctr(0);
}
beamDoseRun::beamDoseRun() {
  aDummyCounter = g_ctr++;
}

void beamDoseRun::Merge(const G4Run* other ) {
  G4Run::Merge(other);
  aDummyCounter += static_cast<const beamDoseRun*>(other)->aDummyCounter;
}
