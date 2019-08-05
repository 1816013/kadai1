#pragma once
#include <memory>

enum class SCN_ID	
{
	GAME,	// ¹Ş°Ñ’†‚Ì¼°İ
	MAX
};

class BaseScene;	// ‚±‚¤‘‚©‚È‚¢‚Æ¸×½‚ğusing‚Åg‚¦‚È‚¢
using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene() {};
	virtual unique_Base Update(unique_Base own) = 0;
	virtual SCN_ID GetSceneID(void) = 0;
};

