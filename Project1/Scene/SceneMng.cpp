#include <DxLib.h>
#include <main.h>
#include <common/VECTOR2.h>
#include <common/ImageMng.h>
#include "SceneMng.h"
#include <Scene/GameScene.h>
#include "_DebugConOut.h"
#include "_DebugDispOut.h"

std::unique_ptr<SceneMng, SceneMng::SceneDeleter> SceneMng::s_Instance(new SceneMng);

void SceneMng::Run(void)
{
	SysInit();

	ImageMng::GetInstance().GetID("ｷｬﾗ", "image/char.png", Vector2(10, 10), Vector2(30, 32));
	ImageMng::GetInstance().GetID("敵爆発", "image/en_blast.png", Vector2(5, 1), Vector2(64, 64));
	ImageMng::GetInstance().GetID("自機爆発", "image/pl_blast.png", Vector2(4, 1), Vector2(64, 64));

	_activeScene = std::make_unique<GameScene>();
	// ----------ｹﾞｰﾑﾙｰﾌﾟ
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_drawList.clear(); // 描画ﾘｽﾄの初期化
		// ｼｰﾝ管理
		_activeScene = _activeScene->Update(std::move(_activeScene));
		addDrawQue({ IMAGE_ID("枠")[0], 0, 0 });
		Draw();
		_dbgStartDrawDebug();
	}
	
	DxLib_End();

}

bool SceneMng::addDrawQue(DrawQueT dQue)
{
	//imageが読まれているかのチェック
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
	// ----------ｼｽﾃﾑ処理
	SetWindowText("ギャラガ");
	// ｼｽﾃﾑ処理
	SetGraphMode(screenSize.x, screenSize.y, 16);	// 800×600ドット65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);							// true:window false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)
	{
		return false;				//DXﾗｲﾌﾞﾗﾘ初期化処理
	}
	// TRACE("DXLIB初期化完了\n");
	
	SET_IMAGE_ID("枠", "image/frame.png");
	_dbgSetUp(200);
#ifdef DEBUG
	_DebugConOut::GetInstance();
#endif // DEBUG
	


	return true;
}

void SceneMng::Draw(void)
{
	_dbgAddDrawDebug();
	SetDrawScreen(DX_SCREEN_BACK);					//ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
	ClsDrawScreen(); //画面消去
	// ｸﾞﾗﾌｨｯｸﾊﾝﾄﾞﾙと座標が必要
	for (auto _dQue : _drawList)
	{
		DrawGraph(std::get<static_cast<int> (DRAW_QUE::X)>(_dQue),
				  std::get<static_cast<int> (DRAW_QUE::Y)>(_dQue), 
				  std::get<static_cast<int> (DRAW_QUE::IMAGE)>(_dQue),
				  true);
	}
	
	ScreenFlip();	//裏画面を表画面に瞬間ｺﾋﾟｰ
}
