// CaloTrigger.cc
// Author: Daniel Lis
// Brief: This is the main module class for the Fun4ALL framework to simulate the sPHENIX Calorimeter Response


#include "CaloTrigger.h"
#include "CaloTriggerSetup.h"
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

int CaloTrigger::process_event(PHCompositeNode */* topNode */) {
  std::cout<<"Initializing Calo Element Maps"<<std::endl;

  if (!InitializeCaloTriggerElements(CEMC)) {
    cout<<"CaloTrigger - EMCAL Trigger Map not initialized... Aborting Run."<<endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }
  if (!InitializeCaloTriggerElements(HCALIN)) {
    cout<<"CaloTrigger - HCALIN Trigger Map not initialized... Aborting Run."<<endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }
  if (!InitializeCaloTriggerElements(HCALOUT)) {
    cout<<"CaloTrigger - HCALOUT Trigger Map not initialized... Aborting Run."<<endl;
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

      cout<<" You have not chosen a detector..."<<endl;
      return 0;
    case CEMC :

      cout<<" Making Map for the EMCAL"<<endl;

      RawTowerContainer *towersRawEM = findNode::getClass<RawTowerContainer>(topNode, "TOWER_RAW_CEMC");
      if (!towersRawEM){
        cout<<"Could not find Node: TOWER_RAW_CEMC..."<<endl;
        return 0;
      }
      RawTowerGeomContainer *geomCEMC = findNode::getClass<RawTowerGeomContainer>(topNode, "TOWERGEOM_CEMC");
      if (!geomCEMC){
        cout<<"Could not find Node: TOWERGEOM_CEMC..."<<endl;
        return 0;
      }

      for (int i = 0; i < EMCALSpecs::n_elements ; i++){
        if (_debug){
          cout<<"Making Element "<< i <<"..."<<endl;
        }
        CaloTriggerElement *calo_trigger_element = new CaloTriggerElement(CEMC);
        for (int j = 0; j < EMCALSpecs::n_calotower_per_element; j++){
          if (_debug){
            cout<<"Making CaloTower "<<j<<endl;
          }
          CaloTriggerTower *calo_trigger_tower = new CaloTriggerTower();

          for (int iphi = 0; iphi < EMCALSpecs::n_phi_tower_per_calo_tower;iphi++){
            const unsigned int iiphi = EMCALSpecs::n_phi_tower_per_calo_tower*i + iphi;
            for (int ieta = 0; ieta < EMCALSpecs::n_eta_tower_per_calo_tower;ieta++){
              const unsigned int iieta = EMCALSpecs::n_eta_tower_per_calo_tower*j+ieta;
              if (_debug){
                cout<<"Adding rawtower "<<ieta<<", "<<iphi<<": "<<iieta<<", "<<iiphi<<endl;
              }
              CaloTriggerTower->AddTower(ieta, iphi, towersRawEM->getTower(iieta, iiphi));
            }
          }

          CaloTriggerElement->AddTower(j, 0, CaloTriggerTower);
        }
        CaloTriggerElementMap->AddTower(0, i, CaloTriggerElement);
      }
      // We have our element map, we need to add in the elements, into those the towers, into those the raw towers.

      break;
    case HCALOUT :
      cout<<" Making Map for the Outer HCAL"<<endl;

      break;
    case HCALIN :
      cout<<" Making Map for the Inner HCAL"<<endl;

      break;
  }
  return 1;
}
