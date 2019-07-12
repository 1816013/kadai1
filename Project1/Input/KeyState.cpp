#include <DxLib.h>
#include "KeyState.h"
#include "_DebugConOut.h"

KeyState::KeyState()
{
	// ﾃﾞﾌｫﾙﾄ
	_keyDef.reserve(static_cast<size_t>(end(INPUT_ID())));
	// emplace_back
	_keyDef.emplace_back(KEY_INPUT_LEFT);
	_keyDef.emplace_back(KEY_INPUT_RIGHT);
	_keyDef.emplace_back(KEY_INPUT_UP);
	_keyDef.emplace_back(KEY_INPUT_DOWN);
	_keyDef.emplace_back(KEY_INPUT_Z);
	_keyDef.emplace_back(KEY_INPUT_X);
	_keyDef.emplace_back(KEY_INPUT_A);
	_keyDef.emplace_back(KEY_INPUT_S);

	TRACE("ｷｰｺﾝﾌｨｸﾞﾛｰﾄﾞ開始\n");
	FILE* fp;
	fopen_s(&fp, "data/key.dat", "rb");
	if (fp == nullptr)
	{
		TRACE("ｷｰｺﾝﾌｨｸﾞﾛｰﾄﾞ失敗\n");
		_keyCon = _keyDef;
		// 初期化ﾘｽﾄ
		/*_keyCon =
		{
			KEY_INPUT_LEFT,
			KEY_INPUT_RIGHT,
			KEY_INPUT_UP,
			KEY_INPUT_DOWN,
			KEY_INPUT_Z,
			KEY_INPUT_X,
			KEY_INPUT_A,
			KEY_INPUT_S
		};*/

	}
	else
	{
		TRACE("ｷｰｺﾝﾌｨｸﾞﾛｰﾄﾞ成功\n");
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));
		fread(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, fp);
		fclose(fp);
	}
	

	func = &KeyState::RefKeyData;		// ｱﾄﾞﾚｽKeyStateからのoffset量しかない
}

KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();
	GetHitKeyStateAll(_buf);
	(this->*func)();
	// vectorでﾃｰﾌﾞﾙ作成
	// ｷｰｺﾝﾌｨｸﾞ
	// F1を押した後INPUT_IDの順番で設定
	// F1を押した後deleteを押すとﾘｾｯﾄ
}

void KeyState::RefKeyData(void)
{
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_keyCon[static_cast<int>(id)]]);
	}
	if (_buf[KEY_INPUT_F1])
	{
		func = &KeyState::SetKeyConfig;
		TRACE("ｷｰｺﾝﾌｨｸﾞ開始\n");
		confID = (begin(INPUT_ID()));
		TRACE("設定ｷｰ:%d\n", confID);
	}
	/*state(INPUT_ID::LEFT, _buf[KEY_INPUT_LEFT]);
	state(INPUT_ID::RIGHT, _buf[KEY_INPUT_RIGHT]);
	state(INPUT_ID::UP, _buf[KEY_INPUT_UP]);
	state(INPUT_ID::DOWN, _buf[KEY_INPUT_DOWN]);
	state(INPUT_ID::BTN_1, _buf[KEY_INPUT_Z]);
	state(INPUT_ID::BTN_2 , _buf[KEY_INPUT_X]);
	state(INPUT_ID::BTN_3, _buf[KEY_INPUT_A]);
	state(INPUT_ID::BTN_4, _buf[KEY_INPUT_S]);*/
}

void KeyState::SetKeyConfig(void)
{
	for (auto id : INPUT_ID())
	{
		state(id, 0);
	}
	for (auto id = 0; id < sizeof(_buf) / sizeof(_buf[0]); id++)
	{
		if (_buf[id] && _lastKeyID != id && id != KEY_INPUT_F1 && id != KEY_INPUT_DELETE)
		{
			_keyCon[static_cast<int>(confID)] = id;
			_lastKeyID = id;
			++confID;
			TRACE("設定ｷｰ:%d\n", confID);
			break;
		}
		if(_buf[id] && id == KEY_INPUT_DELETE)
		{
			TRACE("ﾃﾞﾌｫﾙﾄに変更\n");
			_keyCon = _keyDef;
			confID = end(INPUT_ID());
			break;
		}
	}

	if (confID >= end(INPUT_ID()))
	{
		TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
		FILE* fp;
		fopen_s(&fp, "data/key.dat", "wb");
		if (fp != nullptr)
		{
			fwrite(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, fp);// (格納ﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ, 一つの大きさ,　何回, どこに書くか)
			fclose(fp);
			TRACE("ｷｰｺﾝﾌｨｸﾞｾｰﾌﾞ完了\n");
		}
		else
		{
			TRACE("ｷｰｺﾝﾌｨｸﾞｾｰﾌﾞ失敗\n");
		}
		func = &KeyState::RefKeyData;
	}
}
