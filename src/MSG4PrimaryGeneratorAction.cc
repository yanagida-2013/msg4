#include "MSG4PrimaryGeneratorAction.hh"
#include "MSG4SteppingAction.hh"
#include "MSG4RunAction.hh"
#include "MSG4Run.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include "Randomize.hh"


#include "my_neutron_spectrum.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4PrimaryGeneratorAction::MSG4PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  // In this Function, you must set
  // - number of the bombarded particle
  // - the definition of the particle
  // - the energy of the particle
  // - the momentumDirection
  //
  // in addtion, you can set
  // - the charge
  // - polarization
  //
  // see details in G4ParticleGun.hh
  //
  // To set the particle, we use variable "fParticleGun".
  // fParticleGun is an instance of G4ParticleGun.
  //


  // number of neutron
  G4int number_of_particle = 1;
  fParticleGun  = new G4ParticleGun(number_of_particle);

  // Get the Definitions of particles from ParticleTable
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "neutron");
  fParticleGun->SetParticleDefinition(particle);

  // Z positive direction
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4PrimaryGeneratorAction::~MSG4PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MSG4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  // This function is called at the beginning of each event.
  //
  G4double radiusOfNeutronBeam = 0.5*cm;

  // Initializing Neutron Energy
  //
  G4double neutronEnergy = 0.0;
  G4double theta = 0;
  G4double phi = 0;


  const MSG4Run* run = static_cast<const MSG4Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());

  // 実験で得られた中性子スペクトルからランダムにエネルギーを取り出す。thetaは0°。
  my_nsp::my_nsp(&neutronEnergy);
  /*
  while(1) {
    my_nsp::my_nsp(&neutronEnergy);
    if (neutronEnergy < run->GetVecGates().back() && neutronEnergy > run->GetVecGates().front()) {
      break;
    }
  }
  printf("%f\n", neutronEnergy);
  */

  // 装填
  //
  phi = 2*CLHEP::pi*G4UniformRand();
  fParticleGun->SetParticleEnergy(neutronEnergy*keV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta)));

  // あとで取り出せるように。
  incident_neutron_energy = neutronEnergy;

  // G4cout << fParticleGun->GetParticleEnergy()/keV << G4endl;
  // G4cout << fParticleGun->GetParticleMomentumDirection() << G4endl;

  // ビームの射出位置を指定。
  // 陽子ビームの広がりは等方的であると仮定。
  // The z-length of the Volume "World" is 30cm.
  // So, neutrons are emitted from -15cm.
  //
  G4double x_pos = (0.5 - G4UniformRand()) * 2 * radiusOfNeutronBeam;
  G4double y_pos = (0.5 - G4UniformRand()) * 2 * radiusOfNeutronBeam;
  fParticleGun->SetParticlePosition(G4ThreeVector(x_pos, y_pos, -15*cm));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
