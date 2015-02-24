#ifndef MSG4SteppingAction_h
#define MSG4SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4SteppingManager;

/// Stepping Action class
///

/// UserSteppingAction() is called when the incident step is finished.
/// In this function, it gets what reaction happend at the beggining of step.

/// Actually same thing can be done by TrackingAction.
/// I should have used TrackingAction rather than steppingAction,
/// but there were no examples in basic-example to refer.

class MSG4SteppingAction : public G4UserSteppingAction {
public:
    MSG4SteppingAction();
    ~MSG4SteppingAction();

    void UserSteppingAction(const G4Step* step);
    void setFlag(G4bool flag) { isScattered = flag; };
    G4String GetReactionName();
    G4String GetSecondaryParticle();

private:
    G4bool isScattered;  // scattering flag
};

#endif
