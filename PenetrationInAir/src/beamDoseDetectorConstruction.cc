#include "beamDoseDetectorConstruction.hh"
#include "beamDoseSD.hh"
#include "beamDoseMaterials.hh"

#include "G4SDManager.hh"
#include "G4PSCellFlux.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

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

//------------------------------------------------------------------------------

beamDoseDetectorConstruction* beamDoseDetectorConstruction::fgInstance=0;

//------------------------------------------------------------------------------

beamDoseDetectorConstruction* beamDoseDetectorConstruction::Instance()
{
  return fgInstance;
}

//------------------------------------------------------------------------------

beamDoseDetectorConstruction::beamDoseDetectorConstruction(G4double plateThickness)
 :  G4VUserDetectorConstruction(),   
    fSteelZ(plateThickness)
{ 
  materials = new beamDoseMaterials();
  fgInstance = this;

  // All Y's and Z's are swapped because I cannot rotate the human phantom
  containerSize.setX(1.2*m);
  containerSize.setY(2.4*m);
  containerSize.setZ(2.4*m);

  innerContainerSize.setX(containerSize.x());
  innerContainerSize.setY(containerSize.y());
  innerContainerSize.setZ(containerSize.z() - 5*mm*2);
  
  plateSize.setX(innerContainerSize.x());
  plateSize.setY(innerContainerSize.y());
  plateSize.setZ(fSteelZ*cm);

  worldSize.setX( containerSize.x() );
  worldSize.setY( containerSize.y() );
  worldSize.setZ( containerSize.z() + 80.*cm + 10.*cm + 5.*mm );

  detSize.setX(6.*mm);
  detSize.setY(6.*mm);
  detSize.setZ(50.*mm);

  reflThickness = 0.5*mm;
  PMTLength = 5.*mm;

  detDummyElSize.setX(detSize.x()+reflThickness*2);
  detDummyElSize.setY(detSize.y()+reflThickness*2);
  detDummyElSize.setZ(detSize.z()+PMTLength+reflThickness);

  collimatorSize.setX(1.*cm);
  collimatorSize.setY(detDummyElSize.y()*4.);
  collimatorSize.setZ(40.*cm);

  detVolumeSize.setX(detDummyElSize.x() + 2.*collimatorSize.x());
  detVolumeSize.setY(collimatorSize.y());
  detVolumeSize.setZ(collimatorSize.z());

  containerPos.setX(0);
  containerPos.setY(0);
  containerPos.setZ(-worldSize.z()/2. + 5.*mm + containerSize.z()/2.);

  detVolumePos.setX(0);
  detVolumePos.setY(0);
  detVolumePos.setZ(worldSize.z()/2 - detVolumeSize.z()/2.);

}

beamDoseDetectorConstruction::~beamDoseDetectorConstruction()
{ 
  fgInstance = 0;
}

G4VPhysicalVolume* beamDoseDetectorConstruction::Construct()
{
  // Define volumes
  return ConstructGeom();
}

