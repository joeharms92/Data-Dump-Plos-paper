#ifndef beamDosePrimaryGeneratorAction_h
#define beamDosePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class G4ParticleGun;
class G4Event;

class beamDoseDetectorConstruction;

class beamDosePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  beamDosePrimaryGeneratorAction(beamDoseDetectorConstruction*, G4String);    
  virtual ~beamDosePrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* event);
  
  // set methods
  void SetRandomFlag(G4bool value);

private:

	G4ThreeVector worldSize;
	G4double * GetLENREnergyDist();
	G4double * GetLENRProbDist();
	G4double * GetBremEnergyDist6();
	G4double * GetBremProbDist6_Cu();
	G4double * GetBremProbDist6_W();
	G4double * GetBremProbDist6_CuW();
	G4double * GetBremEnergyDist9();
	G4double * GetBremProbDist9_Cu();
	G4double * GetBremProbDist9_W();
	G4double * GetBremProbDist9_CuW();

	G4ParticleGun*             				fParticleGun; // G4 particle gun
	beamDoseDetectorConstruction* 			fDet;
	G4String fBeam;

	G4double * energy;
	G4double * prob;

};

//------------------------------------------------------------------------------

#endif


