// File: CaloTriggerElementMap.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger ElementMap (All Trigger Areas)

#ifndef CALOTRIGGERELEMENTMAP_H
#define CALOTRIGGERELEMENTMAP_H

#include <fun4all/SubsysReco.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHRandomSeed.h>
#include <phool/getClass.h>
#include <string>

class PHCompositeNode;
class CaloTriggerElement;

class CaloTriggerElementMap
{
public:
    CaloTriggerElementMap();
    ~CaloTriggerElementMap() override;

    void SetLayer(int layer) { _layer = layer; };
    void InitiateMap();
    CaloTriggerElement GetElement(int element);

private:
  int _layer;

  int _hit;

  std::vector<std::pair<int, CaloTriggerElement*>> _calo_trigger_elements;

  void AddElement(CaloTriggerElement* calo_trigger_element);

};

#endif
