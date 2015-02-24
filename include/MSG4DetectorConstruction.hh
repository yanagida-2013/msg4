#ifndef MSG4DetectorConstruction_h
#define MSG4DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class MSG4DetectorConstruction
  : public G4VUserDetectorConstruction {
  public:
  	MSG4DetectorConstruction();
  	~MSG4DetectorConstruction();
  	virtual G4VPhysicalVolume* Construct();
  	G4LogicalVolume* GetSampleVolume() const {return sampleVolume; }
  	G4double GetFlightPath() { return flight_path; };
  private:
  	G4LogicalVolume* sampleVolume;
  	G4double flight_path;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

