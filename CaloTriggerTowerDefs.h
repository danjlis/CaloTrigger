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

 inline CaloTriggerTowerDefs::keytype encode_towerid(const CalorimeterId calo_id, const unsigned int tower_index)
   {
     CaloTriggerTowerDefs::keytype calo_tower_id = 0;

     if (tower_index < 0xFFFFFF)
     {
       calo_tower_id = (calo_id << CaloTriggerTowerDefs::tower_idbits) + tower_index;
     }
     else
     {
       std::cout << "too large index; index: " << tower_index
                 << " (max val " << 0xFFFFFF << ")" << std::endl;
       exit(1);
     }

     return calo_tower_id;
   }

   inline unsigned int decode_index(const unsigned int calo_tower_id)
  {
    return (calo_tower_id) &0xFFFFFF;
  }

  /*! Extract tower index 1 of calorimeter tower from CaloTowerID
   */
  inline unsigned int decode_index1(const unsigned int calo_tower_id)
  {
    return (calo_tower_id >> CaloTriggerTowerDefs::index1_idbits) & 0xFFF;
  }

  /*! Extract tower index 2 of calorimeter tower from CaloTowerID
   */
  inline unsigned int decode_index2(const unsigned int calo_tower_id)
  {
    return calo_tower_id & 0xFFF;
  }

  inline std::string convert_caloid_to_name(const CaloTriggerTowerDefs::CalorimeterId calo_id)
  {
    switch (calo_id)
    {
    case NONE:
      return "NONE";
      break;

    case CEMC:
      return "CEMC";
      break;

    case HCALIN:
      return "HCALIN";
      break;

    case HCALOUT:
      return "HCALOUT";
      break;

    default:
          std::cout
              << "Invalid calorimeter ID passed to RawTowerDefs::convert_caloid_to_name"
              << std::endl;
          exit(1);
    }
  }

  inline CaloTriggerTowerDefs::CalorimeterId convert_name_to_caloid(const std::string &caloname)
 {
   if (caloname == "NONE")
     return NONE;

   else if (caloname == "CEMC")
     return CEMC;

   else if (caloname == "HCALIN")
     return HCALIN;

   else if (caloname == "HCALOUT")
    return HCALOUT;
   else
   {
     std::cout << "Invalid calorimeter name " << caloname
               << " passed to RawTowerDefs::convert_name_to_caloid" << std::endl;
     exit(1);
   }
  }
}

#endif
