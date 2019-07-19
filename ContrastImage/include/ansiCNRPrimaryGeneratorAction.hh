#ifndef ansiCNRPrimaryGeneratorAction_h
#define ansiCNRPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class ansiCNRDetectorConstruction;

class ansiCNRPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  ansiCNRPrimaryGeneratorAction(ansiCNRDetectorConstruction*, G4String, G4int);    
  virtual ~ansiCNRPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* event);
  
  // set methods
  void SetRandomFlag(G4bool value);

private:

	G4double * GetICSEnergyDist();
	G4double * GetICSProbDist();
	G4double * GetLENREnergyDist();
	G4double * GetLENRProbDist();
	G4double * GetBremEnergyDist4();
	G4double * GetBremProbDist4();
	G4double * GetBremEnergyDist6();
	G4double * GetBremProbDist6();
	G4double * GetBremEnergyDist9();
	G4double * GetBremProbDist9();
	G4double * GetBremEnergyDist15();
	G4double * GetBremProbDist15();
	G4double * GetPuBeEnergyDist();
	G4double * GetPuBeProbDist();

	G4ParticleGun*             					fParticleGun; // G4 particle gun
	ansiCNRDetectorConstruction* 			fDet;
	G4int 		   											fSliceNum;

	G4double * energy;
	G4double * prob;

};

//------------------------------------------------------------------------------

#endif


