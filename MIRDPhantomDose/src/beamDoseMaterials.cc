#include "G4Isotope.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4OpticalSurface.hh"

#include "beamDoseMaterials.hh"
#include "G4NistManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

beamDoseMaterials *beamDoseMaterials::Materials = 0;

beamDoseMaterials::beamDoseMaterials() 
{
  CreateMaterials();
  Materials = this;
}

beamDoseMaterials::~beamDoseMaterials() 
{

  delete StainlessSteel;
  delete air;
  delete tungsten;
  delete CdWO4;
  delete water;
}


beamDoseMaterials *beamDoseMaterials::GetMaterials() 
{ return Materials; }


void beamDoseMaterials::CreateMaterials() 
{
  G4NistManager* man = G4NistManager::Instance();

  // Define various target materials
  // In order of increasing density
  tungsten = man->FindOrBuildMaterial("G4_W");

  //Define cadmium tungstate
  G4Element* Cd = man->FindOrBuildElement("Cd");
  G4Element* W = man->FindOrBuildElement("W");
  G4Element* O = man->FindOrBuildElement("O");

  CdWO4 = new G4Material("CdWO4", 7.9*g/cm3, 3);
  CdWO4->AddElement(Cd, 1);
  CdWO4->AddElement(W, 1);
  CdWO4->AddElement(O, 4);

  //Define stainless steel
  G4Element* C = man->FindOrBuildElement("C");
  G4Element* Si = man->FindOrBuildElement("Si");
  G4Element* Cr = man->FindOrBuildElement("Cr");
  G4Element* Mn = man->FindOrBuildElement("Mn");
  G4Element* Fe = man->FindOrBuildElement("Fe");
  G4Element* Ni = man->FindOrBuildElement("Ni");

  StainlessSteel = new G4Material("StainlessSteel", 8.06*g/cm3, 6);
  StainlessSteel->AddElement(C, 0.001);
  StainlessSteel->AddElement(Si, 0.007);
  StainlessSteel->AddElement(Cr, 0.18);
  StainlessSteel->AddElement(Mn, 0.01);
  StainlessSteel->AddElement(Fe, 0.712);
  StainlessSteel->AddElement(Ni, 0.09);

  air = man->FindOrBuildMaterial("G4_AIR");
  water = man->FindOrBuildMaterial("G4_WATER");

}
