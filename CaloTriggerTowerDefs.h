// File: CaloTriggerElementMap.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger ElementMap (All Trigger Areas)

#ifndef CALOTRIGGERTOWERDEFS_H
#define CALOTRIGGERTOWERDEFS_H

namespace CaloTriggerTowerDefs{

  typedef unsigned int keytype;

  static unsigned int calo_idbits = 8;
  static unsigned int tower_idbits = sizeof(keytype) * 8 - calo_idbits;
  static unsigned int index1_idbits = tower_idbits / 2;

  enum CalorimeterId
  {
    NONE = 0,
    CEMC = 1,
    HCALOUT = 2,
    HCALIN = 3
  };

  inline CaloTriggerTowerDefs::keytype encode_towerid(const CalorimeterId calo_id, const unsigned int tower_index_1,
                const unsigned int tower_index_2)
 {
   CaloTriggerTowerDefs::keytype calo_tower_id = 0;

   if (tower_index_1 < 0xFFF && tower_index_2 < 0xFFF)
   {
     calo_tower_id = (calo_id << CaloTriggerTowerDefs::tower_idbits) + (tower_index_1 << CaloTriggerTowerDefs::index1_idbits) + tower_index_2;
   }
   else
   {
     std::cout << "too large index1 and/or index2; index1: "
               << tower_index_1 << " (max val " << 0xFFF << ")"
               << ", index2: "
               << tower_index_2 << " (max val " << 0xFFF << ")" << std::endl;
     exit(1);
   }

   return calo_tower_id;
 }


}

#endif
