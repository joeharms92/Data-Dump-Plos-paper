#include "beamDoseDetectorConstruction.hh"
#include "beamDoseHumanPhantomSD.hh"
#include "beamDoseMaterials.hh"

#include "G4HumanPhantomMaterial.hh"
#include "G4PhantomBuilder.hh"
#include "G4MaleBuilder.hh"
#include "G4PhantomHeadBuilder.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4Run.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4ios.hh"
#include <cmath>

#include <iostream>
#include <fstream>
#include <map>


//------------------------------------------------------------------------------

beamDoseDetectorConstruction* beamDoseDetectorConstruction::fgInstance=0;

//------------------------------------------------------------------------------

beamDoseDetectorConstruction* beamDoseDetectorConstruction::Instance()
{
  return fgInstance;
}

//------------------------------------------------------------------------------

beamDoseDetectorConstruction::beamDoseDetectorConstruction()
 : G4VUserDetectorConstruction()
{ 
  materials = new beamDoseMaterials();
  phantomMaterials = new G4HumanPhantomMaterial();
  fgInstance = this;

  // All Y's and Z's are swapped because I cannot rotate the human phantom
  containerSize.setX(1.2*m);
  containerSize.setY(2.4*m);
  containerSize.setZ(2.4*m);

  innerContainerSize.setX(containerSize.x() - 5*mm*2);
  innerContainerSize.setY(containerSize.y() - 5*mm*2);
  innerContainerSize.setZ(containerSize.z() - 5*mm*2);
  
  plateSize.setX(innerContainerSize.x());
  plateSize.setY(innerContainerSize.y());
  plateSize.setZ(20.*cm);
  
  bodyRad = 20.*cm;
  bodyHeight = 180.*cm;

  worldSize.setX( containerSize.x() );
  worldSize.setY( containerSize.y() );
  worldSize.setZ( containerSize.z() + 2.*m );

  containerPos.setX(0);
  containerPos.setY(0);
  containerPos.setZ(worldSize.z()/2. - containerSize.z()/2.);

}

//------------------------------------------------------------------------------

beamDoseDetectorConstruction::~beamDoseDetectorConstruction()
{ 
  fgInstance = 0;
  delete phantomMaterials;
}

//------------------------------------------------------------------------------

G4VPhysicalVolume* beamDoseDetectorConstruction::Construct()
{
  // Define volumes
  return ConstructGeom();
}


//------------------------------------------------------------------------------

G4VPhysicalVolume* beamDoseDetectorConstruction::ConstructGeom()
{
  
// Clean old geometry, if any
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  BuildWorld();
  BuildContainer();
  BuildPhantom();
  //
  // Always return the physical World
  //
  return worldPV;
}

//------------------------------------------------------------------------------

void beamDoseDetectorConstruction::BuildWorld()
{
  worldS = new G4Box("World",
                  worldSize.x()/2.,
                  worldSize.y()/2.,
                  worldSize.z()/2.);

  worldLV = new G4LogicalVolume(
                  worldS,
                  G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"),
                  "World");

  worldPV = new G4PVPlacement(
                  0,
                  G4ThreeVector(),
                  worldLV,
                  "World",
                  0,
                  false,
                  0);

  worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());
}

//------------------------------------------------------------------------------

void beamDoseDetectorConstruction::BuildContainer()
{


  containerS = new G4Box("ContainerS",
                          containerSize.x()/2.,
                          containerSize.y()/2.,
                          containerSize.z()/2.);

  containerLV = new G4LogicalVolume(containerS,
                            materials->GetStainless(),
                            "ContainerLV");

  containerPV = new G4PVPlacement(0,
                            containerPos,
                            containerLV,
                            "Container PV",
                            worldLV,
                            false,
                            0);

  innerContainerS = new G4Box("InnerContainerS",
                                  innerContainerSize.x()/2.,
                                  innerContainerSize.y()/2.,
                                  innerContainerSize.z()/2.);

  innerContainerLV = new G4LogicalVolume(innerContainerS,
                                     materials->GetAir(),
                                     "InnerContainerLV");

  innerContainerPV = new G4PVPlacement(0,
                                     G4ThreeVector(),
                                     innerContainerLV,
                                     "InnerContainerPV",
                                     containerLV,
                                     false,
                                     0);

  plateS = new G4Box("SteelPlateS",
                                    plateSize.x()/2.,
                                    plateSize.y()/2.,
                                    plateSize.z()/2.);

  plateLV = new G4LogicalVolume(plateS,
                                    materials->GetStainless(),
                                    "PlateLV");

  platePV = new G4PVPlacement(0,
                                    G4ThreeVector(),
                                    plateLV,
                                    "PlatePV",
                                    innerContainerLV,
                                    false,
                                    0);

  G4VisAttributes* plateVis = new G4VisAttributes();
  plateVis->SetColor(G4Color::Gray());
  plateVis->SetForceSolid( true );
  plateVis->SetVisibility( true );
  plateLV->SetVisAttributes( plateVis );

  G4VisAttributes* containerVis = new G4VisAttributes();
  containerVis->SetColor(G4Color::Blue());
  containerVis->SetForceSolid( false );
  containerVis->SetVisibility( true );
  containerLV->SetVisAttributes( containerVis );
  innerContainerLV->SetVisAttributes( containerVis );

}


