#include "ansiCNRDetectorConstruction.hh"
#include "ansiCNRMaterials.hh"
#include "ansiCNRPlaneSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "Randomize.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PVParameterised.hh"
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


//------------------------------------------------------------------------------

ansiCNRDetectorConstruction* ansiCNRDetectorConstruction::fgInstance=0;

//------------------------------------------------------------------------------

ansiCNRDetectorConstruction* ansiCNRDetectorConstruction::Instance()
{
  return fgInstance;
}

//------------------------------------------------------------------------------

ansiCNRDetectorConstruction::ansiCNRDetectorConstruction(G4int sliceNo, G4int detOffsetID)
 : G4VUserDetectorConstruction(),
    fSliceNum(sliceNo)
{ 
  materials = new ansiCNRMaterials();
  fgInstance = this;

  // The size of each detector elements
  detElSize.setX(6.*mm);
  detElSize.setY(10.*mm);
  detElSize.setZ(1.*mm);

  detDummySize.setX(detElSize.x());
  detDummySize.setY(detElSize.y() * (G4double)numDets);
  detDummySize.setZ(detElSize.z());

  // active area for lyso detectors, quartz is cylinder with radius = 3
  detSize.setX(6.*mm);
  detSize.setY(6.*mm);
  detSize.setZ(detElSize.z());

  worldSize.setX((G4double)(numSlices+1) * detElSize.x() / 2.);
  worldSize.setY((G4double)numDets * detElSize.y() + detElSize.y()/2.);
  worldSize.setZ(2.*m);

    // container params
  containerSize.setX(60.*cm);
  containerSize.setY(60.*cm);
  containerSize.setZ(10.*cm);

  containerInteriorSize.setX(containerSize.x());
  containerInteriorSize.setY(containerSize.y());
  containerInteriorSize.setZ(containerSize.z()-10.*mm);

  waterRad = 20.*cm;
  waterZ = containerInteriorSize.z();

  rodRad = 2.5*cm;
  rodZ = waterZ;

  containerPos.setX(0);
  containerPos.setY(0);
  containerPos.setZ(0);

  detPos.setX(-worldSize.x()/2. + ((G4double)fSliceNum * detElSize.x())/2. + detElSize.x()/2. ); // if slice width changes from this, pay attention
  G4double detYpos = -detElSize.y()/4.;
  if ( (detOffsetID % 2) == 0) detYpos = - detYpos;
  detPos.setY(detYpos);
  detPos.setZ(worldSize.z()/2.-detElSize.z()/2.);

}

//------------------------------------------------------------------------------

ansiCNRDetectorConstruction::~ansiCNRDetectorConstruction()
{ 
  delete materials;
  fgInstance = 0;
}

//------------------------------------------------------------------------------

G4VPhysicalVolume* ansiCNRDetectorConstruction::Construct()
{  
  // Clean old geometry, if any
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  BuildWorld();
  Buildcontainer();
  BuildTestObject();
  BuildPlane();
  AssignVisualization();


  // Always return the physical World
  return worldPV;
}

//------------------------------------------------------------------------------

void ansiCNRDetectorConstruction::BuildWorld()
{
  worldS = new G4Box("World",
                  worldSize.x()/2.,
                  worldSize.y()/2.,
                  worldSize.z()/2.);

  worldLV = new G4LogicalVolume(
                  worldS,
                  materials->GetAir(),
                  "World");

  worldPV = new G4PVPlacement(
                  0,
                  G4ThreeVector(),
                  worldLV,
                  "World",
                  0,
                  false,
                  0);
}

//------------------------------------------------------------------------------

