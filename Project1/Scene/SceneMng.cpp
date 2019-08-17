#include <DxLib.h>
#include <main.h>
#include <common/VECTOR2.h>
#include <common/ImageMng.h>
#include "SceneMng.h"
#include <Scene/GameScene.h>
#include <Scene/TitleScene.h>
#include <Scene/GameoverScene.h>
#include <Scene/ClearScene.h>
#include "_DebugConOut.h"
#include "_DebugDispOut.h"

std::unique_ptr<SceneMng, SceneMng::SceneDeleter> SceneMng::s_Instance(new SceneMng);

void SceneMng::Run(void)
{
	SysInit();
	ImageMng::GetInstance().GetID("’e", "image/shot.png", Vector2(2, 1), Vector2(3, 8));
	ImageMng::GetInstance().GetID("·¬×", "image/char.png", Vector2(10, 10), Vector2(30, 32));
	ImageMng::GetInstance().GetID("“G”š”­", "image/en_blast.png", Vector2(5, 1), Vector2(64, 64));
	ImageMng::GetInstance().GetID("©‹@”š”­", "image/pl_blast.png", Vector2(4, 1), Vector2(64, 64));
	ImageMng::GetInstance().GetID("•¶š", "image/text.png", Vector2(30, 1), Vector2(16, 16));


	_activeScene = std::make_unique<TitleScene>();
	// ----------¹Ş°ÑÙ°Ìß
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_drawList.clear(); // •`‰æØ½Ä‚Ì‰Šú‰»
		// ¼°İŠÇ—
		_nowScnID = _activeScene->GetSceneID();
		_nextScnID = _activeScene->NextSceneID();
		if (_nextScnID == SCN_ID::TITLE && _nowScnID != SCN_ID::TITLE)
		{
			_activeScene = std::make_unique<TitleScene>();
		}
		if (_nextScnID == SCN_ID::GAME && _nowScnID != SCN_ID::GAME)
		{
			_activeScene = std::make_unique<GameScene>();
		}
		if (_nextScnID == SCN_ID::GAMEOVER && _nowScnID != SCN_ID::GAMEOVER)
		{
			_activeScene = std::make_unique<GameoverScene>();
		}
		if (_nextScnID == SCN_ID::CLEAR && _nowScnID != SCN_ID::CLEAR)
		{
			_activeScene = std::make_unique<ClearScene>();
		}
		_activeScene = _activeScene->Update(std::move(_activeScene));
		addDrawQue({ IMAGE_ID("˜g")[0], 0, 0 });
		Draw();
		_dbgStartDrawDebug();
		frame++;
	}
	
	DxLib_End();

}

bool SceneMng::addDrawQue(DrawQueT dQue)
{
	//image‚ª“Ç‚Ü‚ê‚Ä‚¢‚é‚©‚Ìƒ`ƒFƒbƒN
	if (std::get<static_cast<int> (DRAW_QUE::IMAGE)>(dQue) == -1)
	{
		return false;
	}
	_drawList.emplace_back(dQue);
	return true;
}

SceneMng::SceneMng() : screenSize{ 800, 600 }, gameScreenSize{ 500, 390 }, gameScreenPos{ 150, 105 }
{
	
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	// ----------¼½ÃÑˆ—
	SetWindowText("ƒMƒƒƒ‰ƒK");
	// ¼½ÃÑˆ—
	SetGraphMode(screenSize.x, screenSize.y, 16);	// 800~600ƒhƒbƒg65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);							// true:window false:ÌÙ½¸Ø°İ
	if (DxLib_Init() == -1)
	{
		return false;				//DX×²ÌŞ×Ø‰Šú‰»ˆ—
	}
	// TRACE("DXLIB‰Šú‰»Š®—¹\n");
	
	SET_IMAGE_ID("˜g", "image/frame.png");
	_dbgSetUp(200);
#ifdef DEBUG
	_DebugConOut::GetInstance();
#endif // DEBUG
	


	return true;
}

void SceneMng::Draw(void)
{
	_dbgAddDrawDebug();
	SetDrawScreen(DX_SCREEN_BACK);					//‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ
	ClsDrawScreen(); //‰æ–ÊÁ‹
	// ¸Ş×Ì¨¯¸ÊİÄŞÙ‚ÆÀ•W‚ª•K—v
	
	for (auto _dQue : _drawList)
	{
		DrawGraph(std::get<static_cast<int> (DRAW_QUE::X)>(_dQue),
				  std::get<static_cast<int> (DRAW_QUE::Y)>(_dQue), 
				  std::get<static_cast<int> (DRAW_QUE::IMAGE)>(_dQue),
				  true);
	}
	//DrawBox(150, 495, 650, 527, 0x000000, true);
	ScreenFlip();	//— ‰æ–Ê‚ğ•\‰æ–Ê‚ÉuŠÔºËß°
}

int SceneMng::Frame(void)
{
	return frame;
}
