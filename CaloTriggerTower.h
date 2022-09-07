// File: CaloTriggerTower.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger Tower (one fiber worth of channels (64))

#ifndef CALOTRIGGERTOWER_H
#define CALOTRIGGERTOWER_H

#include <fun4all/SubsysReco.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHRandomSeed.h>
#include <phool/getClass.h>
#include <string>

class PHCompositeNode;

class CaloTriggerTower
{
public:
    CaloTriggerTower();
    ~CaloTriggerTower() override;

    void SetLayer(int layer) { _layer = layer; };
    void SetEta(int eta) { _eta = eta; };
    void SetPhi(int phi) { _phi = phi; };

private:
  int _layer;
  int _hit;
  int _phi;
  int _eta;

  std::vector<std::pair<int, CaloTriggerElement*>> _calo_trigger_elements;

  void AddElement(CaloTriggerElement* calo_trigger_element);

};

#endif
