// File: CaloTriggerElement.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger Element (Trigger Area)

#ifndef CALOTRIGGERELEMENT_H
#define CALOTRIGGERELEMENT_H

#include <fun4all/SubsysReco.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHRandomSeed.h>
#include <phool/getClass.h>
#include <string>

class PHCompositeNode;
class CaloTriggerTower;

class CaloTriggerElement
{
public:
    CaloTriggerElement();
    ~CaloTriggerElement() override;

    void InitiateElement();
    CaloTriggerElement GetTower(int tower);

private:
  int _layer;
  std::vector<std::pair<int, CaloTriggerTower*>> _calo_trigger_towers;

  void AddTower(CaloTriggerTowert* calo_trigger_Tower);

};

#endif
