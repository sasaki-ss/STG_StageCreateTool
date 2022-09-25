#ifndef STG_FPS_H
#define STG_FPS_H

#include <chrono>
#include <vector>

//FPS����N���X
//FPS�̐���֘A�̏������s���܂��B
class Fps final {
private:
	static const int						SAMPLE_NUM;		//�T���v���̐�

	int										cnt;			//�t���[���J�E���^
	int										index;			//sample�i�[�p��index
	float									fps;			//�P�b�Ԃ̃t���[����(����)
	bool									isDispFps;		//FPS��\���t���O
	std::chrono::system_clock::time_point	startTime;		//�J�n����
	std::vector<float>						fpsSample;		//FPS�T���v����
	std::vector<std::chrono::milliseconds>	waitTimeList;	//�ҋ@���Ԃ̃��X�g�f�[�^
public:
	Fps();			//�R���X�g���N�^
	~Fps();			//�f�X�g���N�^
	void init();	//����������
	void update();	//�X�V����
	void wait();	//�ҋ@����

	/*accessor*/
	void setIsDispFps(bool _val) { isDispFps = _val; }
	float getFps() { return fps; }
};

#endif // !STG_FPS_H
