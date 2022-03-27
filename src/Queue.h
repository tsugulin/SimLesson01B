#ifndef QUEUE_H_
#define QUEUE_H_

#include <omnetpp.h>
using namespace omnetpp;
#include <map>

class Queue : public cSimpleModule
{
  private:
    cQueue queue;
    cLongHistogram waitTime;
    std::map<std::string, long> msgKind;   // 各メッセージの受信数

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* QUEUE_H_ */
