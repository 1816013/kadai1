#pragma once
#include "BaseScene.h"
#include <string>
#include <common/VECTOR2.h>
class GameoverScene :
	public BaseScene
{
public:
	GameoverScene();
	~GameoverScene();
	unique_Base Update(unique_Base own) override;	// Še±¯ÌßÃŞ°Ä‚ğ‚Ü‚Æ‚ß‚é
	void Draw(void);								// À²ÄÙ½¸Ø°İ‚Å‚Ì•`‰æ
	SCN_ID GetSceneID(void);						// ¡‚Ì¼°İ‚ğæ“¾
	SCN_ID NextSceneID(void);						// Ÿ‚Ì¼°İ‚ğæ“¾
private:
	void DrawChar(std::string str, Vector2 pos);	// •¶š—ñ‚Ì•`‰æ—p
	int _ghGameoverScreen;			// ¹Ş°Ñµ°ÊŞ°—p½¸Ø°İ
};

