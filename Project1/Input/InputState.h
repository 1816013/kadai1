#pragma once
#include <map>
#include "INPUT_ID.h"

using KeyPair = std::pair<int, int>;		// ����(int, int) �� (now, old)
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual void Update(void) = 0;
	virtual ~InputState();

	const KeyMap& state(void)const;				// state�擾
	const KeyPair state(INPUT_ID id)const;		// KeyPair�̒��g�̎擾
	bool state(INPUT_ID id, int input);			// �����ް��̾��
	void SetOld(void);							// 1�ڰёO�̓����ް��̾��


private:
	KeyMap _state;

};

