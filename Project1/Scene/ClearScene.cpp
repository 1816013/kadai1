#include <DxLib.h>
#include "ClearScene.h"
#include <Scene/GameScene.h>
#include <common/ImageMng.h>
#include <Scene/SceneMng.h>



ClearScene::ClearScene()
{
	_scnID = SCN_ID::CLEAR;
	_ghClearScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}


ClearScene::~ClearScene()
{
}

unique_Base ClearScene::Update(unique_Base own)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		_scnID = SCN_ID::TITLE;
	}
	Draw();
	return std::move(own);
}

void ClearScene::Draw(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_ghClearScreen);
	ClsDrawScreen(); //âÊñ è¡ãé
	DrawChar("GAME CLEAR", { 160, 100 });
	DrawChar("PUSH SPACE BUTTON", { 110, 300 });
	lpSceneMng.addDrawQue({ _ghClearScreen, lpSceneMng.gameScreenPos.x, lpSceneMng.gameScreenPos.y });
	SetDrawScreen(ghBefor);

}

SCN_ID ClearScene::GetSceneID(void)
{
	return SCN_ID::CLEAR;
}

SCN_ID ClearScene::NextSceneID(void)
{
	return _scnID;
}

void ClearScene::DrawChar(std::string str, Vector2 pos)
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