void ansiCNRDetectorConstruction::Buildcontainer()
{

  G4RotationMatrix* rotate90yz = new G4RotationMatrix();
  rotate90yz->rotateX(90*deg);
  rotate90yz->rotateY(0*deg);
  rotate90yz->rotateZ(0*deg);

  containerS = new G4Box("containerS",
                        containerSize.x()/2.,
                        containerSize.y()/2.,
                        containerSize.z()/2.);

  containerLV = new G4LogicalVolume(containerS, 
                materials->GetStainless(),
                "container Logical",
                0,0,0);

  containerPV = new G4PVPlacement(0,
                containerPos,
                containerLV,
                "container Phyiscal",
                worldLV,
                false,
                1);

  containerInteriorS = new G4Box("HollowVolume",
                                    containerInteriorSize.x()/2.,
                                    containerInteriorSize.y()/2.,
                                    containerInteriorSize.z()/2.);

  containerInteriorLV = new G4LogicalVolume(containerInteriorS,
                                      materials->GetAir(),
                                      "Hollow LV",
                                      0,0,0);

  containerInteriorPV = new G4PVPlacement(0,
                                      G4ThreeVector(0,0,0),
                                      containerInteriorLV,
                                      "Hollow Physical",
                                      containerLV,
                                      false,
                                      1);
}

//------------------------------------------------------------------------------

void ansiCNRDetectorConstruction::BuildTestObject()
{
  waterS = new G4Tubs("waterS",
                                    0,
                                    waterRad,
                                    waterZ/2.,
                                    0,
                                    360*deg);

  waterLV = new G4LogicalVolume(
                                      waterS,
                                      materials->GetWater(),
                                      "waterLV");

  G4RotationMatrix * rotTarget = new G4RotationMatrix();
  rotTarget->rotateZ(90 * deg);
  waterPV = new G4PVPlacement(rotTarget,
                                      G4ThreeVector(),
                                      waterLV,
                                      "waterPV",
                                      containerInteriorLV,
                                      false,
                                      0);

  rodS = new G4Tubs("rodS",
                    0,
                    rodRad,
                    rodZ/2.,
                    0,
                    360*deg);

  carbonLV = new G4LogicalVolume(rodS,
                      materials->GetCarbon(),
                      "carbonLV");

  alLV = new G4LogicalVolume(rodS,
              materials->GetAluminum(),
              "alLV");

  ironLV = new G4LogicalVolume(rodS,
                  materials->GetIron(),
                  "feLV");

  copperLV = new G4LogicalVolume(rodS,
                        materials->GetCopper(),
                        "cuLV");

  tungstenLV = new G4LogicalVolume(rodS,
                          materials->GetTungsten(),
                          "wLV");

  leadLV = new G4LogicalVolume(rodS,
                    materials->GetLead(),
                    "pbLV");

  G4double rodVal = 10.*cm + rodRad;

  G4ThreeVector carbonPos;
  carbonPos.setX(-rodVal*std::sin(pi/3));
  carbonPos.setY(-rodVal*std::cos(pi/3));
  //carbonPos.setZ(0);

  G4ThreeVector alPos;
  alPos.setX(carbonPos.x());
  alPos.setY(-carbonPos.y());
  //alPos.setZ(0);

  G4ThreeVector ironPos;
  ironPos.setY(rodVal);

  G4ThreeVector copperPos;
  copperPos.setX(-carbonPos.x());
  copperPos.setY(alPos.y());

  G4ThreeVector tungstenPos;
  tungstenPos.setX(copperPos.x());
  tungstenPos.setY(carbonPos.y());

  G4ThreeVector leadPos;
  leadPos.setY(-ironPos.y());

  carbonPV = new G4PVPlacement(rotTarget,
                        carbonPos,
                        carbonLV,
                        "carbonPV",
                        waterLV,
                        false,
                        0);

  alPV = new G4PVPlacement(rotTarget,
                        alPos,
                        alLV,
                        "alPV",
                        waterLV,
                        false,
                        0);

  ironPV = new G4PVPlacement(rotTarget,
                        ironPos,
                        ironLV,
                        "ironPV",
                        waterLV,
                        false,
                        0);

  copperPV = new G4PVPlacement(rotTarget,
                        copperPos,
                        copperLV,
                        "copperPV",
                        waterLV,
                        false,
                        0);

  tungstenPV = new G4PVPlacement(rotTarget,
                        tungstenPos,
                        tungstenLV,
                        "tungstenPV",
                        waterLV,
                        false,
                        0);

  leadPV = new G4PVPlacement(rotTarget,
                        leadPos,
                        leadLV,
                        "leadPV",
                        waterLV,
                        false,
                        0);

 
}

//------------------------------------------------------------------------------

