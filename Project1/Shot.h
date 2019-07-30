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
	void HitCheck(std::vector<shared_Obj> list) override;	// “–‚½‚è”»’è
	UNIT GetUType(void);
private:
	UNIT _uType;	// ’e‚ð‘Å‚Á‚½ÕÆ¯Ä‚ÌÀ²Ìß

};
