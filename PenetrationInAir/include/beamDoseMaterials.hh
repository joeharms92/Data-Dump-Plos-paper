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
  inline G4Material * GetQuartz() { return quartz; };
  inline G4Material * GetLYSO() { return lyso; };
  inline G4Material * GetTyvek() { return tyvek; };

  inline G4OpticalSurface * GetTyvekSurface() {return tyvekSurface;}
  inline G4OpticalSurface * GetQuartzSurface() {return quartzSurface;}
  inline G4OpticalSurface * GetPMTSurface() {return quartzSurface;}
  
private:
  void CreateMaterials();
  void SetOpticalProperties();

private:
  static beamDoseMaterials *Materials;
  
  G4Material* air;
  G4Material* tungsten;
  G4Material* StainlessSteel;
  G4Material* CdWO4;
  G4Material* quartz;
  G4Material* lyso;
  G4Material* tyvek;

  G4OpticalSurface * tyvekSurface;
  G4OpticalSurface * quartzSurface;
  G4OpticalSurface * pmtSurface;

  G4int nEntries;
  G4double PMTQEarray[32];
  G4double photonEnergy[32];

};

#endif
