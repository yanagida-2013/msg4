#include "MSG4EventAction.hh"
#include "MSG4Run.hh"
#include "MSG4RunAction.hh"
#include "MSG4SteppingAction.hh"

#include "G4RunManager.hh"

MSG4EventAction::MSG4EventAction()
:G4UserEventAction()
{}

MSG4EventAction::~MSG4EventAction()
{}

void MSG4EventAction::BeginOfEventAction(const G4Event*) {
  // 弾性散乱フラグを初期化
	MSG4SteppingAction* action = static_cast<MSG4SteppingAction*>(G4EventManager::GetEventManager()->GetTrackingManager()->GetSteppingManager()->GetUserAction());
	action->setFlag(false);
}

void MSG4EventAction::EndOfEventAction(const G4Event*) {
	MSG4Run* msg4Run = static_cast<MSG4Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
	// 10000回ごとに表示
	if (msg4Run->GetNumberOfEvent() % 10000 == 0) {
		const MSG4RunAction* ra = static_cast<const MSG4RunAction*>(G4RunManager::GetRunManager()->GetUserRunAction());
		auto start = ra->GetStartTime();
		auto elapsed = std::chrono::system_clock::now() - start;
		G4cout << "# " << msg4Run->GetNumberOfEvent() << " at " << std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() << " [sec]"  << G4endl;
	}
}
