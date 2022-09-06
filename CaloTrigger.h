#ifndef CALOTRIGGER_H
#define CALOTRIGGER_H

// CaloTrigger.h
// Author: Daniel Lis
// Brief: Header file for the CaloTrigger Class:

#include <fun4all/SubsysReco.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHRandomSeed.h>
#include <phool/getClass.h>
#include <string>

class PHCompositeNode;


class CaloTrigger : public SubsysReco
{
public:
    CaloTrigger(const std::string &name = "CaloTrigger");
    ~CaloTrigger() override;

    int Init(PHCompositeNode *topNode) override;
    int InitRun(PHCompositeNode *topNode) override;
    int process_event(PHCompositeNode *topNode) override;
    int ResetEvent(PHCompositeNode *topNode) override;
    int EndRun(const int runnumber) override;
    int End(PHCompositeNode *topNode) override;
    int Reset(PHCompositeNode *topNode) override;

private:
  int CreateNode(PHCompositeNode *topNode);

};

#endif
