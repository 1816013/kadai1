#pragma once
#include <vector>
#include <memory>
#include <map>
#include <common/VECTOR2.h>

enum class ANIM
{
	NOMAL,		// �ʏ�
	EX,			// ����
	DEATH,		// ����
	MAX
};

enum class UNIT
{
	PLAYER,
	P_SHOT,
	ENEMY,
	E_SHOT,
	MAX
};

class Obj;
using unique_Obj = std::unique_ptr<Obj>;	
using shared_Obj = std::shared_ptr<Obj>;

using AnimVector = std::vector<std::pair<int, int>>;	//�@��ڂ̈���������ٓ�ڂ̈����Ͷ���
				 //std::vector<std::vector<int>>
				 //std::vector<std::array<2,int>>
class Obj
{
public:
	Obj();								// �ݽ�׸�
	virtual ~Obj();						// �޽�׸�
	virtual void Draw(void);			// ��Ұ��݊Ǘ��̕`��
	void Draw(int id);					// �ð�ސ��̕`��
	virtual void Update(void) = 0;		// ��޼ު�Ă̑���s��
	virtual UNIT GetUnitType(void) = 0;	// ��ׂ̎�ނ̎擾
	virtual bool init(void) = 0;		// ��Ұ��݂̏����������ݒ�
	virtual bool HitCheck(std::vector<shared_Obj> list) = 0; // �����蔻��
	const ANIM animKey(void) const;		// _animKey�̎擾
	bool animKey(const ANIM key);		// _animKey�̐ݒ�
	const Vector2_D pos(void) const;	// ��޼ު�Ă̍��W�擾
	const Vector2 size(void) const;		// ��޼ު�Ă̑傫���擾
	void SetAlive(bool flag);			// �����Ă��邩�̐ݒ�
	bool isAlive(void) { return _alive; };	// ���q�֐�(����ި���)���ꂽ��
	bool isDeath(void) { return _death; };	// ���q�֐�(����ި���)����ł邩
	bool isShot(void) { return _shotF; };	// ���q�֐�(����ި���)�����Ă��邩
	void SetColF(bool flag);
	bool isColF(void) { return _colF; };
	int submitLife(void) { return _life -= 1; };

	// ��
	bool AllArrivalF(bool flag);		// �S�������������̾��
	

private:
	std::map<ANIM, AnimVector> _animMap;
	ANIM _animKey;						// ��Ұ��݂̖��O
protected:
	int _animCnt;						// ��Ұ��̶݂���
	int _animFrame;						// ��Ұ��݂̌��݂̺�
	bool SetAnim(const ANIM key, AnimVector& data);	// ��Ұ��݂̾��
	bool isAnimEnd(void);				// ��Ұ��݂̏I��
	bool DestroyProc(void);				// ���ꂽ���Ƃ̐���
	Vector2_D _pos;						// ��ׂ̍��W
	Vector2 _size;						// ��ׂ̻���
	Vector2_D _speed;					// ��ׂ̑��x
	bool _alive;						// �����Ă��邩
	bool _death;						// ����ł��邩
	float _angle;						// �p�x
	int _life;							// HP
	bool _shotF;						// ���Č����Ă��邩
	bool _colF;							// �Փ�
	
	// ��
	bool _AllArrivalF;					// �S������������(��а�̂�)
};

