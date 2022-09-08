// File: CaloTriggerElementMap.cc
// Author: Daniel Lis
// Brief: Class for the a single CaloTrigger ElementMap (All Trigger Areas)

#include "CaloTriggerElementMap.h"
#include "CaloTriggerElement.h"
#include "CaloTriggerElementDefs.h"

#include <cstdlib>

#include <iostream>

using namespace std;

void CaloTriggerElementMap::Reset()
{
  while (_towers.begin() != _towers.end())
  {
    delete _towers.begin()->second;
    _towers.erase(_towers.begin());
  }
}

int CaloTriggerElementMap::isValid()
{
  return (!_towers.empty());
}

void CaloTriggerElementMap::identify(std::ostream &os = std::cout)
{
  os << "CaloTriggerElementMap, number of Elements: " << size() << std::endl;
}

CaloTriggerElementMap::ConstIterator CaloTriggerElementMap::AddElement(const unsigned int ieta, const unsigned int iphi, CaloTriggerElement *twr)
{
  CaloTriggerElementDefs::keytype key = CaloTriggerElementDefs::encode_towerid(_caloid, ieta, iphi);
  _elements[key] = twr;
  twr->set_id(key);  // force tower key to be synced to container key

  return _elements.find(key);
}

CaloTriggerElementMap::ConstIterator CaloTriggerElementMap::AddElement(CaloTriggerElementDefs::keytype key, CaloTriggerElement *twr)
{
  if (CaloTriggerElementDefs::decode_caloid(key) != _caloid)
  {
    cout << "CaloTriggerTower::AddTower - Error - adding tower to wrong container! Container CaloID = "
         << _caloid << ", requested CaloID = " << CaloTriggerElementDefs::decode_caloid(key) << " based on key " << key << endl;
    exit(2);
  }

  _elements[key] = twr;
  twr->set_id(key);  // force tower key to be synced to container key

  return _elements.find(key);
}


CaloTriggerElement *CaloTriggerElementMap::getElement(CaloTriggerElementDefs::keytype key)
{
  Iterator it = _elements.find(key);
  if (it != _elements.end())
  {
    return it->second;
  }
  return NULL;
}

const CaloTriggerElement *CaloTriggerElementMap::getElement(CaloTriggerElementDefs::keytype key)
{
  ConstIterator it = _elements.find(key);
  if (it != _elements.end())
  {
    return it->second;
  }
  return NULL;
}

CaloTriggerElement *CaloTriggerElementMap::getElement(const unsigned int ieta, const unsigned int iphi)
{
  CaloTriggerElementDefs::keytype key = CaloTriggerElementDefs::encode_towerid(_caloid, ieta, iphi);
  return getElement(key);
}

const CaloTriggerElement *CaloTriggerElementMap::getElement(const unsigned int ieta, const unsigned int iphi)
{
  CaloTriggerElementDefs::keytype key = CaloTriggerElementDefs::encode_towerid(_caloid, ieta, iphi);
  return getElement(key);
}

CaloTriggerElement *CaloTriggerElementMap::getElement(const unsigned int ieta, const unsigned int iphi, const unsigned int il )
{
  CaloTriggerElementDefs::keytype key = CaloTriggerElementDefs::encode_towerid(_caloid, ieta, iphi, il);
  return getElement(key);
}

const CaloTriggerElement *CaloTriggerElementMap::getElement(const unsigned int ieta, const unsigned int iphi, const unsigned int il)
{
  CaloTriggerElementDefs::keytype key = CaloTriggerElementDefs::encode_towerid(_caloid, ieta, iphi, il);
  return getElement(key);
}

//! return all Elements
CaloTriggerElementMap::Range CaloTriggerElementMap::getElements()
{
  return make_pair(_elements.begin(), _elements.end());

}

CaloTriggerElementMap::ConstRange CaloTriggerElementMap::getElements()
{
  return make_pair(_elements.begin(), _elements.end());
}
