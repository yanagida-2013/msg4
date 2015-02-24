#include "MSG4RunAction.hh"
#include "MSG4PrimaryGeneratorAction.hh"
#include "MSG4Run.hh"
#include "MSG4SteppingAction.hh"


#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <chrono>  // std:C++11
#include <fstream>


MSG4RunAction::MSG4RunAction()
: G4UserRunAction()
{
}

MSG4RunAction::~MSG4RunAction()
{}

G4Run* MSG4RunAction::GenerateRun()
{
  return new MSG4Run;
}

void MSG4RunAction::BeginOfRunAction(const G4Run*) {
  // This function is called when the Run started.
  // So, it's normally called only once.
  starting_time = std::chrono::system_clock::now();
}


void MSG4RunAction::EndOfRunAction(const G4Run* run) {
  // This function is called when the Run ended.
  // So, it's normally called only once.

  // Print
  if (IsMaster()) {
    G4cout << "\n--------------------End of Global Run-----------------------\n";
    G4cout << "\n Time Elapsed:  ";
    // Show the time elapsed
    auto time_elapsed = std::chrono::system_clock::now() - starting_time;
    G4cout << std::chrono::duration_cast<std::chrono::seconds>(time_elapsed).count() << " [sec]"  << G4endl;
    // Data acquisition
    G4int nofEvents = run->GetNumberOfEvent();
    const MSG4Run* msg4Run = static_cast<const MSG4Run*>(run);

    // Print Results
    G4cout << "\nNumber of Events          : " << nofEvents << G4endl;
    G4cout << "Result "<< std::setw(12) << "Ba138" << std::setw(12) << "wosc" << std::setw(12) << "Ba137" << std::setw(12) << "wosc" << std::setw(12) << "Ba136" << std::setw(12) << "wosc" << std::setw(12) << "Ba135" << std::setw(12) << "wosc" << std::setw(12) << "O16" << std::setw(12) << "wosc" << std::setw(12) << "C12" << std::setw(12) << "wosc" << G4endl;
    for(size_t i = 0; i < msg4Run->GetNumberOfGates(); i++) {
      G4cout << "Gate" << i+1 << ": ";
      for (int j = 0; j < 6; j ++) {
        G4cout
        << std::setw(12) << msg4Run->GetVecC(j)[i]
        << std::setw(12) << msg4Run->GetVecCWS(j)[i];
      }
      G4cout << G4endl;
    }
    std::ofstream output( "./result.dat", std::ios::app);
    output << "Time Elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(time_elapsed).count() << " [sec]"  << G4endl;
    output << "\nNumber of Events          : " << nofEvents << std::endl;
    // output << "Result "<< std::setw(12) << "SampCap" << std::setw(12) << "ImpCap" << std::setw(12) << "SampCap wo sc" << std::setw(12) << "ImpCap wo sc" << std::endl;
    output << "Result "<< std::setw(12) << "Ba138" << std::setw(12) << "wosc" << std::setw(12) << "Ba137" << std::setw(12) << "wosc" << std::setw(12) << "Ba136" << std::setw(12) << "wosc" << std::setw(12) << "Ba135" << std::setw(12) << "wosc" << std::setw(12) << "O16" << std::setw(12) << "wosc" << std::setw(12) << "C12" << std::setw(12) << "wosc" << std::endl;
    for(size_t i = 0; i < msg4Run->GetNumberOfGates(); i++) {
      output << "Gate" << i+1 << ": ";
      for (int j = 0; j < 6; j ++) {
        output
        << std::setw(12) << msg4Run->GetVecC(j)[i]
        << std::setw(12) << msg4Run->GetVecCWS(j)[i];
      }
      output << std::endl;
    }

  }
}
