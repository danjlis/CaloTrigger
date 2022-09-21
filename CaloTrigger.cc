// CaloTrigger.cc
// Author: Daniel Lis
// Brief: This is the main module class for the Fun4ALL framework to simulate the sPHENIX Calorimeter Response


#include "CaloTrigger.h"
#include "CaloTriggerSetup.h"
#include "CaloTriggerTower.h"
#include "CaloTriggerElement.h"
#include "CaloTriggerElementDefs.h"

#include <calobase/RawCluster.h>
#include <calobase/RawClusterContainer.h>
#include <calobase/RawTower.h>
#include <calobase/RawTowerContainer.h>
#include <calobase/RawTowerGeom.h>
#include <calobase/RawTowerGeomContainer.h>
#include <calobase/RawClusterUtility.h>

#include <fun4all/Fun4AllReturnCodes.h>

CaloTrigger::CaloTrigger(const std::string &name):
  SubsysReco(name) {
    _debug = true;
  }

CaloTrigger::~CaloTrigger(){

}

int CaloTrigger::Init(PHCompositeNode */* topNode */) {

  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloTrigger::InitRun(PHCompositeNode *topNode) {
  return CreateNode(topNode);
}

int CaloTrigger::process_event(PHCompositeNode *topNode ) {
  GetNodes(topNode);
  _emcal_trigger_element_map = new CaloTriggerElementMap(CaloTriggerElementDefs::CEMC);

  std::cout<<"Initializing Calo Element Maps"<<std::endl;
  
  if (!InitializeCaloTriggerElements(CEMC)) {
    std::cout<<"CaloTrigger - EMCAL Trigger Map not initialized... Aborting Run."<<std::endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }
  if (!InitializeCaloTriggerElements(HCALIN)) {
    std::cout<<"CaloTrigger - HCALIN Trigger Map not initialized... Aborting Run."<<std::endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }
  if (!InitializeCaloTriggerElements(HCALOUT)) {
    std::cout<<"CaloTrigger - HCALOUT Trigger Map not initialized... Aborting Run."<<std::endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }



  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloTrigger::ResetEvent(PHCompositeNode */* topNode */) {
  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloTrigger::EndRun(const int /*runnumber*/) {
  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloTrigger::End(PHCompositeNode */* topNode */) {
  return Fun4AllReturnCodes::EVENT_OK;
}
int CaloTrigger::Reset(PHCompositeNode */* topNode */) {
  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloTrigger::GetNodes(PHCompositeNode *topNode){
  
  _towersRawEM = findNode::getClass<RawTowerContainer>(topNode, "TOWER_RAW_CEMC");
  if (!_towersRawEM){
    std::cout<<"Could not find Node: TOWER_RAW_CEMC..."<<std::endl;
    return 0;
  }


  return 1;
}

int CaloTrigger::CreateNode(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);

  // Looking for the DST node
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode)
    {
      std::cout << PHWHERE << "DST Node missing, doing nothing." << std::endl;
      return Fun4AllReturnCodes::ABORTRUN;
    }

  // store the PFlow elements under a sub-node directory
  PHCompositeNode *caloTrigNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "CALOTRIGGER"));
  if (!caloTrigNode)
    {
      caloTrigNode = new PHCompositeNode("CALOTRIGGER");
      dstNode->addNode( caloTrigNode );
    }

  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloTrigger::InitializeCaloTriggerElements(unsigned int detector)
{

  switch(detector){
    case NONE :

      std::cout<<" You have not chosen a detector..."<<std::endl;
      return 0;
    case CEMC :

      std::cout<<" Making Map for the EMCAL"<<std::endl;

      for (unsigned int i = 0; i < EMCALSpecs::n_caloelements ; i++){
        if (_debug){
          std::cout<<"Making Element "<< i <<"..."<<std::endl;
        }
        CaloTriggerElement *calo_trigger_element = new CaloTriggerElement(CaloTriggerTowerDefs::CEMC);
        for (unsigned int j = 0; j < EMCALSpecs::n_calotower_per_element; j++){
          if (_debug){
            std::cout<<"Making CaloTower "<<j<<std::endl;
          }
          CaloTriggerTower *calo_trigger_tower = new CaloTriggerTower();

          for (unsigned int iphi = 0; iphi < EMCALSpecs::n_phi_tower_per_calotower;iphi++){
            const unsigned int iiphi = EMCALSpecs::n_phi_tower_per_calotower*i + iphi;
            for (unsigned int ieta = 0; ieta < EMCALSpecs::n_eta_tower_per_calotower;ieta++){
              const unsigned int iieta = EMCALSpecs::n_eta_tower_per_calotower*j+ieta;
              if (_debug){
                std::cout<<"Adding rawtower "<<ieta<<", "<<iphi<<": "<<iieta<<", "<<iiphi<<std::endl;
              }
              calo_trigger_tower->AddTower(ieta, iphi, _towersRawEM->getTower(iieta, iiphi));
            }
          }

          calo_trigger_element->AddTower(j, 0, calo_trigger_tower);
        }
        calo_trigger_element->identify();

	_emcal_trigger_element_map->AddTower(0, i, calo_trigger_element);
	
      }
      // We have our element map, we need to add in the elements, into those the towers, into those the raw towers.

      break;
    case HCALOUT :
      std::cout<<" Making Map for the Outer HCAL"<<std::endl;

      break;
    case HCALIN :
      std::cout<<" Making Map for the Inner HCAL"<<std::endl;

      break;
  }
  return 1;
}
