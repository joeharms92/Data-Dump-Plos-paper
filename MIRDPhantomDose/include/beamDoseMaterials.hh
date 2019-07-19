#ifndef beamDoseMaterials_hh
#define beamDoseMaterials_hh 1

class G4Material;
class G4VisAttributes;
class G4OpticalSurface;

class beamDoseMaterials {

public:
  beamDoseMaterials();
  ~beamDoseMaterials();
  
  static beamDoseMaterials * GetMaterials();

  
  inline G4Material * GetAir() {return air; };
  inline G4Material * GetTungsten() { return tungsten; };
  inline G4Material * GetCdWO4() {return CdWO4; };
  inline G4Material * GetStainless() { return StainlessSteel; };
  inline G4Material * GetWater() { return water; };

private:
  void CreateMaterials();
  void SetMaterialVis();

private:
  static beamDoseMaterials *Materials;
  
  G4Material* air;
  G4Material* tungsten;
  G4Material* StainlessSteel;
  G4Material* CdWO4;
  G4Material* water;

};

#endif
