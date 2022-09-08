// File: CaloTriggerTower.cc
// Author: Daniel Lis
// Brief: Class for the a single CaloTrigger Tower

#include "CaloTriggerTower.h"
#include <calobase/RawTower.h>
#include <calobase/RawTowerDefs.h>

CaloTriggerTower::ConstRange CaloTriggerTower::getTowers()
{
  return make_pair(_towers.begin(), _towers.end());
}

CaloTriggerTower::Range CaloTriggerTower::getTowers()
{
  return make_pair(_towers.begin(), _towers.end());
}

CaloTriggerTower::ConstIterator CaloTriggerTower::AddTower(const unsigned int ieta, const int unsigned iphi, RawTower *rawtower)
{
  RawTowerDefs::keytype key = RawTowerDefs::encode_towerid(_caloid, ieta, iphi);
  _towers[key] = rawtower;
  rawtower->set_id(key);  // force tower key to be synced to container key

  return _towers.find(key);
}

CaloTriggerTower::ConstIterator CaloTriggerTower::AddTower(RawTowerDefs::keytype key, RawTower *twr)
{
  if (RawTowerDefs::decode_caloid(key) != _caloid)
  {
    cout << "CaloTriggerTower::AddTower - Error - adding tower to wrong container! Container CaloID = "
         << _caloid << ", requested CaloID = " << RawTowerDefs::decode_caloid(key) << " based on key " << key << endl;
    exit(2);
  }

  _towers[key] = twr;
  twr->set_id(key);  // force tower key to be synced to container key

  return _towers.find(key);
}

RawTower *CaloTriggerTower::getTower(RawTowerDefs::keytype key)
{
  ConstIterator it = _towers.find(key);
  if (it != _towers.end())
  {
    return it->second;
  }
  return NULL;
}

const RawTower *CaloTriggerTower::getTower(RawTowerDefs::keytype key) const
{
  ConstIterator it = _towers.find(key);
  if (it != _towers.end())
  {
    return it->second;
  }
  return NULL;
}

RawTower *CaloTriggerTower::getTower(const unsigned int ieta, const unsigned int iphi)
{
  RawTowerDefs::keytype key = RawTowerDefs::encode_towerid(_caloid, ieta, iphi);
  return getTower(key);
}

const RawTower *CaloTriggerTower::getTower(const unsigned int ieta, const unsigned int iphi) const
{
  RawTowerDefs::keytype key = RawTowerDefs::encode_towerid(_caloid, ieta, iphi);
  return getTower(key);
}

RawTower *CaloTriggerTower::getTower(const unsigned int ieta, const unsigned int iphi , const unsigned int il)
{
  RawTowerDefs::keytype key = RawTowerDefs::encode_towerid(_caloid, ieta, iphi, il);
  return getTower(key);
}

const RawTower *CaloTriggerTower::getTower(const unsigned int ieta, const unsigned int iphi, const unsigned int il) const
{
  RawTowerDefs::keytype key = RawTowerDefs::encode_towerid(_caloid, ieta, iphi, il);
  return getTower(key);
}


int CaloTriggerTower::isValid() const
{
  return (!_towers.empty());
}

void CaloTriggerTower::Reset()
{
  while (_towers.begin() != _towers.end())
  {
    delete _towers.begin()->second;
    _towers.erase(_towers.begin());
  }
}

void CaloTriggerTower::identify(std::ostream &os) const
{
  os << "CaloTriggerTower, number of towers: " << size() << std::endl;
}

double CaloTriggerTower::getTotalEdep() const
{
  double totalenergy = 0;
  ConstIterator iter;
  for (iter = _towers.begin(); iter != _towers.end(); ++iter)
  {
    totalenergy += iter->second->get_energy();
  }
  return totalenergy;
}
