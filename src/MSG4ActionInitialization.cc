#include "MSG4ActionInitialization.hh"
#include "MSG4PrimaryGeneratorAction.hh"
#include "MSG4SteppingAction.hh"
#include "MSG4RunAction.hh"
#include "MSG4EventAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4ActionInitialization::MSG4ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4ActionInitialization::~MSG4ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MSG4ActionInitialization::BuildForMaster() const {
	SetUserAction(new MSG4RunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MSG4ActionInitialization::Build() const {
	SetUserAction(new MSG4PrimaryGeneratorAction);
	SetUserAction(new MSG4RunAction);
	SetUserAction(new MSG4EventAction);
	SetUserAction(new MSG4SteppingAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
