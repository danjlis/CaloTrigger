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
  os << "CaloTriggerTower, number of towers: " << size() << std::endl;
}

CaloTriggerElement::ConstIterator CaloTriggerElement::AddTower(const unsigned int ieta, const unsigned int iphi, CaloTriggerTower *twr)
{

}

CaloTriggerElement::ConstIterator CaloTriggerElement::AddTower(CaloTriggerTowerDefs::keytype key, CaloTriggerTower *twr)
{

}

CaloTriggerTower *CaloTriggerElement::getTower(CaloTriggerTowerDefs::keytype key)
{

}
const CaloTriggerTower *CaloTriggerElement::getTower(CaloTriggerTowerDefs::keytype key){

}

CaloTriggerTower *CaloTriggerElement::getTower(const unsigned int ieta, const unsigned int iphi)
{

}

const CaloTriggerTower *getTower(const unsigned int ieta, const unsigned int iphi)
{

}

CaloTriggerTower *CaloTriggerElement::getTower(const unsigned int ieta, const unsigned int iphi, const unsigned int il )
{

}

const CaloTriggerTower *CaloTriggerElement::getTower(const unsigned int ieta, const unsigned int iphi, const unsigned int il)
{

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

void CaloTriggerElement::compress(const double emin)
{

}

double CaloTriggerElement::getTotalEdep()
{

}

CaloTriggerElement::ClassDefOverride(CaloTriggerElement, 1)
[

]
