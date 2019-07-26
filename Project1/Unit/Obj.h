#pragma once
#include <vector>
#include <memory>
#include <map>
#include <common/VECTOR2.h>

enum class ANIM
{
	NOMAL,		// �ʏ�
	NOMAL2,
	NOMAL3,
	EX,			// ����
	DEATH,		// ����
	MAX
};

enum class UNIT
{
	PLAYER,
	ENEMY,
	SHOT,
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
	const ANIM animKey(void) const;		// _animKey�̎擾
	bool animKey(const ANIM key);		// _animKey�̐ݒ�
	const Vector2_D pos(void) const;		// ��޼ު�Ă̍��W�擾
	bool isAlive(void) { return _alive; };	// ���q�֐�(����ި���)
	void setAlive(bool alive);				// �����Ă��邩�擾
	bool isDeath(void) { return _death; };	// ���q�֐�(����ި���)
private:
	std::map<ANIM, AnimVector> _animMap;
	ANIM _animKey;						// ��Ұ��݂̖��O
	int _animFrame;						// ��Ұ��݂̌��݂̺�
	bool _animEnd;
protected:
	int _animCnt;						// ��Ұ��̶݂���
	bool SetAnim(const ANIM key, AnimVector& data);	// ��Ұ��݂̾��
	bool isAnimEnd(void);
	bool DestroyProc(void);
	Vector2_D _pos;						// ��ׂ̍��W
	Vector2 _size;						// ��ׂ̻���
	bool _alive;						// �����Ă��邩
	bool _death;
	float _angle;

};

