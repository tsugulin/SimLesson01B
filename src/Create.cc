#include "Create.h"
Define_Module(Create);

void Create::initialize()
{
    mode = par("mode").stringValue();               // 分岐方法
    max = par("forkNumber").intValue();             // 分岐数をロード
    for (int i = 0; i < max; i++)  nxt[i] = 0;      // 次の分岐先を初期化
    WATCH_MAP(nxt);                                 // 次の分岐先を監視
    scheduleAt(simTime() + par("intervalTime"), new cMessage("beat"));   // 平均値10分のポアソン分布に基づき，患者を発生させるメッセージを自身に向けて発信
}

void Create::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {           // 患者が到着した場合、待合室に案内する
        int j = intuniform(0, max-1);       // 乱数にて分岐先を決定
        if (mode == "minimum")              // もし分岐方法が最小値方式ならば分岐先を変更
            j = (nxt[0] <= nxt[1]) ? 0: 1;  // 待ち行列が少ない方を選択
        send(new cMessage("patient"), "out", j);    // 患者を表すメッセージを待ち行列に向けて発信
        nxt[j]++;                           // 待ち行列の長さを更新
        showGUI(nxt[0], nxt[1]);            // GUI表示
        scheduleAt(simTime() + par("intervalTime"), msg);   // 次の患者を発生させるメッセージを自身に向けて発信
    } else {                                // 待合室から待ち状況が届いた場合
        int n = (strcmp(msg->getArrivalGate()->getFullName(), "in[0]") == 0) ? 0: 1;   // 待合室のインデックス。0または1
        int m = msg->getKind();             // 待ち行列の長さ
        nxt[n] = m;                         // 待ち行列の長さを更新
        showGUI(nxt[0], nxt[1]);            // GUI表示
        delete msg;     // 待合室から届いたメッセージを削除
    }
}

void Create::showGUI(int a1, int a2)
{
    std::string str = "Room0:" + std::to_string(a1) + " ,Room1:" + std::to_string(a2);  // 表示する文字列を生成
    getDisplayString().setTagArg("t", 0, str.c_str());                                  // GUIに表示
}
