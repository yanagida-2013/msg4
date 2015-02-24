#pragma once

#include <Randomize.hh>
#include <vector>

// #define CHECK

namespace my_nsp {
void my_nsp(double *kev) {
  // 自分で設定するのは次の２行だけ。
  std::vector<double> neutron_energy = { 1, 2, 3, 4, 5};
  std::vector<double> intensity = { 0.2, 0.2, 0.2, 0.1, 0.3};





  // このCHECKはシミュレーション速度を低下させる。
  // 長さが同じで昇順だったら問題ない。
#ifdef CHECK
  // 長さが同じかチェック
  if (neutron_energy.size() != intensity.size()) std::exit(0);

  // エネルギーが昇順で並んでいるかチェック
  std::vector<double> tmp;
  std::copy(neutron_energy.begin(), neutron_energy.end(), std::back_inserter(tmp));
  std::sort(tmp.begin(), tmp.end());

  if (neutron_energy != tmp) std::exit(0);
#endif

  double e_max = *std::max_element(neutron_energy.begin(), neutron_energy.end());
  double e_min = *std::min_element(neutron_energy.begin(), neutron_energy.end());

  double i_max = *std::max_element(intensity.begin(), intensity.end());
  double i_min = *std::min_element(intensity.begin(), intensity.end());

  while(1) {
    double e_rnd = (e_max - e_min) * G4UniformRand() + e_min;
    double i_rnd = (i_max - i_min) * G4UniformRand() + i_min;

    // printf("# Random number :\n");
    // printf("e_rnd = %f kev\n", e_rnd);
    // printf("i_rnd = %f \n", i_rnd);

    int i = 0;
    for(; i < neutron_energy.size()-1; i++) {
        if (neutron_energy[i] < e_rnd && e_rnd < neutron_energy[i+1]) {
            break;
        }
    }
    // printf("index = %d\n", i);

    // 線形的に求める
    double i_e_rnd = ((intensity[i+1]-intensity[i])*e_rnd - neutron_energy[i]*intensity[i+1] + neutron_energy[i+1]*intensity[i]) / (neutron_energy[i+1] - neutron_energy[i]);
    // printf("i_e_rnd = %f \n", i_e_rnd);
    if (i_rnd < i_e_rnd) {
        *kev = e_rnd;
        break;
    }
  }

}
}
