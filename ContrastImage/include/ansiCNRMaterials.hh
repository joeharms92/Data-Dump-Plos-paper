#ifndef ansiCNRMaterials_hh
#define ansiCNRMaterials_hh 1

#include <vector>

class G4Material;
class G4VisAttributes;
class G4OpticalSurface;

class ansiCNRMaterials {

public:
  ansiCNRMaterials();
  ~ansiCNRMaterials();
  
  static ansiCNRMaterials * GetMaterials();
  
  inline G4Material * GetVacuum() { return vacuum; };
  inline G4Material * GetAir() {return air;};
  inline G4Material * GetWater() {return water; };
  inline G4Material * GetC1008() {return c1008; };
  inline G4Material * GetStainless() {return StainlessSteel; };
  inline G4Material * GetCarbon() {return carbon; };
  inline G4Material * GetAluminum() {return aluminum; };
  inline G4Material * GetIron() {return iron; };
  inline G4Material * GetCopper() {return copper; };
  inline G4Material * GetTungsten() {return tungsten; };
  inline G4Material * GetLead() {return lead; };

private:
  void CreateMaterials();

private:
  static ansiCNRMaterials *Materials;
  
  G4Material * vacuum;
  G4Material * air;
  G4Material * water;
  G4Material * c1008;
  G4Material * StainlessSteel;
  G4Material * carbon;
  G4Material * aluminum;
  G4Material * iron;
  G4Material * copper; 
  G4Material * tungsten;
  G4Material * lead;
  
};

#endif
