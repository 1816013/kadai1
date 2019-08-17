#include <DxLib.h>
#include "GameoverScene.h"
#include <Scene/GameScene.h>
#include <common/ImageMng.h>
#include <Scene/SceneMng.h>



GameoverScene::GameoverScene()
{
	_scnID = SCN_ID::GAMEOVER;
	_ghGameoverScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}


GameoverScene::~GameoverScene()
{
}


unique_Base GameoverScene::Update(unique_Base own)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		_scnID = SCN_ID::TITLE;
	}
	Draw();
	return std::move(own);
}

void GameoverScene::Draw(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_ghGameoverScreen);
	ClsDrawScreen(); //âÊñ è¡ãé
	DrawChar("GAME OVER", { 160, 100 });
	DrawChar("PUSH SPACE BUTTON", { 110, 300 });
	lpSceneMng.addDrawQue({ _ghGameoverScreen, lpSceneMng.gameScreenPos.x, lpSceneMng.gameScreenPos.y });
	SetDrawScreen(ghBefor);

}

SCN_ID GameoverScene::GetSceneID(void)
{
	return SCN_ID::GAMEOVER;
}

SCN_ID GameoverScene::NextSceneID(void)
{
	return _scnID;
}

void GameoverScene::DrawChar(std::string str, Vector2 pos)
{
	int drawID;
	int Drawpos = 0;
	for (auto charCode : str)
	{
		if (charCode < 'A' || charCode > 'Z')
		{
			switch (charCode)
			{
			case'-':
				drawID = 26;
				break;
			case'%':
				drawID = 27;
				break;
			case'.':
				drawID = 28;
				break;
			case'!':
				drawID = 29;
				break;
			default:
				drawID = -1;
				break;
			}
		}
		else
		{
			drawID = charCode - 'A';
		}
		if (drawID != -1)
		{
			DrawGraph(pos.x + 16 * Drawpos, pos.y, IMAGE_ID("ï∂éö")[drawID], true);
		}
		Drawpos++;
	}
}