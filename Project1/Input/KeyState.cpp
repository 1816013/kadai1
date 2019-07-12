#include <DxLib.h>
#include "KeyState.h"
#include "_DebugConOut.h"

KeyState::KeyState()
{
	// ��̫��
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

	TRACE("����̨��۰�ފJ�n\n");
	FILE* fp;
	fopen_s(&fp, "data/key.dat", "rb");
	if (fp == nullptr)
	{
		TRACE("����̨��۰�ގ��s\n");
		_keyCon = _keyDef;
		// ������ؽ�
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
		TRACE("����̨��۰�ސ���\n");
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));
		fread(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, fp);
		fclose(fp);
	}
	

	func = &KeyState::RefKeyData;		// ���ڽKeyState�����offset�ʂ����Ȃ�
}

KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();
	GetHitKeyStateAll(_buf);
	(this->*func)();
	// vector��ð��ٍ쐬
	// ����̨��
	// F1����������INPUT_ID�̏��ԂŐݒ�
	// F1����������delete��������ؾ��
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
		TRACE("����̨�ފJ�n\n");
		confID = (begin(INPUT_ID()));
		TRACE("�ݒ跰:%d\n", confID);
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
			TRACE("�ݒ跰:%d\n", confID);
			break;
		}
		if(_buf[id] && id == KEY_INPUT_DELETE)
		{
			TRACE("��̫�ĂɕύX\n");
			_keyCon = _keyDef;
			confID = end(INPUT_ID());
			break;
		}
	}

	if (confID >= end(INPUT_ID()))
	{
		TRACE("����̨�ޏI��\n");
		FILE* fp;
		fopen_s(&fp, "data/key.dat", "wb");
		if (fp != nullptr)
		{
			fwrite(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, fp);// (�i�[�ް��̐擪�߲��, ��̑傫��,�@����, �ǂ��ɏ�����)
			fclose(fp);
			TRACE("����̨�޾��ފ���\n");
		}
		else
		{
			TRACE("����̨�޾��ގ��s\n");
		}
		func = &KeyState::RefKeyData;
	}
}
