// File: CaloTriggerElementMap.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger ElementMap (All Trigger Areas)

#ifndef CALOTRIGGERELEMENTMAP_H
#define CALOTRIGGERELEMENTMAP_H

#include <phool/PHObject.h>
#include <map>
#include <iostream>

#include "CaloTriggerElementDefs.h"
#include "CaloTriggerElement.h"

class CaloTriggerElement;

class CaloTriggerElementMap : public PHObject
{
public:
    typedef std::map<CaloTriggerElementDefs::keytype, CaloTriggerElement *> Map;
    typedef Map::iterator Iterator;
    typedef Map::const_iterator ConstIterator;
    typedef std::pair<Iterator, Iterator> Range;
    typedef std::pair<ConstIterator, ConstIterator> ConstRange;


    CaloTriggerElement(CaloTriggerElementDefs::CalorimeterId caloid = CaloTriggerElementDefs::NONE) : _caloid(caloid){}

    ~CaloTriggerElement() override;

    void Reset() override;
    int isValid() const override;
    void identify(std::ostream &os = std::cout) const override;


      void setCalorimeterID(CaloTriggerElementDefs::CalorimeterId caloid) { _caloid = caloid; }
      CaloTriggerElementDefs::CalorimeterId getCalorimeterID() { return _caloid; }

      ConstIterator AddElement(const unsigned int ieta, const unsigned int iphi, CaloTriggerElement *twr);
      ConstIterator AddElement(CaloTriggerElementDefs::keytype key, CaloTriggerElement *twr);

      CaloTriggerElement *getElement(CaloTriggerElementDefs::keytype key);
      const CaloTriggerElement *getElement(CaloTriggerElementDefs::keytype key) const;

      CaloTriggerElement *getElement(const unsigned int ieta, const unsigned int iphi);
      const CaloTriggerElement *getElement(const unsigned int ieta, const unsigned int iphi) const;

      CaloTriggerElement *getElement(const unsigned int ieta, const unsigned int iphi, const unsigned int il );
      const CaloTriggerElement *getElement(const unsigned int ieta, const unsigned int iphi, const unsigned int il) const;

      //! return all Elements
      ConstRange getElements(void) const;
      Range getElements(void);

      unsigned int size() const { return _elements.size(); }
      void compress(const double emin);
      double getTotalEdep() const;

     protected:
      CaloTriggerElementDefs::CalorimeterId _caloid;
      Map _elements;

      ClassDefOverride(CaloTriggerElement, 1)
    };

};
