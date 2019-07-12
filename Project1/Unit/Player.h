#pragma once
#include "Obj.h"
#include <memory>
#include <Input/KeyState.h>

class Player :
	public Obj
{
public:
	Player();							// ºİ½Ä×¸À
	Player(Vector2 vec, Vector2 size);	// ˆø”•t‚«ºİ½Ä×¸À
	~Player();							// ÃŞ½Ä×¸À
	void Update(void);					// ÌßÚ²Ô°‚ÌˆÚ“®ˆ—ŠÖ”
	void Draw(void) override;			// ÌßÚ²Ô°•`‰æ
	UNIT GetUnitType(void) override;	// ‚¨‘O‚ÍÌßÚ²Ô°‚©H
private:
	bool init(void) override;			// •`‰æÃŞ°À‚Ì‰Šú‰»‚È‚Ç
	std::unique_ptr<InputState> _inputState;
};