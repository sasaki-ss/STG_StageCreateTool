#ifndef TOOL_SYSTEM_H
#define TOOL_SYSTEM_H

class System final {
public:
	bool Init();	//初期化処理
	void Final();	//終了処理
	void Run();		//実行処理
};

#endif // !TOOL_SYSTEM_H