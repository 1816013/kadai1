#pragma once
#include <unit/Obj.h>


using ShotPair = std::pair<Vector2_D, UNIT >;

class Shot : public Obj
{
public:
	Shot();
	Shot(ShotPair state, Vector2 size);
	~Shot();
	void Update(void) override;				// ¼®¯ÄˆÚ“®
	UNIT GetUnitType(void) override;		// ‰½‚Ì¼®¯Ä‚©
	void Draw(void) override;				// •`‰æ
	bool init(void) override;				// ‰Šú‰»
	bool HitCheck(std::vector<shared_Obj> list) override;	// “–‚½‚è”»’è
	UNIT GetUType(void);					// ’e‚ğ‘Å‚Á‚½ÕÆ¯Ä‚ÌÀ²Ìß‚Í‰½‚©
private:
	UNIT _uType;	// ’e‚ğ‘Å‚Á‚½ÕÆ¯Ä‚ÌÀ²Ìß

};
