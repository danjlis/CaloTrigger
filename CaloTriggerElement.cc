// File: CaloTriggerElement.cc
// Author: Daniel Lis
// Brief: Class for the a single CaloTrigger Element (Trigger Area)

#include "CaloTriggerElement.h"
#include "CaloTriggerElementDefs.h"

#include <iostream>

#include "CaloTriggerTower.h"
#include "CaloTriggerTowerDefs.h"

void CaloTriggerElement::Reset()
{
  while (_towers.begin() != _towers.end())
  {
    delete _towers.begin()->second;
    _towers.erase(_towers.begin());
  }
}
int CaloTriggerElement::isValid(){
  return (!_towers.empty());
}
void CaloTriggerElement::identify(std::ostream &os = std::cout)
{
  os << "CaloTriggerElement, number of towers: " << size() << std::endl;
}

CaloTriggerElement::ConstIterator CaloTriggerElement::AddTower(const unsigned int ieta, const unsigned int iphi, CaloTriggerTower *twr)
{
  CaloTriggerTowerDefs::keytype key = CaloTriggerTowerDefs::encode_towerid(_caloid, ieta, iphi);
  _towers[key] = twr;
  rawtower->set_id(key);  // force tower key to be synced to container key

  return _towers.find(key);
}

CaloTriggerElement::ConstIterator CaloTriggerElement::AddTower(CaloTriggerTowerDefs::keytype key, CaloTriggerTower *twr)
{
  if (CaloTriggerTowerDefs::decode_caloid(key) != _caloid)
  {
    cout << "CaloTriggerTower::AddTower - Error - adding tower to wrong container! Container CaloID = "
         << _caloid << ", requested CaloID = " << CaloTriggerTowerDefs::decode_caloid(key) << " based on key " << key << endl;
    exit(2);
  }

  _towers[key] = twr;
  twr->set_id(key);  // force tower key to be synced to container key

  return _towers.find(key);
}

CaloTriggerTower *CaloTriggerElement::getTower(CaloTriggerTowerDefs::keytype key)
{
  Iterator it = _towers.find(key);
  if (it != _towers.end())
  {
    return it->second;
  }
  return NULL;
}
const CaloTriggerTower *CaloTriggerElement::getTower(CaloTriggerTowerDefs::keytype key){
  ConstIterator it = _towers.find(key);
  if (it != _towers.end())
  {
    return it->second;
  }
  return NULL;
}

CaloTriggerTower *CaloTriggerElement::getTower(const unsigned int ieta, const unsigned int iphi)
{
  CaloTriggerTowerDefs::keytype key = CaloTriggerTowerDefs::encode_towerid(_caloid, ieta, iphi);
  return getTower(key);
}

const CaloTriggerTower *getTower(const unsigned int ieta, const unsigned int iphi)
{
  CaloTriggerTowerDefs::keytype key = CaloTriggerTowerDefs::encode_towerid(_caloid, ieta, iphi);
  return getTower(key);
}

CaloTriggerTower *CaloTriggerElement::getTower(const unsigned int ieta, const unsigned int iphi, const unsigned int il )
{
  CaloTriggerTowerDefs::keytype key = CaloTriggerTowerDefs::encode_towerid(_caloid, ieta, iphi, il);
  return getTower(key);
}

const CaloTriggerTower *CaloTriggerElement::getTower(const unsigned int ieta, const unsigned int iphi, const unsigned int il)
{
  CaloTriggerTowerDefs::keytype key = CaloTriggerTowerDefs::encode_towerid(_caloid, ieta, iphi, il);
  return getTower(key);
}

//! return all towers
CaloTriggerElement::ConstRange CaloTriggerElement::getTowers()
{
  return make_pair(_towers.begin(), _towers.end());
}

CaloTriggerElement::Range CaloTriggerElement::getTowers()
{
  return make_pair(_towers.begin(), _towers.end());
}

double CaloTriggerElement::getTotalEdep()
{
  double totalenergy = 0;
  ConstIterator iter;
  for (iter = _towers.begin(); iter != _towers.end(); ++iter)
  {
    totalenergy += iter->second->getTotalEdep();
  }
  return totalenergy;
}
