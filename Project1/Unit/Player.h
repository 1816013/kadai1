#pragma once
#include "Obj.h"
#include <memory>
#include <Input/KeyState.h>

class Player :
	public Obj
{
public:
	Player();							// �ݽ�׸�
	Player(Vector2 vec, Vector2 size);	// �����t���ݽ�׸�
	~Player();							// �޽�׸�
	void Update(void);					// ��ڲ԰�̈ړ������֐�
	void Draw(void) override;			// ��ڲ԰�`��
	UNIT GetUnitType(void) override;	// ���O����ڲ԰���H
private:
	bool init(void) override;			// �`���ް��̏������Ȃ�
	std::unique_ptr<InputState> _inputState;
};