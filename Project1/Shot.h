#pragma once
#include <unit/Obj.h>

class Shot : public Obj
{
public:
	Shot();
	Shot(Vector2_D pos, Vector2 size, UNIT type);
	~Shot();
	void Update(void) override;
	UNIT GetUnitType(void) override;
	void Draw(void) override;
	bool init(void) override;
	void HitCheck(std::vector<shared_Obj> list) override;	// �����蔻��
	UNIT GetUType(void);
private:
	UNIT _uType;	// �e��ł����ƯĂ�����

};
