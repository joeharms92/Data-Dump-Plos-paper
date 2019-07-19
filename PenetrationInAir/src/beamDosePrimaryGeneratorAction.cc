#include "beamDosePrimaryGeneratorAction.hh"
#include "beamDoseDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"


beamDosePrimaryGeneratorAction::beamDosePrimaryGeneratorAction(
				beamDoseDetectorConstruction* detector, G4String beamType)
: 	G4VUserPrimaryGeneratorAction(),
	fParticleGun(0),
	fDet(detector),
	fBeam(beamType)
{
	G4int nofParticles = 1;
	fParticleGun = new G4ParticleGun(nofParticles);

	G4ParticleDefinition* particleDefinition 
		= G4ParticleTable::GetParticleTable()->FindParticle("gamma");

	fParticleGun->SetParticleDefinition(particleDefinition);	

	if (fBeam == "lenr") {
		energy = GetLENREnergyDist();
		prob = GetLENRProbDist();
	}
	else if (fBeam == "brem6_w") {
		energy = GetBremEnergyDist6();
		prob = GetBremProbDist6_W();
	}
	else if (fBeam == "brem9_w") {
		energy = GetBremEnergyDist9();
		prob = GetBremProbDist9_W();
	}	
	else{
		G4cout << "No beam type specified" << G4endl;
		G4cout << "Default beam is Brem 6 W" << G4endl;
		energy = GetBremEnergyDist6();
		prob = GetBremProbDist6_W();
  	}

  	worldSize = fDet->GetWorldSize();
}

beamDosePrimaryGeneratorAction::~beamDosePrimaryGeneratorAction()
{
	delete fParticleGun;
	delete[] energy;
	delete[] prob;
}

void beamDosePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	G4double particleEnergy;
	if (fBeam == "mps3_10"){
		particleEnergy = G4RandGauss::shoot(3, 0.1*3./2.35)*MeV;
	}
	else if (fBeam == "mps6_10"){
		particleEnergy = G4RandGauss::shoot(6, 0.1*6./2.35)*MeV;
	}
	else if (fBeam == "mps9_10"){
		particleEnergy = G4RandGauss::shoot(9, 0.1*9./2.35)*MeV;
	}
	else if (fBeam == "mps3_20"){
		particleEnergy = G4RandGauss::shoot(3, 0.2*3./2.35)*MeV;
	}
	else if (fBeam == "mps6_20"){
		particleEnergy = G4RandGauss::shoot(6, 0.2*6./2.35)*MeV;
	}
	else if (fBeam == "mps9_20"){
		particleEnergy = G4RandGauss::shoot(9, 0.2*9./2.35)*MeV;
	}
	else {
		G4double probRand = G4UniformRand();
		G4int counter = 0;
		while ( probRand > prob[counter]){
			counter++;
		}
		if (fBeam == "lenr") {
			particleEnergy = energy[counter];
		} else {
	 		particleEnergy = energy[counter] + (G4UniformRand()-0.5)*0.1*MeV;
		}
	}
	fParticleGun->SetParticleEnergy(particleEnergy);

  G4double posX, posY;
  posX = 6.*mm*(G4UniformRand() - 0.5);
  posY = 6.*mm*(G4UniformRand() - 0.5);
  
  fParticleGun->SetParticlePosition(G4ThreeVector(posX,posY,-worldSize.z()/2.));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

G4double * beamDosePrimaryGeneratorAction::GetLENREnergyDist()
{
	G4double * lenrEnergy = new G4double[7];
	lenrEnergy[0] = 0.511*MeV;
	lenrEnergy[1] = 0.954*MeV;
	lenrEnergy[2] = 1.678*MeV;
	lenrEnergy[3] = 4.438*MeV;
	lenrEnergy[4] = 6.505*MeV;
	lenrEnergy[5] = 8.95*MeV;
	lenrEnergy[6] = 15.1*MeV;
	return lenrEnergy;
}

G4double * beamDosePrimaryGeneratorAction::GetLENRProbDist()
{
	G4double * lenrProb = new G4double[7];
	lenrProb[0] = 0.181269;
	lenrProb[1] = 0.332326;
	lenrProb[2] = 0.60423;
	lenrProb[3] = 0.906344;
	lenrProb[4] = 0.930514;
	lenrProb[5] = 0.954683;
	lenrProb[6] = 1;
	return lenrProb;
}

