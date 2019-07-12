#pragma once
#include <vector>
#include "InputState.h"
class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;		// ｷｰをﾊﾞｯﾌｧに登録
private:
	void RefKeyData(void);			// 入力されたｷｰを反映、F1を押したらｷｰｺﾝﾌｨｸﾞへ
	void SetKeyConfig(void);		// ｷｰｺﾝﾌｨｸﾞ
	char _buf[256];					// ｷｰﾊﾞｯﾌｧ
	std::vector<int> _keyCon;		// ｷｰの配置	
	std::vector<int> _keyDef;		// ﾃﾞﾌｫﾙﾄのｷｰ配置
	void(KeyState::*func)(void);	// 関数ﾎﾟｲﾝﾀ
	INPUT_ID confID;				// ｷｰｺﾝﾌｨｸﾞ用ｶｳﾝﾀ
	int _lastKeyID;					// ｷｰｺﾝﾌｨｸﾞ用一つ前の入力ｷｰ情報
};

