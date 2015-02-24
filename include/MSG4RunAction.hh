#ifndef MSG4RunAction_h
#define MSG4RunAction_h 1

#include "G4UserRunAction.hh"
#include <chrono>
#include <vector>

class G4Run;

/// RunAction class
///

/// In BeginOfRunAction function, it gets the starting time.
/// In EndOfRunAction function, it shows the result.

class MSG4RunAction : public G4UserRunAction {
public:
	MSG4RunAction();
	virtual ~MSG4RunAction();

	virtual G4Run* GenerateRun();
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
	const std::chrono::system_clock::time_point GetStartTime() const { return starting_time; };

private:
	std::chrono::system_clock::time_point starting_time;
};

#endif