G4double * beamDosePrimaryGeneratorAction::GetBremEnergyDist6()
{
	G4double * Brem6MVE = new G4double[60];
	Brem6MVE[0] = 0.05*MeV;
	Brem6MVE[1] = 0.15*MeV;
	Brem6MVE[2] = 0.25*MeV;
	Brem6MVE[3] = 0.35*MeV;
	Brem6MVE[4] = 0.45*MeV;
	Brem6MVE[5] = 0.55*MeV;
	Brem6MVE[6] = 0.65*MeV;
	Brem6MVE[7] = 0.75*MeV;
	Brem6MVE[8] = 0.85*MeV;
	Brem6MVE[9] = 0.95*MeV;
	Brem6MVE[10] = 1.05*MeV;
	Brem6MVE[11] = 1.15*MeV;
	Brem6MVE[12] = 1.25*MeV;
	Brem6MVE[13] = 1.35*MeV;
	Brem6MVE[14] = 1.45*MeV;
	Brem6MVE[15] = 1.55*MeV;
	Brem6MVE[16] = 1.65*MeV;
	Brem6MVE[17] = 1.75*MeV;
	Brem6MVE[18] = 1.85*MeV;
	Brem6MVE[19] = 1.95*MeV;
	Brem6MVE[20] = 2.05*MeV;
	Brem6MVE[21] = 2.15*MeV;
	Brem6MVE[22] = 2.25*MeV;
	Brem6MVE[23] = 2.35*MeV;
	Brem6MVE[24] = 2.45*MeV;
	Brem6MVE[25] = 2.55*MeV;
	Brem6MVE[26] = 2.65*MeV;
	Brem6MVE[27] = 2.75*MeV;
	Brem6MVE[28] = 2.85*MeV;
	Brem6MVE[29] = 2.95*MeV;
	Brem6MVE[30] = 3.05*MeV;
	Brem6MVE[31] = 3.15*MeV;
	Brem6MVE[32] = 3.25*MeV;
	Brem6MVE[33] = 3.35*MeV;
	Brem6MVE[34] = 3.45*MeV;
	Brem6MVE[35] = 3.55*MeV;
	Brem6MVE[36] = 3.65*MeV;
	Brem6MVE[37] = 3.75*MeV;
	Brem6MVE[38] = 3.85*MeV;
	Brem6MVE[39] = 3.95*MeV;
	Brem6MVE[40] = 4.05*MeV;
	Brem6MVE[41] = 4.15*MeV;
	Brem6MVE[42] = 4.25*MeV;
	Brem6MVE[43] = 4.35*MeV;
	Brem6MVE[44] = 4.45*MeV;
	Brem6MVE[45] = 4.55*MeV;
	Brem6MVE[46] = 4.65*MeV;
	Brem6MVE[47] = 4.75*MeV;
	Brem6MVE[48] = 4.85*MeV;
	Brem6MVE[49] = 4.95*MeV;
	Brem6MVE[50] = 5.05*MeV;
	Brem6MVE[51] = 5.15*MeV;
	Brem6MVE[52] = 5.25*MeV;
	Brem6MVE[53] = 5.35*MeV;
	Brem6MVE[54] = 5.45*MeV;
	Brem6MVE[55] = 5.55*MeV;
	Brem6MVE[56] = 5.65*MeV;
	Brem6MVE[57] = 5.75*MeV;
	Brem6MVE[58] = 5.85*MeV;
	Brem6MVE[59] = 5.95*MeV;

	return Brem6MVE;
}

