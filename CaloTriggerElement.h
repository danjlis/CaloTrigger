// File: CaloTriggerElement.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger Element (Trigger Area)

#ifndef CALOTRIGGERELEMENT_H
#define CALOTRIGGERELEMENT_H

#include <phool/PHObject.h>
#include <map>
#include "CaloTriggerTowerDefs.h"
#include "CaloTriggerTower.h"

class CaloTriggerTower;

class CaloTriggerElement : public PHObject
{
public:
    typedef std::map<CaloTriggerTowerDefs::keytype, CaloTriggerTower *> Map;
    typedef Map::iterator Iterator;

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
