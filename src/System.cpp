#include "System.h"

#include <DxLib.h>
#include "Fps.h"

bool System::Init() {
#ifdef _DEBUG
#else
	FreeConsole();							//�R���\�[����\�����Ȃ�
	SetOutApplicationLogValidFlag(FALSE);	//���O���o�͂��Ȃ�
#endif // _DEBUG

	SetWaitVSyncFlag(FALSE);				//���������҂������Ȃ�
	SetMainWindowText("tool");				//�E�B���h�E�^�C�g��
	SetWindowStyleMode(0);					//�E�B���h�E�X�^�C�����f�t�H���g��
	SetGraphMode(1280, 960, 32);			//�摜�𑜓x��ύX
	ChangeWindowMode(TRUE);					//�E�B���h�E���[�h�ɕύX
	SetDrawMode(DX_DRAWMODE_NEAREST);		//�l�A���X�g�l�C�o�[�@�ŕ`�悷��
	if (DxLib_Init())return false;			//DX���C�u������������
	SetDrawScreen(DX_SCREEN_BACK);			//����ʏ����ɕύX

	return true;
}

void System::Final() {
	DxLib_End();
}

void System::Run() {
	Fps fps;

	fps.init();

	while (!ProcessMessage()) {
		ClearDrawScreen();

		fps.update();

		//DrawBox(0, 32, 768, 928,GetColor(255,255,255),TRUE);
		for (int i = 0; i <= 12; i++)DrawLine(i * 64, 32, i * 64, 928, GetColor(255, 0, 0));
		for (int i = 0; i <= 15; i++)DrawLine(0, i * 64 - 32, 768, i * 64 - 32, GetColor(255, 0, 0));

		ScreenFlip();
		fps.wait();
	}
}