#pragma once
#include "Obj.h"
#include <memory>
#include <Input/KeyState.h>

class Player :
	public Obj
{
public:
	Player();							// �ݽ�׸�
	Player(const Vector2_D& vec, const Vector2& size);	// �����t���ݽ�׸�
	~Player();							// �޽�׸�
	void Update(void);					// ��ڲ԰�̈ړ������֐�
	void Draw(void) override;			// ��ڲ԰�`��
	UNIT GetUnitType(void) override;	// ���O����ڲ԰���H
	bool HitCheck(std::vector<shared_Obj> list)override;	// �����蔻��
	
private:
	bool init(void) override;			// �`���ް��̏������Ȃ�
	std::unique_ptr<InputState> _inputState;	
	int _remain;						// �c�@
};