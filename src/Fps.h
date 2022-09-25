#ifndef STG_FPS_H
#define STG_FPS_H

#include <chrono>
#include <vector>

//FPS制御クラス
//FPSの制御関連の処理を行います。
class Fps final {
private:
	static const int						SAMPLE_NUM;		//サンプルの数

	int										cnt;			//フレームカウンタ
	int										index;			//sample格納用のindex
	float									fps;			//１秒間のフレーム数(平均)
	bool									isDispFps;		//FPSを表示フラグ
	std::chrono::system_clock::time_point	startTime;		//開始時刻
	std::vector<float>						fpsSample;		//FPSサンプル数
	std::vector<std::chrono::milliseconds>	waitTimeList;	//待機時間のリストデータ
public:
	Fps();			//コンストラクタ
	~Fps();			//デストラクタ
	void init();	//初期化処理
	void update();	//更新処理
	void wait();	//待機処理

	/*accessor*/
	void setIsDispFps(bool _val) { isDispFps = _val; }
	float getFps() { return fps; }
};

#endif // !STG_FPS_H
