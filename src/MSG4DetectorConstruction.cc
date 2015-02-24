#include "MSG4DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4DetectorConstruction::MSG4DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4DetectorConstruction::~MSG4DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* MSG4DetectorConstruction::Construct()
{

  flight_path = 120*mm;
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  //
  // World
  //
  G4double world_sizeXY = 100*mm;
  G4double world_sizeZ  = 300*mm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld
    = new G4Box("World",
		0.5*world_sizeXY,
		0.5*world_sizeXY,
		0.5*world_sizeZ);
  G4LogicalVolume* logicWorld
    = new G4LogicalVolume(solidWorld,
			  world_mat,
			  "World");
  G4VPhysicalVolume* physWorld
    = new G4PVPlacement(0,                     //no rotation
			G4ThreeVector(),       //at (0,0,0)
			logicWorld,            //its logical volume
			"World",               //its name
			0,                     //its mother  volume
			false,                 //no boolean operation
			0);                    //copy number


  G4double sample_center_pos = flight_path-world_sizeZ/2;
// #define AUSAMPLE
#ifdef AUSAMPLE
  //
  // Sample (Au-197, Metal)
  //
  // G4Material* au_mat = nist->FindOrBuildMaterial("G4_Au");
  G4String name, symbol;
  G4int natoms, ncomponents, z;
  G4double a = 196.9665687*g/mole;
  G4Element* elnatAu = new G4Element(name="natAu", symbol="Au", z=79, a);
  G4double density = 17.00*g/cm3;
  G4Material* au_mat = new G4Material(name="NatAu", density, ncomponents=1);
  au_mat->AddElement(elnatAu, natoms=1);
  G4double au_thisckness = 0.8*mm;
  G4double au_radius = 27.5*mm;
  G4Tubs* solidAuSample
  = new G4Tubs("AuSample",
    0.0*mm,
    au_radius,
    au_thisckness/2,
    0*degree, 360*degree
    );
  G4LogicalVolume* logicAuSample = new G4LogicalVolume(
    solidAuSample,
    au_mat,
    "AuSample");
  G4ThreeVector pos = G4ThreeVector(0*cm, 0*cm, sample_center_pos);
  new G4PVPlacement(0,
        pos,
        logicAuSample,
        "AuSample",
        logicWorld,
        false,
        0);
#else

  //
  // Sample (Ba-138, BaCO3)
  //

  //
  // setting the composition
  //
  G4String name, symbol;
  G4int iz, n, ncomponents, natoms;
  G4double a, z, density;
  // Ba !neutron number
  G4Isotope* Ba135 = new G4Isotope(name="Ba135", iz=56, n=135, a=134.91*g/mole);
  G4Isotope* Ba136 = new G4Isotope(name="Ba136", iz=56, n=136, a=135.90*g/mole);
  G4Isotope* Ba137 = new G4Isotope(name="Ba137", iz=56, n=137, a=136.91*g/mole);
  G4Isotope* Ba138 = new G4Isotope(name="Ba138", iz=56, n=138, a=137.91*g/mole);

  G4Element* elBa = new G4Element(name="enriched Barium", symbol="Ba", ncomponents=4);
  elBa->AddIsotope(Ba135, 0.02*perCent);
  elBa->AddIsotope(Ba136, 0.02*perCent);
  elBa->AddIsotope(Ba137, 0.16*perCent);
  elBa->AddIsotope(Ba138, 99.8*perCent);
  // C
  a = 12.01*g/mole;
  G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6, a);
  // O
  a = 16.00*g/mole;
  G4Element* elO = new G4Element(name="Oxygen", symbol="A", z=8, a);
  // Material
  // density = 4.29*g/cm3; // 理論密度でやっていた。失敗した。
  density = 1.362*g/cm3;
  G4Material* ba_sample_mat = new G4Material(name="BaSample", density, ncomponents=3);
  // G4Material* gd_mat = nist->FindOrBuildMaterial("G4_Gd");  // used for check.
  ba_sample_mat->AddElement(elBa, natoms=1);
  ba_sample_mat->AddElement(elC,  natoms=1);
  ba_sample_mat->AddElement(elO,  natoms=3);


  G4ThreeVector pos = G4ThreeVector(0*cm, 0*cm, sample_center_pos);
  // Solid
  G4double pRMin = 0.0*mm, pRMax=28.1*mm;
  G4double pDz = 12.7*mm;
  G4double pSPhi = 0*degree, pDPhi = 360*degree;
  G4Tubs* solidBaSample
    = new G4Tubs("BaSample",
		 pRMin,
		 pRMax,
		 pDz/2,
		 pSPhi,
		 pDPhi);
  // Logical Volume
  G4LogicalVolume* logicBaSample
    = new G4LogicalVolume(solidBaSample,
			  // gd_mat,
        ba_sample_mat,
			  "BaSample");
  // Placement
  new G4PVPlacement(0,
		    pos,
		    logicBaSample,
		    "BaSample",
		    logicWorld,
		    false,
		    0);

  //
  sampleVolume = logicBaSample;
  //
  // Carbon Case
  //
  // G4Material* c_mat = nist->FindOrBuildMaterial("G4_C");
  a = 12.01*g/mole;
  G4Element* elnatC = new G4Element(name="natC", symbol="C", z=6, a);
  density=1.175*g/cm3;
  G4Material* c_mat = new G4Material(name="NatCarbon", density, ncomponents=1);
  c_mat->AddElement(elnatC, natoms=1);
  //
  // Tube
  //
  pos = G4ThreeVector(0*cm, 0*cm, sample_center_pos);
  // Solid
  pRMin = 28.1*mm, pRMax=29.5*mm;
  pDz = 12.7*mm;
  pSPhi = 0*degree, pDPhi = 360*degree;
  G4Tubs* solidCaseTube
    = new G4Tubs("CaseTube",
		 pRMin,
		 pRMax,
		 pDz/2,
		 pSPhi,
		 pDPhi);
  // Logical Volume
  G4LogicalVolume* logicCaseTube
    = new G4LogicalVolume(solidCaseTube,
			  c_mat,
			  "CaseTube");
  // Placement
  new G4PVPlacement(0,
		    pos,
		    logicCaseTube,
		    "CaseTube",
		    logicWorld,
		    false,
		    0);
  //
  // top and bottom
  //
  // Solid
  pRMin = 0.0*mm, pRMax=29.5*mm;
  pSPhi = 0*degree, pDPhi = 360*degree;
  G4double topThickness = 1.0*mm;
  G4double bottomThickness = 1.1*mm;

  G4Tubs* solidCaseTop
    = new G4Tubs("CaseTop",
		 pRMin,
		 pRMax,
		 topThickness/2,
		 pSPhi,
		 pDPhi);
  G4Tubs* solidCaseBottom
    = new G4Tubs("CaseBottom",
		 pRMin,
		 pRMax,
     bottomThickness/2,
 		 pSPhi,
		 pDPhi);
  // Logical Volume
  G4LogicalVolume* logicCaseTop
    = new G4LogicalVolume(solidCaseTop,
			  c_mat,
			  "CaseTop");
  G4LogicalVolume* logicCaseBottom
    = new G4LogicalVolume(solidCaseBottom,
			  c_mat,
			  "CaseBottom");
  // Placement
  pos = G4ThreeVector(0*cm, 0*cm, 0*cm);
  new G4PVPlacement(0,
		    G4ThreeVector(0, 0, sample_center_pos+(pDz/2+topThickness/2)),
		    logicCaseTop,
		    "CaseTop",
		    logicWorld,
		    false,
		    0);
  new G4PVPlacement(0,
		    G4ThreeVector(0, 0, sample_center_pos-(pDz/2+bottomThickness/2)),
		    logicCaseBottom,
		    "CaseBottom",
		    logicWorld,
		    false,
		    0);

#endif
  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
