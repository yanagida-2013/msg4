#ifndef MSG4Run_h
#define MSG4Run_h 1

#include "G4Run.hh"
#include <vector>
#include <array>
class G4Event;

/// Run class
///

/// Normally, Run class holds the important physical quantity such as Energy deposit.
/// In this program, this class holds the number of capture events occured.

class MSG4Run : public G4Run {
public:
    MSG4Run();
    ~MSG4Run();

    // for master thread
    virtual void Merge(const G4Run*);

    // 中性子のエネルギー、散乱されたか、計測対象の核種かに合わせてカウントを増やす
    // void inc_gated(G4double neutronEnergy, G4bool isScattered, G4bool isSample);
    void inc_gated(G4double neutronEnergy, G4int indexOfIsotope, G4bool isScattered);

    size_t GetNumberOfGates() const { return gates.size()-1; }
    // std::vector<G4int> GetVecTC() const { return gated_target_capture; }
    // std::vector<G4int> GetVecIC() const { return gated_impurity_capture; }
    // std::vector<G4int> GetVecTCWS() const { return gated_target_capture_without_scattering; }
    // std::vector<G4int> GetVecICWS() const { return gated_impurity_capture_without_scattering ; }
    std::vector<G4int> GetVecC(G4int index) const { return gated_capture[index]; }
    std::vector<G4int> GetVecCWS(G4int index) const { return gated_capture_without_scattering[index]; }
    std::vector<G4double> GetVecGates() const { return gates; }

private:
    std::vector<G4double> gates;
    // std::vector<G4int> gated_target_capture;
    // std::vector<G4int> gated_impurity_capture;
    // std::vector<G4int> gated_target_capture_without_scattering;
    // std::vector<G4int> gated_impurity_capture_without_scattering;
    std::array<std::vector<G4int>, 6> gated_capture;
    std::array<std::vector<G4int>, 6> gated_capture_without_scattering;
};

#endif