G4double * beamDosePrimaryGeneratorAction::GetBremProbDist6_W()
{
	G4double * Brem6MVProb = new G4double[60];
	Brem6MVProb[0] = 6.01948e-06;
	Brem6MVProb[1] = 0.000240626;
	Brem6MVProb[2] = 0.00104297;
	Brem6MVProb[3] = 0.00547014;
	Brem6MVProb[4] = 0.0214776;
	Brem6MVProb[5] = 0.0533823;
	Brem6MVProb[6] = 0.0912255;
	Brem6MVProb[7] = 0.134439;
	Brem6MVProb[8] = 0.180356;
	Brem6MVProb[9] = 0.227101;
	Brem6MVProb[10] = 0.27361;
	Brem6MVProb[11] = 0.319072;
	Brem6MVProb[12] = 0.362819;
	Brem6MVProb[13] = 0.404452;
	Brem6MVProb[14] = 0.443815;
	Brem6MVProb[15] = 0.480905;
	Brem6MVProb[16] = 0.515779;
	Brem6MVProb[17] = 0.548423;
	Brem6MVProb[18] = 0.578972;
	Brem6MVProb[19] = 0.607615;
	Brem6MVProb[20] = 0.63442;
	Brem6MVProb[21] = 0.659486;
	Brem6MVProb[22] = 0.68299;
	Brem6MVProb[23] = 0.705051;
	Brem6MVProb[24] = 0.725755;
	Brem6MVProb[25] = 0.745093;
	Brem6MVProb[26] = 0.763239;
	Brem6MVProb[27] = 0.780319;
	Brem6MVProb[28] = 0.796374;
	Brem6MVProb[29] = 0.811417;
	Brem6MVProb[30] = 0.825577;
	Brem6MVProb[31] = 0.838879;
	Brem6MVProb[32] = 0.851407;
	Brem6MVProb[33] = 0.863235;
	Brem6MVProb[34] = 0.874313;
	Brem6MVProb[35] = 0.88475;
	Brem6MVProb[36] = 0.89456;
	Brem6MVProb[37] = 0.903787;
	Brem6MVProb[38] = 0.912467;
	Brem6MVProb[39] = 0.920615;
	Brem6MVProb[40] = 0.928282;
	Brem6MVProb[41] = 0.935478;
	Brem6MVProb[42] = 0.942231;
	Brem6MVProb[43] = 0.948541;
	Brem6MVProb[44] = 0.954412;
	Brem6MVProb[45] = 0.959924;
	Brem6MVProb[46] = 0.96505;
	Brem6MVProb[47] = 0.969814;
	Brem6MVProb[48] = 0.974205;
	Brem6MVProb[49] = 0.978237;
	Brem6MVProb[50] = 0.981949;
	Brem6MVProb[51] = 0.985346;
	Brem6MVProb[52] = 0.98839;
	Brem6MVProb[53] = 0.991091;
	Brem6MVProb[54] = 0.993462;
	Brem6MVProb[55] = 0.995518;
	Brem6MVProb[56] = 0.997231;
	Brem6MVProb[57] = 0.998585;
	Brem6MVProb[58] = 0.999549;
	Brem6MVProb[59] = 1;
	return Brem6MVProb;
}

