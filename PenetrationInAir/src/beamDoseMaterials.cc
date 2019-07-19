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
  SetOpticalProperties();
  Materials = this;
}

beamDoseMaterials::~beamDoseMaterials() 
{
  delete StainlessSteel;
  delete air;
  delete tungsten;
  delete CdWO4;
  delete quartz;
  delete lyso;
  delete tyvek;
}


beamDoseMaterials *beamDoseMaterials::GetMaterials() 
{ return Materials; }


void beamDoseMaterials::CreateMaterials() 
{
  G4NistManager* man = G4NistManager::Instance();

  // Define various target materials
  // In order of increasing density
  tungsten = man->FindOrBuildMaterial("G4_W");

  // Define cadmium tungstate
  G4Element* Cd = man->FindOrBuildElement("Cd");
  G4Element* W = man->FindOrBuildElement("W");
  G4Element* O = man->FindOrBuildElement("O");
  CdWO4 = new G4Material("CdWO4", 7.9*g/cm3, 3);
  CdWO4->AddElement(Cd, 1);
  CdWO4->AddElement(W, 1);
  CdWO4->AddElement(O, 4);

  // Define stainless steel
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

  // quartz
  quartz = new G4Material( "quartz", 2.2*g/cm3, 2 );
  quartz->AddElement( Si, 1 );
  quartz->AddElement( O, 2 );

  G4Element* Y = man->FindOrBuildElement("Y");
  G4Element* Lu = man->FindOrBuildElement("Lu");
  // lyso
  lyso = new G4Material( "lyso", 7.1*g/cm3, 4 );
  lyso->AddElement(Lu, 9);
  lyso->AddElement(Y, 1);
  lyso->AddElement(Si, 5);
  lyso->AddElement(O, 25);

  G4Element* H = man->FindOrBuildElement("H");  
  // tyvek
  tyvek = new G4Material( "tyvek",0.96*g/cm3,2);
  tyvek->AddElement( H, 2);
  tyvek->AddElement( C, 1);

  air = man->FindOrBuildMaterial("G4_AIR");
}

void beamDoseMaterials::SetOpticalProperties() 
{

  G4double energy[2] = {1.034*eV,8.136*eV}; 
  G4double photonEnergy32[] = 
  {1.034*eV, 2.068*eV, 2.106*eV, 2.139*eV, 2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV, 
    2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV, 2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV, 
    2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV, 3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV, 
    3.353*eV, 3.446*eV, 3.545*eV, 3.629*eV, 3.760*eV, 3.877*eV, 4.002*eV, 8.136*eV};
  const G4int nEntries32 = sizeof(photonEnergy32)/sizeof(G4double);  
  G4double refl_energy[9] ={1.034*eV,1.550*eV,1.771*eV,2.066*eV,2.480*eV,3.100*eV,4.133*eV,6.199*eV,8.136*eV}; // refl energy Gore


  // Quartz Material Properties
  G4double refractiveIndexQuartz[32] = {1.445,1.47,1.47,1.47,1.47,1.471,1.471,1.471,
                          1.472,1.472,1.473,1.473,1.473,1.474,1.474,1.474,
                          1.474,1.475,1.475,1.475,1.475,1.475,1.477,1.477,
                          1.479,1.479,1.485,1.49,1.49,1.495,1.495,1.5};

  G4double absorptionQuartz[32] = {33.333*m,16.667*m,16.129*m,15.625*m,15.1515*m,14.70588*m,14.2857*m,
                     13.88889*m,13.5135*m,13.15789*m,12.8025*m,12.5*m,12.195*m,11.90476*m,
                     11.6279*m,11.3636*m,11.1111*m,11.1111*m,10.52632*m,10.52632*m,10.0*m,
                     10.0*m,9.5238*m,9.5238*m,9.0909*m,9.0909*m,9.0909*m,8.3333*m,
                     7.6923*m,7.1429*m,6.6667*m,0.03125*m};

  G4MaterialPropertiesTable *quartzMat = new G4MaterialPropertiesTable();
  quartzMat->AddProperty( "RINDEX", photonEnergy32, refractiveIndexQuartz, nEntries32 );
  quartzMat->AddProperty("ABSLENGTH", photonEnergy32, absorptionQuartz, nEntries32 );
  quartz->SetMaterialPropertiesTable( quartzMat );

  // Tyvek Material Properties  // This is used in the model as reflector
  G4double absorptionTyvek[2] = {0.0001*mm, 0.0001*mm};
  G4MaterialPropertiesTable *tyvekMat = new G4MaterialPropertiesTable();
  tyvekMat->AddProperty( "ABSORPTION", energy, absorptionTyvek, 2);
  tyvek->SetMaterialPropertiesTable( tyvekMat );

  // Quartz-Tyvek Surface material properties
  G4double refl[9] = {0.98,0.98,0.988,0.99,0.995,0.995,0.995,0.7,0.0}; //Gore
  G4double specularlobe[2] = {0.3, 0.3};
  G4double specularspike[2] = {0.2, 0.2};

  G4MaterialPropertiesTable *tyvekSurfaceMat = new G4MaterialPropertiesTable();
  tyvekSurfaceMat->AddProperty("REFLECTIVITY",refl_energy,refl,9);
  tyvekSurfaceMat->AddProperty("SPECULARLOBECONSTANT",energy, specularlobe, 2);
  tyvekSurfaceMat->AddProperty("SPECULARSPIKECONSTANT", energy, specularspike, 2);
  tyvekSurfaceMat->AddProperty("BACKSCATTERCONSTANT", energy, specularspike, 2);
    
  tyvekSurface = new G4OpticalSurface("TyvekSurface");
  tyvekSurface->SetFinish(ground);
  tyvekSurface->SetModel(glisur);
  tyvekSurface->SetType(dielectric_metal);
  tyvekSurface->SetPolish(0.01);    //guess
  tyvekSurface->SetMaterialPropertiesTable(tyvekSurfaceMat);

  G4double refl_quartz[2] = {0.96,0.96};
  G4double effi_quartz[2] = {0.96,0.96};
    
  quartzSurface = new G4OpticalSurface("QuartzSurface");                                                              
  quartzSurface->SetType(dielectric_dielectric);
  quartzSurface->SetFinish(polished);
  quartzSurface->SetModel(glisur);

  G4MaterialPropertiesTable *quartzSurfaceMat = new G4MaterialPropertiesTable();
  quartzSurfaceMat->AddProperty("REFLECTIVITY", energy,refl_quartz,2);
  quartzSurfaceMat->AddProperty("EFFICIENCY",energy,effi_quartz,2);
  quartzSurface->SetMaterialPropertiesTable(quartzSurfaceMat);  
}
