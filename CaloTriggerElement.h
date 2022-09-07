// File: CaloTriggerElement.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger Element (Trigger Area)

#ifndef CALOTRIGGERELEMENT_H
#define CALOTRIGGERELEMENT_H

#include <phool/PHObject.h>
#include <map>
#include <iostream>

#include "CaloTriggerTowerDefs.h"
#include "CaloTriggerTower.h"

class CaloTriggerTower;

class CaloTriggerElement : public PHObject
{
public:
    typedef std::map<CaloTriggerTowerDefs::keytype, CaloTriggerTower *> Map;
    typedef Map::iterator Iterator;
    typedef Map::const_iterator ConstIterator;
    typedef std::pair<Iterator, Iterator> Range;
    typedef std::pair<ConstIterator, ConstIterator> ConstRange;


    CaloTriggerElement(CaloTriggerTowerDefs::CalorimeterId caloid = CaloTriggerTowerDefs::NONE) : _caloid(caloid){}

    ~CaloTriggerElement() override;

    void Reset() override;
    int isValid() const override;
    void identify(std::ostream &os = std::cout) const override;


      void setCalorimeterID(CaloTriggerTowerDefs::CalorimeterId caloid) { _caloid = caloid; }
      CaloTriggerTowerDefs::CalorimeterId getCalorimeterID() { return _caloid; }

      ConstIterator AddTower(const unsigned int ieta, const unsigned int iphi, CaloTriggerTower *twr);
      ConstIterator AddTower(CaloTriggerTowerDefs::keytype key, CaloTriggerTower *twr);

      CaloTriggerTower *getTower(CaloTriggerTowerDefs::keytype key);
      const CaloTriggerTower *getTower(CaloTriggerTowerDefs::keytype key) const;

      CaloTriggerTower *getTower(const unsigned int ieta, const unsigned int iphi);
      const CaloTriggerTower *getTower(const unsigned int ieta, const unsigned int iphi) const;

      CaloTriggerTower *getTower(const unsigned int ieta, const unsigned int iphi, const unsigned int il );
      const CaloTriggerTower *getTower(const unsigned int ieta, const unsigned int iphi, const unsigned int il) const;

      //! return all towers
      ConstRange getTowers(void) const;
      Range getTowers(void);

      unsigned int size() const { return _towers.size(); }
      void compress(const double emin);
      double getTotalEdep() const;

     protected:
      CaloTriggerTowerDefs::CalorimeterId _caloid;
      Map _towers;

      ClassDefOverride(CaloTriggerElement, 1)
    };

};

#endif
