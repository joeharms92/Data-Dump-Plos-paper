#include "G4Isotope.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4OpticalSurface.hh"

#include "ansiCNRMaterials.hh"
#include "G4NistManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

ansiCNRMaterials *ansiCNRMaterials::Materials = 0;

ansiCNRMaterials::ansiCNRMaterials() 
{
  CreateMaterials();  
  Materials = this;
}

ansiCNRMaterials::~ansiCNRMaterials() 
{
  delete vacuum;
  delete air;
  delete carbon;
  delete aluminum;
  delete iron;
  delete copper;
  delete tungsten;
  delete lead;
}


ansiCNRMaterials *ansiCNRMaterials::GetMaterials() 
{ return Materials; }


void ansiCNRMaterials::CreateMaterials() 
{
  G4NistManager* man = G4NistManager::Instance();
  G4Element* H = man->FindOrBuildElement("H");  
  G4Element* C = man->FindOrBuildElement("C");
  G4Element* O = man->FindOrBuildElement("O");  
  G4Element* Mn = man->FindOrBuildElement("Mn");
  G4Element* Fe = man->FindOrBuildElement("Fe");
  G4Element* S = man->FindOrBuildElement("S");
  G4Element* P = man->FindOrBuildElement("P");
  G4Element* Si = man->FindOrBuildElement("Si");
  G4Element* Ni = man->FindOrBuildElement("Ni");
  G4Element* Cr = man->FindOrBuildElement("Cr");

  carbon = man->FindOrBuildMaterial("G4_C");
  aluminum = man->FindOrBuildMaterial("G4_Al");
  iron = man->FindOrBuildMaterial("G4_Fe");
  copper = man->FindOrBuildMaterial("G4_Cu");
  tungsten = man->FindOrBuildMaterial("G4_W");
  lead = man->FindOrBuildMaterial("G4_Pb");

  //    Materials
  water = new G4Material("Water",1*g/cm3,2);
  water->AddElement(H,2);
  water->AddElement(O,1);

  c1008 = new G4Material("CarbonSteel", 7.872*g/cm3, 5);
  c1008->AddElement(Fe, 0.9951);
  c1008->AddElement(Mn, 0.003);
  c1008->AddElement(C, 0.001);
  c1008->AddElement(S, 0.0005);
  c1008->AddElement(P, 0.0004);

  StainlessSteel = new G4Material("StainlessSteel", 8.06*g/cm3, 6);
  StainlessSteel->AddElement(C, 0.001);
  StainlessSteel->AddElement(Si, 0.007);
  StainlessSteel->AddElement(Cr, 0.18);
  StainlessSteel->AddElement(Mn, 0.01);
  StainlessSteel->AddElement(Fe, 0.712);
  StainlessSteel->AddElement(Ni, 0.09);

  vacuum = new G4Material( "vacuum", 1., 1.008*g/mole, 1.e-25*g/cm3,kStateGas, 
               273*kelvin, 3.8e-18*pascal );

  air = man->FindOrBuildMaterial("G4_AIR");

}
