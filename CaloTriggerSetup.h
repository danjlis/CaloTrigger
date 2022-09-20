// File: CaloTriggerSetup.h
// Author: Daniel Lis
// Brief: This header file gives all the parameters for the set up of all the towers and elements and maps

#ifndef CALOTRIGGERSETUP_H
#define CALOTRIGGERSETUP_H

#include <string>

// The enum for Calorimeter ID is declared and defined here
enum CaloID {
  NONE = 0,
  CEMC = 1,
  HCALOUT = 2,
  HCALIN = 3
};


// Here lies the specs for each detector.
namespace EMCALSpecs {

  static unsigned int n_elements = 32;
  static unsigned int n_calotower_per_element = 12;
  static unsigned int n_tower_per calo_tower = 64;
  static unsigned int n_phi_tower = 256;
  static unsigned int n_eta_tower = 96;
  static unsinged int n_towers = n_phi*n_eta;

  static unsinged int n_phi_calotower = 32;
  static unsinged int n_eta_calotower = 12;
  static unsinged int n_calotowers = n_phi_calotower*n_eta_calotower;

  static unsinged int n_phi_caloelement = 32;
  static unsinged int n_eta_caloelement = 1;
  static unsinged int n_caloelements = n_phi_caloelement*n_eta_caloelement;
}

namespace HCALINSpecs {
  static unsigned int n_phi_tower = 64;
  static unsigned int n_eta_tower = 24;
  static unsinged int n_towers = n_phi*n_eta;

  static unsinged int n_phi_calotower = 8;
  static unsinged int n_eta_calotower = 3;
  static unsinged int n_calotowers = n_phi_calotower*n_eta_calotower;

  static unsinged int n_phi_caloelement = 2;
  static unsinged int n_eta_caloelement = 1;
  static unsinged int n_caloelements = n_phi_caloelement*n_eta_caloelement;
}

namespace HCALOUTSpecs {
  static unsigned int n_phi_tower = 64;
  static unsigned int n_eta_tower = 24;
  static unsinged int n_towers = n_phi*n_eta;

  static unsinged int n_phi_calotower = 8;
  static unsinged int n_eta_calotower = 3;
  static unsinged int n_calotowers = n_phi_calotower*n_eta_calotower;

  static unsinged int n_phi_caloelement = 2;
  static unsinged int n_eta_caloelement = 1;
  static unsinged int n_caloelements = n_phi_caloelement*n_eta_caloelement;
}


#endif