G4double * beamDosePrimaryGeneratorAction::GetBremEnergyDist9()
{
	G4double * Brem9MVE = new G4double[90];Brem9MVE[0] = 0.05*MeV;
	Brem9MVE[1] = 0.15*MeV;
	Brem9MVE[2] = 0.25*MeV;
	Brem9MVE[3] = 0.35*MeV;
	Brem9MVE[4] = 0.45*MeV;
	Brem9MVE[5] = 0.55*MeV;
	Brem9MVE[6] = 0.65*MeV;
	Brem9MVE[7] = 0.75*MeV;
	Brem9MVE[8] = 0.85*MeV;
	Brem9MVE[9] = 0.95*MeV;
	Brem9MVE[10] = 1.05*MeV;
	Brem9MVE[11] = 1.15*MeV;
	Brem9MVE[12] = 1.25*MeV;
	Brem9MVE[13] = 1.35*MeV;
	Brem9MVE[14] = 1.45*MeV;
	Brem9MVE[15] = 1.55*MeV;
	Brem9MVE[16] = 1.65*MeV;
	Brem9MVE[17] = 1.75*MeV;
	Brem9MVE[18] = 1.85*MeV;
	Brem9MVE[19] = 1.95*MeV;
	Brem9MVE[20] = 2.05*MeV;
	Brem9MVE[21] = 2.15*MeV;
	Brem9MVE[22] = 2.25*MeV;
	Brem9MVE[23] = 2.35*MeV;
	Brem9MVE[24] = 2.45*MeV;
	Brem9MVE[25] = 2.55*MeV;
	Brem9MVE[26] = 2.65*MeV;
	Brem9MVE[27] = 2.75*MeV;
	Brem9MVE[28] = 2.85*MeV;
	Brem9MVE[29] = 2.95*MeV;
	Brem9MVE[30] = 3.05*MeV;
	Brem9MVE[31] = 3.15*MeV;
	Brem9MVE[32] = 3.25*MeV;
	Brem9MVE[33] = 3.35*MeV;
	Brem9MVE[34] = 3.45*MeV;
	Brem9MVE[35] = 3.55*MeV;
	Brem9MVE[36] = 3.65*MeV;
	Brem9MVE[37] = 3.75*MeV;
	Brem9MVE[38] = 3.85*MeV;
	Brem9MVE[39] = 3.95*MeV;
	Brem9MVE[40] = 4.05*MeV;
	Brem9MVE[41] = 4.15*MeV;
	Brem9MVE[42] = 4.25*MeV;
	Brem9MVE[43] = 4.35*MeV;
	Brem9MVE[44] = 4.45*MeV;
	Brem9MVE[45] = 4.55*MeV;
	Brem9MVE[46] = 4.65*MeV;
	Brem9MVE[47] = 4.75*MeV;
	Brem9MVE[48] = 4.85*MeV;
	Brem9MVE[49] = 4.95*MeV;
	Brem9MVE[50] = 5.05*MeV;
	Brem9MVE[51] = 5.15*MeV;
	Brem9MVE[52] = 5.25*MeV;
	Brem9MVE[53] = 5.35*MeV;
	Brem9MVE[54] = 5.45*MeV;
	Brem9MVE[55] = 5.55*MeV;
	Brem9MVE[56] = 5.65*MeV;
	Brem9MVE[57] = 5.75*MeV;
	Brem9MVE[58] = 5.85*MeV;
	Brem9MVE[59] = 5.95*MeV;
	Brem9MVE[60] = 6.05*MeV;
	Brem9MVE[61] = 6.15*MeV;
	Brem9MVE[62] = 6.25*MeV;
	Brem9MVE[63] = 6.35*MeV;
	Brem9MVE[64] = 6.45*MeV;
	Brem9MVE[65] = 6.55*MeV;
	Brem9MVE[66] = 6.65*MeV;
	Brem9MVE[67] = 6.75*MeV;
	Brem9MVE[68] = 6.85*MeV;
	Brem9MVE[69] = 6.95*MeV;
	Brem9MVE[70] = 7.05*MeV;
	Brem9MVE[71] = 7.15*MeV;
	Brem9MVE[72] = 7.25*MeV;
	Brem9MVE[73] = 7.35*MeV;
	Brem9MVE[74] = 7.45*MeV;
	Brem9MVE[75] = 7.55*MeV;
	Brem9MVE[76] = 7.65*MeV;
	Brem9MVE[77] = 7.75*MeV;
	Brem9MVE[78] = 7.85*MeV;
	Brem9MVE[79] = 7.95*MeV;
	Brem9MVE[80] = 8.05*MeV;
	Brem9MVE[81] = 8.15*MeV;
	Brem9MVE[82] = 8.25*MeV;
	Brem9MVE[83] = 8.35*MeV;
	Brem9MVE[84] = 8.45*MeV;
	Brem9MVE[85] = 8.55*MeV;
	Brem9MVE[86] = 8.65*MeV;
	Brem9MVE[87] = 8.75*MeV;
	Brem9MVE[88] = 8.85*MeV;
	Brem9MVE[89] = 8.95*MeV;

	return Brem9MVE;
}

