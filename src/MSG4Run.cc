#include "MSG4Run.hh"
#include "G4RunManager.hh"


MSG4Run::MSG4Run() {
	// ゲートのエネルギーをセット
	//
	gates = {15, 20, 28 ,33, 50, 80};
	for (int j = 0; j < 6; j++) {
		gated_capture[j] = {0, 0, 0, 0, 0};
		gated_capture_without_scattering[j] = {0, 0, 0, 0, 0};
	}
	// for(size_t i = 0; i < gates.size()-1; i++) {
		// gated_target_capture.push_back(0);
		// gated_impurity_capture.push_back(0);
		// gated_impurity_capture_without_scattering.push_back(0);
		// gated_target_capture_without_scattering.push_back(0);
	// }
}

MSG4Run::~MSG4Run()
{}

void MSG4Run::Merge(const G4Run* run) {
	// Function for multi-threading

	// Get the local run pointer
	const MSG4Run* localRun = static_cast<const MSG4Run*>(run);

	// Get each data of the local Run
	for(size_t i = 0; i < localRun->GetNumberOfGates(); i++) {
		// gated_target_capture[i] += localRun->gated_target_capture[i];
		// gated_target_capture_without_scattering[i] += localRun->gated_target_capture_without_scattering[i];
		// gated_impurity_capture[i] += localRun->gated_impurity_capture[i];
		// gated_impurity_capture_without_scattering[i] += localRun->gated_impurity_capture_without_scattering[i];
		for(size_t j = 0; j < 6; j++) {
			gated_capture[j][i] += localRun->gated_capture[j][i];
			gated_capture_without_scattering[j][i] += localRun->gated_capture_without_scattering[j][i];
		}
	}

	// Merge
	G4Run::Merge(run);
}

void MSG4Run::inc_gated(G4double neutron_energy, G4int indexOfIsotope, G4bool isScattered) {
	MSG4Run* localRun = static_cast<MSG4Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
	for(size_t i = 0; i < localRun->GetNumberOfGates(); i++) {
		if(localRun->gates[i] < neutron_energy && localRun->gates[i+1] > neutron_energy) {
			// if(isSample) {
			// 	gated_target_capture[i]++;
			// 	if(!isScattered) {
			// 		gated_target_capture_without_scattering[i]++;
			// 	}
			// } else {
			// 	gated_impurity_capture[i]++;
			// 	if(!isScattered) {
			// 		gated_impurity_capture_without_scattering[i]++;
			// 	}
			// }
			gated_capture[indexOfIsotope][i]++;
			if (!isScattered) {
				gated_capture_without_scattering[indexOfIsotope][i]++;
			}
			break;
		}
	}
	// G4cout << "Neutron Energy: " << neutron_energy << G4endl;
}
