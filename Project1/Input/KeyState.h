#pragma once
#include <vector>
#include "InputState.h"
class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;		// �����ޯ̧�ɓo�^
private:
	void RefKeyData(void);			// ���͂��ꂽ���𔽉f�AF1���������緰��̨�ނ�
	void SetKeyConfig(void);		// ����̨��
	char _buf[256];					// ���ޯ̧
	std::vector<int> _keyCon;		// ���̔z�u	
	std::vector<int> _keyDef;		// ��̫�Ă̷��z�u
	void(KeyState::*func)(void);	// �֐��߲��
	INPUT_ID confID;				// ����̨�ޗp����
	int _lastKeyID;					// ����̨�ޗp��O�̓��ͷ����
};

