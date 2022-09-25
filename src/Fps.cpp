#include "Fps.h"

#include <thread>
#include <DxLib.h>

using namespace std::chrono;
using namespace std::this_thread;

const int						Fps::SAMPLE_NUM{ 10 };

/*�R���X�g���N�^*/
Fps::Fps() :
	cnt(0), index(0), fps(0.0f), isDispFps(false),
	startTime(), fpsSample(), waitTimeList() {

}

/*�f�X�g���N�^*/
Fps::~Fps() {
	fpsSample.clear();
	waitTimeList.clear();
}

/*����������*/
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

/*�X�V����*/
void Fps::update() {
	//1�t���[���ڂɎ��Ԃ��擾�A����ȊO��cnt�����Z
	if (cnt == 60) {
		//FPS��\������ꍇ�̏���
		if (isDispFps) {
			//1�b�Ԃ̏������Ԃ����߂�
			system_clock::time_point nowTime = system_clock::now();
			milliseconds procTime = duration_cast<milliseconds>(nowTime - startTime);

			//���݂�FPS�����߂�
			float nowFps = floor(procTime.count() / 16.66f * 10) / 10;
			fpsSample[index] = nowFps;

			//�T���v���̕���FPS�����߂�
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

/*�ҋ@����*/
void Fps::wait() {
	//���݂̎��Ԃ��I�������֊i�[���A�ҋ@���Ԃ��v�Z����
	system_clock::time_point endTime = system_clock::now();
	milliseconds procTime = duration_cast<milliseconds>(endTime - startTime);
	milliseconds waitTime = waitTimeList[cnt - 1] - procTime;

	//�ҋ@���K�v�ȏꍇ�ҋ@������
	if (waitTime < waitTimeList[cnt - 1]) {
		sleep_for(waitTime);
	}
}
