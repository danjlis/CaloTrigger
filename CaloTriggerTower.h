// File: CaloTriggerTower.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger Tower (one fiber worth of channels (64))

#ifndef CALOTRIGGERTOWER_H
#define CALOTRIGGERTOWER_H

#include <phool/PHObject.h>

#include <calobase/RawTower.h>
#include <calobase/RawTowerContainer.h>

#include <string>

class RawTower;
class RawTowerContainer;

class CaloTriggerTower : public PHObject
{
public:
    CaloTriggerTower();
    ~CaloTriggerTower() override;

    void SetLayer(int layer) { _layer = layer; };
    void SetEtaIndex(int ieta) { _index_eta = ieta; };
    void SetPhiIndex(int iphi) { _index_phi = iphi; };
    void InitateTower();
private:
  int _layer;
  int _hit;
  int _index_phi;
  int _index_eta;

  float _eta_high, _eta_low;
  float _phi_high, _phi_low;

  RawTowerContainer _raw_calo_towers;
};

#endif
