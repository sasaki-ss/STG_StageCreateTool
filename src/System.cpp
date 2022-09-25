#include "System.h"

#include <DxLib.h>
#include "Fps.h"

bool System::Init() {
#ifdef _DEBUG
#else
	FreeConsole();							//コンソールを表示しない
	SetOutApplicationLogValidFlag(FALSE);	//ログを出力しない
#endif // _DEBUG

	SetWaitVSyncFlag(FALSE);				//垂直同期待ちをしない
	SetMainWindowText("tool");				//ウィンドウタイトル
	SetWindowStyleMode(0);					//ウィンドウスタイルをデフォルトに
	SetGraphMode(1280, 960, 32);			//画像解像度を変更
	ChangeWindowMode(TRUE);					//ウィンドウモードに変更
	SetDrawMode(DX_DRAWMODE_NEAREST);		//ネアレストネイバー法で描画する
	if (DxLib_Init())return false;			//DXライブラリを初期化
	SetDrawScreen(DX_SCREEN_BACK);			//裏画面処理に変更

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