G4double * beamDosePrimaryGeneratorAction::GetBremProbDist9_W()
{
	G4double * Brem9MVProb = new G4double[90];
	Brem9MVProb[0] = 8.33485e-06;
	Brem9MVProb[1] = 0.000297938;
	Brem9MVProb[2] = 0.00121021;
	Brem9MVProb[3] = 0.00506639;
	Brem9MVProb[4] = 0.0178797;
	Brem9MVProb[5] = 0.0444387;
	Brem9MVProb[6] = 0.0738915;
	Brem9MVProb[7] = 0.107925;
	Brem9MVProb[8] = 0.144456;
	Brem9MVProb[9] = 0.182101;
	Brem9MVProb[10] = 0.220043;
	Brem9MVProb[11] = 0.257609;
	Brem9MVProb[12] = 0.294152;
	Brem9MVProb[13] = 0.329307;
	Brem9MVProb[14] = 0.362943;
	Brem9MVProb[15] = 0.395;
	Brem9MVProb[16] = 0.42545;
	Brem9MVProb[17] = 0.454341;
	Brem9MVProb[18] = 0.481673;
	Brem9MVProb[19] = 0.507546;
	Brem9MVProb[20] = 0.532003;
	Brem9MVProb[21] = 0.555197;
	Brem9MVProb[22] = 0.577122;
	Brem9MVProb[23] = 0.597932;
	Brem9MVProb[24] = 0.617603;
	Brem9MVProb[25] = 0.636303;
	Brem9MVProb[26] = 0.654046;
	Brem9MVProb[27] = 0.670868;
	Brem9MVProb[28] = 0.686855;
	Brem9MVProb[29] = 0.702034;
	Brem9MVProb[30] = 0.71647;
	Brem9MVProb[31] = 0.730224;
	Brem9MVProb[32] = 0.743285;
	Brem9MVProb[33] = 0.75571;
	Brem9MVProb[34] = 0.767564;
	Brem9MVProb[35] = 0.778872;
	Brem9MVProb[36] = 0.789639;
	Brem9MVProb[37] = 0.799932;
	Brem9MVProb[38] = 0.809761;
	Brem9MVProb[39] = 0.819139;
	Brem9MVProb[40] = 0.828115;
	Brem9MVProb[41] = 0.836682;
	Brem9MVProb[42] = 0.844882;
	Brem9MVProb[43] = 0.852739;
	Brem9MVProb[44] = 0.860258;
	Brem9MVProb[45] = 0.867445;
	Brem9MVProb[46] = 0.874337;
	Brem9MVProb[47] = 0.880955;
	Brem9MVProb[48] = 0.887286;
	Brem9MVProb[49] = 0.893346;
	Brem9MVProb[50] = 0.89915;
	Brem9MVProb[51] = 0.904737;
	Brem9MVProb[52] = 0.910075;
	Brem9MVProb[53] = 0.915199;
	Brem9MVProb[54] = 0.920112;
	Brem9MVProb[55] = 0.924811;
	Brem9MVProb[56] = 0.929322;
	Brem9MVProb[57] = 0.93364;
	Brem9MVProb[58] = 0.937791;
	Brem9MVProb[59] = 0.941777;
	Brem9MVProb[60] = 0.945605;
	Brem9MVProb[61] = 0.949256;
	Brem9MVProb[62] = 0.952768;
	Brem9MVProb[63] = 0.956127;
	Brem9MVProb[64] = 0.959337;
	Brem9MVProb[65] = 0.962401;
	Brem9MVProb[66] = 0.965332;
	Brem9MVProb[67] = 0.968151;
	Brem9MVProb[68] = 0.970832;
	Brem9MVProb[69] = 0.973385;
	Brem9MVProb[70] = 0.975817;
	Brem9MVProb[71] = 0.978131;
	Brem9MVProb[72] = 0.98032;
	Brem9MVProb[73] = 0.982393;
	Brem9MVProb[74] = 0.984351;
	Brem9MVProb[75] = 0.986194;
	Brem9MVProb[76] = 0.987932;
	Brem9MVProb[77] = 0.989554;
	Brem9MVProb[78] = 0.991064;
	Brem9MVProb[79] = 0.99246;
	Brem9MVProb[80] = 0.993754;
	Brem9MVProb[81] = 0.994929;
	Brem9MVProb[82] = 0.99599;
	Brem9MVProb[83] = 0.996938;
	Brem9MVProb[84] = 0.997763;
	Brem9MVProb[85] = 0.998478;
	Brem9MVProb[86] = 0.999065;
	Brem9MVProb[87] = 0.999531;
	Brem9MVProb[88] = 0.999856;
	Brem9MVProb[89] = 1;

	return Brem9MVProb;
}
