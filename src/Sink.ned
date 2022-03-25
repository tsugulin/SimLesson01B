simple Sink		// シンプルモジュール名をSinkとする
{
    parameters:
        volatile double serviceTime @unit(s) = default(0);		// パラメータとしてserviceTimeを定義し，単位は秒，初期値はゼロとする
    gates:
        input in;		// 入口としてinを定義する
        output out;		// 出口としてoutを定義する
}