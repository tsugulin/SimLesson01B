network Simulation01	// モデル名をSimulation01とする
{
    @display("bgb=459,318");	// 枠の大きさは横459ピクセル，縦318ピクセルとする
    submodules:					// モジュールの定義
        enter: Create {			// Createモジュールを継承してenterノードを定義とする
            parameters:
                @display("p=74,88;i=block/source");		// 座標(74,88)にimages/block/source.pngを表示する
        }
        wait[2]: Queue {			// Queueモジュールを継承してwaitノードを２つ定義する
            parameters:
                @display("p=215,88,c,100;i=block/queue;q=queue");	// 座標(215,88)にimages/block/queue.pngを表示する。ノードにqueueの値を表示する
        }
        doctor[2]: Sink {			// Sinkモジュールを継承してdoctorノードを２つ定義する
            parameters:
                @display("p=348,88,c,100;i=block/sink");	// 座標(348,88)にimages/block/sink.pngを表示する
        }
    connections:						// モジュール間の接続の定義
        enter.out++ --> wait[0].in++;	// enterをwait0に接続する
        enter.out++ --> wait[1].in++;	// enterをwaitに接続する
        wait[0].out --> doctor[0].in;	// wait0をdoctor0に接続する
        wait[1].out --> doctor[1].in;	// wait1をdoctor1に接続する
        doctor[0].out --> wait[0].in++;	// doctor0をwait0に接続する
        doctor[1].out --> wait[1].in++;	// doctor1をwait1に接続する
}
