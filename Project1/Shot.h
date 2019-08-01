#pragma once
#include <unit/Obj.h>


using ShotPair = std::pair<Vector2_D, UNIT >;

class Shot : public Obj
{
public:
	Shot();
	Shot(ShotPair state, Vector2 size);
	~Shot();
	void Update(void) override;
	UNIT GetUnitType(void) override;
	void Draw(void) override;
	bool init(void) override;
	bool HitCheck(std::vector<shared_Obj> list) override;	// “–‚½‚è”»’è
	UNIT GetUType(void);
private:
	UNIT _uType;	// ’e‚ð‘Å‚Á‚½ÕÆ¯Ä‚ÌÀ²Ìß

};
