#include "Queue.h"
Define_Module(Queue);

void Queue::initialize()
{
   queue.setName("queue");      // 待ち行列に名前をつける
   WATCH_MAP(msgKind);          // 変数の監視
}

void Queue::handleMessage(cMessage *msg)
{
    msgKind[(std::string)msg->getName()]++;  // メッセージの数をカウント
    if (strcmp(msg->getName(), "patient") == 0) {       // 患者が到着した場合
        msg->setTimestamp(simTime());   // リードタイムの開始時間をセット
        queue.insert(msg);              // 待ち行列にメッセージを保管
        send(new cMessage("request"), "out");   // リクエストを医師へ
    } else if (strcmp(msg->getName(), "call") == 0) {   // 医師からの呼び出しがあった場合
        if (queue.getLength() > 0) {       // もし患者が待っていれば
            cMessage *patient = check_and_cast<cMessage *>(queue.pop());    // 待ち行列からメッセージを取り出す
            waitTime.collect(simTime() - patient->getTimestamp());          // 待ち時間をカウント
            send(patient, "out");           // 患者をドクターへ
        }
        delete msg;     // 呼び出しメッセージを削除
    }
}

//　ノードの統計情報を表示
void Queue::finish()
{
    EV << "Queue Jobs Count:    " << waitTime.getCount() << endl;
    EV << "Queue Min Leadtime:  " << waitTime.getMin() << endl;
    EV << "Queue Mean Leadtime: " << waitTime.getMean() << endl;
    EV << "Queue Max Leadtime:  " << waitTime.getMax() << endl;
    EV << "Standard deviation:  " << waitTime.getStddev() << endl;

    waitTime.recordAs("queue length");
}
