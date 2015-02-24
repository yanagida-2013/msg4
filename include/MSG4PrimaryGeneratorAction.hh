#ifndef MSG4PrimaryGeneratorAction_h
#define MSG4PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

/// The primary generator action class with particle gun.
///

class MSG4PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    MSG4PrimaryGeneratorAction();    
    virtual ~MSG4PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

    G4double GetIncidentNeutronEnergy() const { return incident_neutron_energy; }

  
  private:
    G4ParticleGun* fParticleGun; // pointer a to G4 gun class
    G4double incident_neutron_energy;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

