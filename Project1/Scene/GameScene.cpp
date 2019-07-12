#include <DxLib.h>
#include <algorithm>
#include <time.h>
#include "GameScene.h"
#include "SceneMng.h"
#include <Unit/Player.h>
#include <Unit/Enemy.h>
#include "_DebugConOut.h"


//#include <Input/InputState.h>
//#include <Input/KeyState.h>

GameScene::GameScene()
{
	Init();
	_cnt = 0;
}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	Vector2 _pos[6] = 
	{
		{ 0 - 16, 0  - 16},
		{ 0 - 16, 179},
		{ 0 - 16, 390 + 16},
		{ 500 + 16, 0 - 16},
		{ 500 + 16, 179},
		{ 500 + 16, 390 + 16}
	};
	Vector2 _aim = { 250, 195 };
	/*int KeyData[10] = {
		KEY_INPUT_NUMPAD0,
		KEY_INPUT_NUMPAD1,
		KEY_INPUT_NUMPAD2,
		KEY_INPUT_NUMPAD3,
		KEY_INPUT_NUMPAD4,
		KEY_INPUT_NUMPAD5,
		KEY_INPUT_NUMPAD6,
		KEY_INPUT_NUMPAD7,
		KEY_INPUT_NUMPAD8,
		KEY_INPUT_NUMPAD9
	};*/
	//newKey[i] & ~oldKey[i];
	_lastKey = _newKey;
	_newKey = CheckHitKey(KEY_INPUT_R);
	if (_newKey && !_lastKey)
	{
		EnemyInstance({_pos[_cnt], Vector2(30, 32),static_cast<E_TYPE>(rand() % static_cast<int>(E_TYPE::MAX)), _aim });
		/*_objList.emplace_back(new Enemy(Vector2(30 + (50 * (_cnt % 7)), 32 + (50 * (_cnt / 7))), Vector2(30, 32)));*/
		_cnt++;
		if (_cnt > 6)
		{
			_cnt = 0;
		}
	}



	for (auto& itr : _objList)		// 範囲for文shared_ptrを使うとできるunique_ptrでもauto&を使えばできる
	{
		itr->Update();
	}
	_objList.erase(std::remove_if(
				   _objList.begin(),
				   _objList.end(),
					[](shared_Obj& obj) { return (*obj).isDeath(); }), 
				   _objList.end());

	Draw();

	return std::move(own);
}

SCN_ID GameScene::GetSceneID(void)
{
	return SCN_ID::GAME;
}

void GameScene::EnemyInstance(ENEMY_T state)
{
	_objList.emplace_back(new Enemy(state));	// 0番目
	/*for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			_objList.emplace_back(new Enemy(Vector2(30 + (x * 30), 30 + (y * 32)), Vector2(30, 32)));
		}
	}*/
}

bool GameScene::Init(void)
{
	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
	_objList.emplace_back(new Player(Vector2(200, 300), Vector2(30, 32)));
	srand(time(NULL));
	return true;
}

void GameScene::Draw(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_ghGameScreen);	
	ClsDrawScreen(); //画面消去

	//for (auto itr = _objList.begin();	// unique_ptrだとある程度べた書き
	//	itr != _objList.end();
	//	itr++)
	//{
	//	(*itr)->Draw;
	//}
	for (auto& itr : _objList)		// 範囲for文shared_ptrを使うとできるunique_ptrでもauto&を使えばできる
	{
		//itr->Draw();
		itr->Obj::Draw();
	}
	lpSceneMng.addDrawQue({ _ghGameScreen, lpSceneMng.gameScreenPos.x, lpSceneMng.gameScreenPos.y });
	SetDrawScreen(ghBefor);
}
