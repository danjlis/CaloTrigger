// File: CaloTriggerElementMap.h
// Author: Daniel Lis
// Brief: Header for the a single CaloTrigger ElementMap (All Trigger Areas)

#ifndef CALOTRIGGERELEMENTDEFS_H
#define CALOTRIGGERELEMENTDEFS_H

namespace CaloTriggerElementDefs{

  typedef unsigned int keytype;

  static unsigned int calo_idbits = 8;
  static unsigned int element_idbits = sizeof(keytype) * 8 - calo_idbits;
  static unsigned int index1_idbits = element_idbits / 2;

  enum CalorimeterId
  {
    NONE = 0,
    CEMC = 1,
    HCALOUT = 2,
    HCALIN = 3
  };

  inline CaloTriggerElementDefs::keytype encode_elementid(const CalorimeterId calo_id, const unsigned int element_index_1,
                const unsigned int element_index_2)
 {
   CaloTriggerElementDefs::keytype calo_element_id = 0;

   if (element_index_1 < 0xFFF && element_index_2 < 0xFFF)
   {
     calo_element_id = (calo_id << CaloTriggerElementDefs::element_idbits) + (element_index_1 << CaloTriggerElementDefs::index1_idbits) + element_index_2;
   }
   else
   {
     std::cout << "too large index1 and/or index2; index1: "
               << element_index_1 << " (max val " << 0xFFF << ")"
               << ", index2: "
               << element_index_2 << " (max val " << 0xFFF << ")" << std::endl;
     exit(1);
   }

   return calo_element_id;
 }

 inline CaloTriggerElementDefs::keytype encode_elementid(const CalorimeterId calo_id, const unsigned int element_index)
   {
     CaloTriggerElementDefs::keytype calo_element_id = 0;

     if (element_index < 0xFFFFFF)
     {
       calo_element_id = (calo_id << CaloTriggerElementDefs::element_idbits) + element_index;
     }
     else
     {
       std::cout << "too large index; index: " << element_index
                 << " (max val " << 0xFFFFFF << ")" << std::endl;
       exit(1);
     }

     return calo_element_id;
   }

   inline unsigned int decode_index(const unsigned int calo_element_id)
  {
    return (calo_element_id) &0xFFFFFF;
  }

  /*! Extract element index 1 of calorimeter element from CaloelementID
   */
  inline unsigned int decode_index1(const unsigned int calo_element_id)
  {
    return (calo_element_id >> CaloTriggerElementDefs::index1_idbits) & 0xFFF;
  }

  /*! Extract element index 2 of calorimeter element from CaloelementID
   */
  inline unsigned int decode_index2(const unsigned int calo_element_id)
  {
    return calo_element_id & 0xFFF;
  }

  inline std::string convert_caloid_to_name(const CaloTriggerElementDefs::CalorimeterId calo_id)
  {
    switch (calo_id)
    {
    case NONE:
      return "NONE";
      break;

    case DRCALO:
      return "DRCALO";
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
              << "Invalid calorimeter ID passed to RawElementDefs::convert_caloid_to_name"
              << std::endl;
          exit(1);
    }
  }

  inline CaloTriggerElementDefs::CalorimeterId convert_name_to_caloid(const std::string &caloname)
 {
   if (caloname == "NONE")
     return NONE;

   else if (caloname == "CEMC")
     return CEMC;

   else if (caloname == "DRCALO")
     return DRCALO;

   else if (caloname == "HCALIN")
     return HCALIN;

   else if (caloname == "HCALOUT")
    return HCALOUT;
   else
   {
     std::cout << "Invalid calorimeter name " << caloname
               << " passed to RawElementDefs::convert_name_to_caloid" << std::endl;
     exit(1);
   }
  }
}

#endif
