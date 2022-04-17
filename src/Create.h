#ifndef CREATE_H_
#define CREATE_H_

#include <omnetpp.h>
using namespace omnetpp;
#include <map>

class Create : public cSimpleModule {
protected:
    std::string mode;   // 分岐方法
    int max;            // 次ノード分岐数
    std::map<long, long> nxt;   // 各ノードの待ち行列の長さ
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void showGUI(int, int);
};

#endif /* CREATE_H_ */
