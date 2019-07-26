#pragma once
#include <unit/Obj.h>
class Shot : public Obj
{
public:
	Shot();
	Shot(Vector2_D pos, Vector2 size, UNIT type);
	~Shot();
	void Update(void);
	UNIT GetUnitType(void);
	void Draw(void);
	bool init(void);
private:
	UNIT _uType;

};
