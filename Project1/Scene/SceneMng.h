#pragma once
#include <memory>
#include <vector>
#include <Scene/BaseScene.h>
#include <common/VECTOR2.h>

#define lpSceneMng SceneMng::GetInstance()

using DrawQueT = std::tuple<int, int, int>;	// ¸Ş×Ì¨¯¸ÊİÄŞÙ, xÀ•W, yÀ•W

enum class DRAW_QUE
{
	IMAGE,	// ÊİÄŞÙ
	X,		// XÀ•W
	Y		// YÀ•W
};


class SceneMng
{
public:
	static SceneMng &GetInstance(void)	
	{
		return (*s_Instance);
	}
	void Run(void);	// ‰Šúİ’è

	bool addDrawQue(DrawQueT dQue);		// •`‰æ—p‚Ì·­°‚Éî•ñ‚ğ‘}“ü‚·‚é

	const Vector2 screenSize;		// ³²İÄŞ³‚Ì»²½Ş(800, 600)
	const Vector2 gameScreenSize;	// ¹Ş°Ñ½¸Ø°İ‚Ì»²½Ş(500, 390)
	const Vector2 gameScreenPos;	// ¹Ş°Ñ½¸Ø°İ‚Ì¶ã‚Ìpos

	int Frame(void);				// ±ÆÒ°¼®İ—pÌÚ°Ñ‚ğ“n‚·
private:
	struct SceneDeleter							// ÃŞØ°À°
	{
		void operator()(SceneMng* sceneMng)
		{
			delete sceneMng;
		}
	};
	SceneMng();
	~SceneMng();

	bool SysInit(void);	// ¼½ÃÑ‰Šú‰»(Å‰‚Ì‚İ‰Šú‰»‚·‚é‚à‚Ì)
	void Draw(void);	// •`‰æ‚Ì·­°‚ğ‚à‚Æ‚É•`‰æ‚µ‚Ä‚¢‚­
	std::vector <DrawQueT> _drawList;	// •`‰æ‚Ì·­°

	// •Ï”
	static std::unique_ptr<SceneMng, SceneDeleter> s_Instance;		
	unique_Base _activeScene;		// Œ»İ‚Ì¼°İ
	int frame = 0;		// ±ÆÒ°¼®İ—pÌÚ°Ñ


};

