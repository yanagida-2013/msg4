#ifndef MSG4EventAction_h
#define MSG4EventAction_h

#include "G4UserEventAction.hh"

class G4Event;

class MSG4EventAction : public G4UserEventAction
{
public:
	MSG4EventAction();
	~MSG4EventAction();

	void virtual BeginOfEventAction(const G4Event*);
	void virtual EndOfEventAction(const G4Event*);
};

#endif