void beamDoseDetectorConstruction::BuildPhantom()
{
  phantomMaterials->DefineMaterials();

  G4BasePhantomBuilder* builder = 0;

  G4Box* dummyVolume = new G4Box("dummyS",
              0.25*m,
              0.2*m,
              0.95*m);
  G4LogicalVolume* dummyLV = new G4LogicalVolume(dummyVolume,
            materials->GetAir(),
            "dummyLV");
  dummyLV->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4ThreeVector phantomPos;
  phantomPos.setX(0);
  phantomPos.setY(-innerContainerSize.y()/2. + 0.95*m);
  phantomPos.setZ(-innerContainerSize.z()/2. + 0.2*m);

  G4VPhysicalVolume* dummyPV = new G4PVPlacement(0,
            phantomPos,
            dummyLV,
            "dummyPV",
            innerContainerLV,
            false,
            0);

  // using MIRD model
  builder = new G4MaleBuilder;
  builder->SetModel("MIRD");
  builder->SetMotherVolume(dummyPV);

  builder->BuildHead("yellow", true, sensitivities["Head"]);
  builder->BuildSkull("yellow", false,sensitivities["Skull"]); 
  builder->BuildBrain("yellow", true,sensitivities["Brain"]); 
  builder->BuildTrunk("yellow", true, sensitivities["Trunk"]);
  builder->BuildLeftLeg("yellow", true,sensitivities["LeftLeg"]);
  builder->BuildRightLeg("yellow", true,sensitivities["RightLeg"]);
  builder->BuildLeftArmBone("grey", true,sensitivities["LeftArmBone"]);
  builder->BuildRightArmBone("grey", true, sensitivities["RightArmBone"]);  
  builder->BuildLeftLegBone("grey", true,sensitivities["LeftLegBone"]);
  builder->BuildRightLegBone("grey", true,sensitivities["RightLegBone"]);
  builder->BuildUpperSpine("yellow", true,sensitivities["UpperSpine"]); 
  builder->BuildLeftScapula("grey", true, sensitivities["LeftScapula"]); 
  builder->BuildRightScapula("grey", true, sensitivities["RightScapula"]);
  builder->BuildLeftClavicle("grey", true,sensitivities["LeftClavicle"]);
  builder->BuildRightClavicle("grey", true,sensitivities["RightClavicle"]);
  builder->BuildRibCage("grey", true,sensitivities["RibCage"]); 
  builder->BuildMiddleLowerSpine("yellow", true,sensitivities["MiddleLowerSpine"]);
  builder->BuildPelvis("grey", true,sensitivities["Pelvis"]); 

  G4VPhysicalVolume* result=builder->GetPhantom(); 
  G4RotationMatrix* rotMat = new G4RotationMatrix();
  rotMat->rotateX(90*deg);
  result->SetRotation(rotMat);
  result->SetTranslation(phantomPos);
  delete builder;
}

void beamDoseDetectorConstruction::ConstructSDandField(){

  beamDoseHumanPhantomSD* SD = new beamDoseHumanPhantomSD("SD", "HumanPhantomCollection");
  SetSensitiveDetector("logicalHead",SD);
  SetSensitiveDetector("logicalSkull",SD);
  SetSensitiveDetector("logicalBrain",SD);
  SetSensitiveDetector("logicalTrunk",SD);
  SetSensitiveDetector("logicalLeftLeg",SD); 
  SetSensitiveDetector("logicalRightLeg",SD);
  SetSensitiveDetector("logicalLeftArmBone",SD); 
  SetSensitiveDetector("logicalRightArmBone",SD);
  SetSensitiveDetector("logicalLeftLegBone",SD); 
  SetSensitiveDetector("logicalRightLegBone",SD);
  SetSensitiveDetector("logicalUpperSpine",SD);
  SetSensitiveDetector("logicalLeftScapula",SD);
  SetSensitiveDetector("logicalRightScapula",SD);
  SetSensitiveDetector("logicalLeftClavicle",SD);
  SetSensitiveDetector("logicalRightClavicle",SD);
  SetSensitiveDetector("logicalRibCage",SD);       
  SetSensitiveDetector("logicalMiddleLowerSpine",SD);
  SetSensitiveDetector("logicalPelvis",SD); 

  //G4SDManager::GetSDMpointer()->AddNewDetector(bodyDet);
}