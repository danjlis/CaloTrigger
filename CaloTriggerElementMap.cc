// File: CaloTriggerElementMap.cc
// Author: Daniel Lis
// Brief: Class for the a single CaloTrigger ElementMap (All Trigger Areas)

#include "CaloTriggerElementMap.h"

#include <calobase/RawTower.h>

#include <cstdlib>

#include <iostream>

using namespace std;

void CaloTriggerElementMap::Reset()
{

}

int CaloTriggerElementMap::isValid()
{

}

void CaloTriggerElementMap::identify(std::ostream &os = std::cout)
{

}

ConstIterator CaloTriggerElementMap::AddElement(const unsigned int ieta, const unsigned int iphi, CaloTriggerElement *twr)
{}

ConstIterator CaloTriggerElementMap::AddElement(CaloTriggerElementDefs::keytype key, CaloTriggerElement *twr)
{}


CaloTriggerElement *CaloTriggerElementMap::getElement(CaloTriggerElementDefs::keytype key)
{}
const CaloTriggerElement *CaloTriggerElementMap::getElement(CaloTriggerElementDefs::keytype key)
{}

CaloTriggerElement *CaloTriggerElementMap::getElement(const unsigned int ieta, const unsigned int iphi)
{}
const CaloTriggerElement *CaloTriggerElementMap::getElement(const unsigned int ieta, const unsigned int iphi)
{}

CaloTriggerElement *CaloTriggerElementMap::getElement(const unsigned int ieta, const unsigned int iphi, const unsigned int il )
{}

const CaloTriggerElement *CaloTriggerElementMap::getElement(const unsigned int ieta, const unsigned int iphi, const unsigned int il)
{}

//! return all Elements
ConstRange CaloTriggerElementMap::getElements()
{}

void CaloTriggerElementMap::compress(const double emin)
{}

double CaloTriggerElementMap::getTotalEdep()
{}
