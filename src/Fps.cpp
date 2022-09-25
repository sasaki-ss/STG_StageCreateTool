#include "Fps.h"

#include <thread>
#include <DxLib.h>

using namespace std::chrono;
using namespace std::this_thread;

const int						Fps::SAMPLE_NUM{ 10 };

/*コンストラクタ*/
Fps::Fps() :
	cnt(0), index(0), fps(0.0f), isDispFps(false),
	startTime(), fpsSample(), waitTimeList() {

}

/*デストラクタ*/
Fps::~Fps() {
	fpsSample.clear();
	waitTimeList.clear();
}

/*初期化処理*/
void Fps::init() {
	cnt = 0;
	index = 0;
	fps = 0.0f;
	isDispFps = false;
	startTime = system_clock::now();
	fpsSample.reserve(SAMPLE_NUM);
	waitTimeList.reserve(60);
	for (int i = 0; i < SAMPLE_NUM; i++)fpsSample.emplace_back(60.0f);
	for (int i = 1; i <= 60; i++)waitTimeList.emplace_back(static_cast<int>(i * 16.66f));
}

/*更新処理*/
void Fps::update() {
	//1フレーム目に時間を取得、それ以外はcntを加算
	if (cnt == 60) {
		//FPSを表示する場合の処理
		if (isDispFps) {
			//1秒間の処理時間を求める
			system_clock::time_point nowTime = system_clock::now();
			milliseconds procTime = duration_cast<milliseconds>(nowTime - startTime);

			//現在のFPSを求める
			float nowFps = floor(procTime.count() / 16.66f * 10) / 10;
			fpsSample[index] = nowFps;

			//サンプルの平均FPSを求める
			float sum = 0.0f;
			for (float sample : fpsSample) {
				sum += sample;
			}
			fps = sum / SAMPLE_NUM;

			if (index == SAMPLE_NUM - 1) {
				index = 0;
			}
			else {
				index++;
			}
		}

		cnt = 1;
		startTime = system_clock::now();
	}
	else {
		cnt++;
	}
}

/*待機処理*/
void Fps::wait() {
	//現在の時間を終了時刻へ格納し、待機時間を計算する
	system_clock::time_point endTime = system_clock::now();
	milliseconds procTime = duration_cast<milliseconds>(endTime - startTime);
	milliseconds waitTime = waitTimeList[cnt - 1] - procTime;

	//待機が必要な場合待機をする
	if (waitTime < waitTimeList[cnt - 1]) {
		sleep_for(waitTime);
	}
}