void ansiCNRDetectorConstruction::BuildPlane()
{


 detPlaneS = new G4Box("TotalDetArray",
                      detDummySize.x()/2.,
                      detDummySize.y()/2.,
                      detDummySize.z()/2.);

 detPlaneLV = new G4LogicalVolume(
                        detPlaneS,
                        materials->GetAir(),
                        "TotalDetArrayLV");

 detPlanePV = new G4PVPlacement(
                        0,
                        detPos,
                        detPlaneLV,
                        "plane",
                        worldLV,
                        false,
                        0);

 elementS = new G4Box("Element",
                      detElSize.x()/2.,
                      detElSize.y()/2.,
                      detElSize.z()/2.);

 elementLV = new G4LogicalVolume(
                      elementS,
                      materials->GetAir(),
                      "Element");


  elementPV = new G4PVReplica("Element",
                      elementLV,
                      detPlanePV,
                      kYAxis,
                      numDets,
                      detElSize.y(),
                      0);

  quartzS = new G4Tubs("Crystal",
                      0,
                      detSize.x()/2.,
                      detSize.z()/2.,
                      0*deg,
                      360*deg);

  crystalLV = new G4LogicalVolume(
                      quartzS,
                      materials->GetAir(),
                      "CrystalLV");


  crystalPV = new G4PVPlacement(
                      0,
                      G4ThreeVector(0,0,0),
                      crystalLV,
                      "Crystal",
                      elementLV,
                      false,
                      0);


}

//------------------------------------------------------------------------------

void ansiCNRDetectorConstruction::AssignVisualization()
{

  //worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());
  //testObjDummyLV->SetVisAttributes(G4VisAttributes::GetInvisible());
  //elementLV->SetVisAttributes(G4VisAttributes::GetInvisible());
  detPlaneLV->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4VisAttributes* waterVis = new G4VisAttributes();
  waterVis->SetColor(G4Color::Cyan());
  waterVis->SetForceSolid( true) ;
  waterVis->SetVisibility(true);
  waterLV->SetVisAttributes(waterVis);

  G4VisAttributes* carbonVis = new G4VisAttributes();
  carbonVis->SetColor(G4Color::Gray() );
  carbonVis->SetForceSolid(true);
  carbonVis->SetVisibility(true);
  carbonLV->SetVisAttributes(carbonVis);

  G4VisAttributes* alVis = new G4VisAttributes();
  alVis->SetColor(G4Color::White() );
  alVis->SetForceSolid(true);
  alVis->SetVisibility(true);
  alLV->SetVisAttributes(alVis);

  G4VisAttributes* ironVis = new G4VisAttributes();
  ironVis->SetColor(G4Color::Yellow() );
  ironVis->SetForceSolid(true);
  ironVis->SetVisibility(true);
  ironLV->SetVisAttributes(ironVis);

  G4VisAttributes* copperVis = new G4VisAttributes();
  copperVis->SetColor(G4Color::Red());
  copperVis->SetForceSolid(true);
  copperVis->SetVisibility(true);
  copperLV->SetVisAttributes(copperVis);

  G4VisAttributes* tungstenVis = new G4VisAttributes();
  tungstenVis->SetColor(G4Color::Green());
  tungstenVis->SetForceSolid(true);
  tungstenVis->SetVisibility(true);
  tungstenLV->SetVisAttributes(tungstenVis);

  G4VisAttributes* leadVis = new G4VisAttributes();
  leadVis->SetColor(G4Color::Blue() );
  leadVis->SetForceSolid(true);
  leadVis->SetVisibility(true);
  leadLV->SetVisAttributes(leadVis);

  G4VisAttributes* detVis = new G4VisAttributes();
  detVis->SetColor(G4Color::Blue());
  detVis->SetForceSolid(true);
  detVis->SetVisibility(true);
  crystalLV->SetVisAttributes(detVis);

}

//------------------------------------------------------------------------------

void ansiCNRDetectorConstruction::ConstructSDandField(){
  ansiCNRPlaneSD* detSD = new ansiCNRPlaneSD("detSD","planeHitsCollection", numDets);
  SetSensitiveDetector("CrystalLV",detSD);
}