G4VPhysicalVolume* beamDoseDetectorConstruction::ConstructGeom()
{
  
// Clean old geometry, if any
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  BuildWorld();
  BuildContainer();
  BuildDetector();

  // Always return the physical World
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

//------------------------------------------------------------------------------

void beamDoseDetectorConstruction::BuildDetector()
{
  detBlockS = new G4Box("WholeDetVolumeS",
                              detVolumeSize.x()/2.,
                              detVolumeSize.y()/2.,
                              detVolumeSize.z()/2.);

  detBlockLV = new G4LogicalVolume(detBlockS,
                              materials->GetAir(),
                              "WholeDetVolumeLV");

  detBlockPV = new G4PVPlacement(0,
                              detVolumePos,
                              detBlockLV,
                              "WholeDetVolumePV",
                              worldLV,
                              false,
                              0);

  collimatorS = new G4Box("CollimatorS",
                              collimatorSize.x()/2.,
                              collimatorSize.y()/2.,
                              collimatorSize.z()/2.);

  collimatorLV = new G4LogicalVolume(collimatorS,
                              materials->GetTungsten(),
                              "CollimatorLV");

  G4LogicalVolume* collimator2LV = new G4LogicalVolume(collimatorS,
                              materials->GetTungsten(),
                              "CollimatorLV");

  collimator1PV = new G4PVPlacement(0,
                              G4ThreeVector(-detVolumeSize.x()/2. + collimatorSize.x()/2., 0, 0),
                              collimatorLV,
                              "Collimator1PV",
                              detBlockLV,
                              false,
                              0);

  collimator2PV = new G4PVPlacement(0,
                              G4ThreeVector(detVolumeSize.x()/2. - collimatorSize.x()/2., 0, 0),
                              collimator2LV,
                              "Collimator2PV",
                              detBlockLV,
                              false,
                              0);


    reflS = new G4Box("Reflector",
                              detDummyElSize.x()/2.,
                              detDummyElSize.y()/2.,
                              detDummyElSize.z()/2.);

    reflLV = new G4LogicalVolume(
                              (G4Box*)reflS,
                              materials->GetAir(),
                              "ReflectorLV");

    detS = new G4Box("detS",
                              detSize.x()/2.,
                              detSize.y()/2.,
                              detSize.z()/2.);

    detLV = new G4LogicalVolume((G4Box*)detS,
                              materials->GetAir(),
                              "detLV");

    pmtS = new G4Box("PMT",
                  detSize.x()/2.,
                  detSize.y()/2.,
                  detSize.z()/2.);

    pmtLV = new G4LogicalVolume(
                  pmtS,
                  materials->GetAir(),
                  "PMTLV");

  reflPV = new G4PVPlacement(
                    0,
                    G4ThreeVector(0,0,detVolumeSize.z()/2. - 10.*cm + detDummyElSize.z()/2.),
                    reflLV,
                    "Reflector",
                    detBlockLV,
                    false,
                    0);

  detPV = new G4PVPlacement(
                      0,
                      G4ThreeVector(0,0,detDummyElSize.z()/2. - PMTLength - detSize.z()/2.),
                      detLV,
                      "Crystal",
                      reflLV,
                      false,
                      0);

  pmtPV = new G4PVPlacement(
                  0,
                  G4ThreeVector(0, 0, detDummyElSize.z()/2. - PMTLength/2.),
                  pmtLV,
                  "PMT",
                  reflLV,
                  false,
                  0);

  detBlockLV->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4VisAttributes* collimatorVis = new G4VisAttributes();
  collimatorVis->SetColor(G4Color::Gray());
  collimatorVis->SetForceSolid( false );
  collimatorVis->SetVisibility( true );
  collimatorLV->SetVisAttributes( collimatorVis );

  G4VisAttributes* collimator2Vis = new G4VisAttributes();
  collimator2Vis->SetColor(G4Color::Gray());
  collimator2Vis->SetForceSolid( true );
  collimator2Vis->SetVisibility( true );
  collimator2LV->SetVisAttributes( collimator2Vis );

  G4VisAttributes* detVis = new G4VisAttributes();
  detVis->SetColor(G4Color::Blue());
  detVis->SetForceSolid( true );
  detVis->SetVisibility( true );
  detLV->SetVisAttributes( detVis );

  G4VisAttributes* pmtVis = new G4VisAttributes();
  pmtVis->SetColor(G4Color::Red());
  pmtVis->SetForceSolid( true );
  pmtVis->SetVisibility( true );
  pmtLV->SetVisAttributes( pmtVis );
}

//------------------------------------------------------------------------------

void beamDoseDetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(0);
  G4SDManager* pSDman = G4SDManager::GetSDMpointer();

  beamDoseSD* quartzDet = new beamDoseSD("det", "DetCollection");
  SetSensitiveDetector("detLV", quartzDet);
  pSDman->AddNewDetector(quartzDet);
}