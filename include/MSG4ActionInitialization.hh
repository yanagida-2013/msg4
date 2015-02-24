#ifndef MSG4ActionInitialization_h
#define MSG4ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

/// Build() function inits all the action.
/// For example,
///  - PrimaryAction
///  - SteppingAction
///  - EventAction
///  - RunAction
///  - TrackingAction

/// BuildForMaster() function is for multi-threading.

class MSG4ActionInitialization : public G4VUserActionInitialization
{
public:
  MSG4ActionInitialization();
  virtual ~MSG4ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

