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

  }

CaloTrigger::~CaloTrigger(){

}

int CaloTrigger::Init(PHCompositeNode */* topNode */) {
  if (!InitializeCaloTriggerElements(,_emcal_trigger_element_map)) {
    cout<<"CaloTrigger - EMCAL Trigger Map not initialized... Aborting Run."<<endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }
  if (!InitializeCaloTriggerElements(_hcalin_trigger_element_map)) {
    cout<<"CaloTrigger - HCALIN Trigger Map not initialized... Aborting Run."<<endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }
  if (!InitializeCaloTriggerElements(_hcalout_trigger_element_map)) {
    cout<<"CaloTrigger - HCALOUT Trigger Map not initialized... Aborting Run."<<endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }
  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloTrigger::InitRun(PHCompositeNode *topNode) {
  return CreateNode(topNode);
}

int CaloTrigger::process_event(PHCompositeNode */* topNode */) {
  std::cout<<"I am here..."<<std::endl;
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
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"\
));
  if (!dstNode)
    {
      std::cout << PHWHERE << "DST Node missing, doing nothing." << std::endl;
      return Fun4AllReturnCodes::ABORTRUN;
    }

  // store the PFlow elements under a sub-node directory
  PHCompositeNode *caloTrigNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "PA\
RTICLEFLOW"));
  if (!caloTrigNode)
    {
      caloTrigNode = new PHCompositeNode("CALOTRIGGER");
      dstNode->addNode( caloTrigNode );
    }

  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloTrigger::InitializeCaloTriggerElements(unsigned int detector, CaloTriggerElementMap *calo_trigger_element_map)
{


  switch(detector){
    case NONE :

      cout<<" You have not chosen a detector..."<<endl;
      return 0;
    case CEMC :
      cout<<" Making Map for the EMCAL"<<endl;

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
