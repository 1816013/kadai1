#include <DxLib.h>
#include "TitleScene.h"
#include <Scene/GameScene.h>
#include <common/ImageMng.h>
#include <Scene/SceneMng.h>



TitleScene::TitleScene()
{
	_scnID = SCN_ID::TITLE;
	_ghTitleScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		_scnID = SCN_ID::GAME;
	}
	Draw();
	return std::move(own);
}

void TitleScene::Draw(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_ghTitleScreen);
	ClsDrawScreen(); //âÊñ è¡ãé
	DrawChar("PUSH SPACE BUTTON", { 110, 300 });
	lpSceneMng.addDrawQue({ _ghTitleScreen, lpSceneMng.gameScreenPos.x, lpSceneMng.gameScreenPos.y });
	SetDrawScreen(ghBefor);
	
}

SCN_ID TitleScene::GetSceneID(void)
{
	return SCN_ID::TITLE;
}

SCN_ID TitleScene::NextSceneID(void)
{
	return _scnID;
}

void TitleScene::DrawChar(std::string str, Vector2 pos)
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
