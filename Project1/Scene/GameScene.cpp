#include <DxLib.h>
#include <algorithm>
#include <time.h>
#include "GameScene.h"
#include "SceneMng.h"
#include <Unit/Player.h>
#include <Unit/Enemy.h>
#include "Shot.h"
#include "_DebugConOut.h"
#include "_DebugDispOut.h"
#include <Input/KeyState.h>
#include <common/ImageMng.h>

//#include <Input/InputState.h>
//#include <Input/KeyState.h>

GameScene::GameScene()
{
	Init();
	_popCnt = 0;
	_inputState = std::make_unique<KeyState>();
	_col = std::make_unique<Collision>();
	_arrivalCnt = 0;
}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	_col->Update(_objList);
	_inputState->Update();
	Vector2_D _pos[6] = 
	{
		{ (double)0 - 16,(double)0  - 16},
		{ (double)0 - 16, (double)lpSceneMng.gameScreenSize.y / 2 - 16},
		{ (double)0 - 16, (double)lpSceneMng.gameScreenSize.y - 48},
		{ (double)lpSceneMng.gameScreenSize.x + 16, (double)0 - 16},
		{ (double)lpSceneMng.gameScreenSize.x + 16,(double)lpSceneMng.gameScreenSize.y / 2 - 16},
		{ (double)lpSceneMng.gameScreenSize.x + 16, (double)lpSceneMng.gameScreenSize.y - 48}
	};

	Vector2_D sigAim[2];	// ｼｸﾞﾓｲﾄﾞの目標座標
	Vector2_D sigAim2[2];
	sigAim[1] = { (double)300, (double)lpSceneMng.gameScreenSize.y / 2 - 16 };
	sigAim[0] = { (double)200, (double)lpSceneMng.gameScreenSize.y / 2 - 16 };
	sigAim2[1] = { (double)100, (double)lpSceneMng.gameScreenSize.y - 48 };
	sigAim2[0] = { (double)400, (double)lpSceneMng.gameScreenSize.y - 48 };

	/*Vector2_D aim[42];
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			aim[y * 7 + x] = {(double) 32 + (x * 32), (double)32 + (y * 32) };
		}
	}*/


	auto a = _bossAim.size() + _goeiAim.size() + _zakoAim.size();
	_lastKey = _newKey;
	_newKey = CheckHitKey(KEY_INPUT_R);
	if (_newKey && !_lastKey || _popCnt % 120 == 0 && a < 40)
	{
		int no = rand() % 6;
		for (int i = 0; i < 5; i++)
		{
			E_TYPE randType = static_cast<E_TYPE>(rand() % static_cast<int>(E_TYPE::MAX));

			if (no < 3)
			{
				eMoveCon.emplace_back(_pos[no], E_MOVE_TYPE::WAIT);
				eMoveCon.emplace_back(sigAim[0], E_MOVE_TYPE::SIGMOID);
				eMoveCon.emplace_back(sigAim2[0], E_MOVE_TYPE::SIGMOID);
				eMoveCon.emplace_back(sigAim2[0], E_MOVE_TYPE::SWIRL);
			}
			else
			{
				eMoveCon.emplace_back(_pos[no], E_MOVE_TYPE::WAIT);
				eMoveCon.emplace_back(sigAim[1], E_MOVE_TYPE::SIGMOID);
				eMoveCon.emplace_back(sigAim2[1], E_MOVE_TYPE::SIGMOID);
				eMoveCon.emplace_back(sigAim2[1], E_MOVE_TYPE::SWIRL);
			}			
			if (randType == E_TYPE::BOSS)
			{
				if (_bossAim.size() < 4)
				{
					_bossAim.emplace_back(Vector2_D(32 * _bossAim.size() + lpSceneMng.gameScreenSize.x / 2 - 48, 32));
					eMoveCon.emplace_back(_bossAim[_bossAim.size() - 1], E_MOVE_TYPE::AIMING);
				}
				else
				{
					randType = E_TYPE::GOEI;
				}
			}
			if (randType == E_TYPE::GOEI)
			{
				if (_goeiAim.size() < 16)
				{
					_goeiAim.emplace_back(Vector2_D(32 * (int)(_goeiAim.size() % 8) + lpSceneMng.gameScreenSize.x / 2 - 112, 64 + 32 * (int)(_goeiAim.size() / 8)));
					eMoveCon.emplace_back(_goeiAim[_goeiAim.size() - 1], E_MOVE_TYPE::AIMING);
				}
				else
				{
					randType = E_TYPE::ZAKO;
				}
			}
			if (randType == E_TYPE::ZAKO)
			{
				if (_zakoAim.size() < 20)
				{
					_zakoAim.emplace_back(Vector2_D(32 * (int)(_zakoAim.size() % 10) + lpSceneMng.gameScreenSize.x / 2 - 144, 128 + 32 * (int)(_zakoAim.size() / 10)));
					eMoveCon.emplace_back(_zakoAim[_zakoAim.size() - 1], E_MOVE_TYPE::AIMING);
				}
			}

			eMoveCon.emplace_back(Vector2_D( lpSceneMng.gameScreenSize.x / 2 , 32), E_MOVE_TYPE::ZOOM);

			EnemyInstance({ _pos[no], Vector2(30, 32),randType, move(eMoveCon), i * 8 });
		}
	}
	
	if(a >= 40)
	{
		_arrivalCnt++;
	}
	_popCnt++;


	/*int arrivalCnt = std::count_if(_objList.begin(), _objList.end(),
		[](shared_Obj& obj)->bool {return ((*obj).isArrival() == true); }
	);*/
	for (auto& itr : _objList)		// 範囲for文shared_ptrを使うとできるunique_ptrでもauto&を使えばできる
	{
		if (_arrivalCnt >= 270)
		{
			itr->AllArrivalF(true);
		}
	}

	size_t plS_count = std::count_if(_objList.begin(), _objList.end(),
		[](shared_Obj& obj)->bool {return ((*obj).GetUnitType() == UNIT::P_SHOT); }
	);

 	for (auto& itr : _objList)
	{
		itr->Update();
		if (itr->isShot())
		{
			if (itr->GetUnitType() == UNIT::PLAYER && plS_count < 2)
			{
				_shotList.emplace_back(itr->pos(), itr->GetUnitType());
			}
			if (itr->GetUnitType() == UNIT::ENEMY)
			{
				_shotList.emplace_back(itr->pos(), itr->GetUnitType());
			}
		}
	}
	
	/*size_t p_count = std::count_if(_objList.begin(), _objList.end(),
		[](shared_Obj& obj)->bool {return ((*obj).GetUnitType() == UNIT::PLAYER); }
	);*/
	
	if (_shotList.size() > 0)
	{
		for (auto itr : _shotList)
		{
			_objList.emplace_back(new Shot(itr, Vector2(3, 8)));
		}
		std::sort(_objList.begin(),
			_objList.end(),
			[](shared_Obj& obj, shared_Obj& obj2) { return (*obj).GetUnitType() < (*obj2).GetUnitType(); });
		_shotList.erase(_shotList.begin(), _shotList.end());
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
	_objList.emplace_back(new Enemy(state));	
	/*for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			_objList.emplace_back(new Enemy(Vector2(30 + (x * 30), 30 + (y * 32)), Vector2(30, 32)));
		}
	}*/
}

void GameScene::DrawChar(std::string str, Vector2 pos)
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
			DrawGraph(pos.x + 16 * Drawpos, pos.y, IMAGE_ID("文字")[drawID], true);
		}
		Drawpos++;
	}
}

bool GameScene::Init(void)
{
	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
	_objList.emplace_back(new Player(Vector2_D(lpSceneMng.gameScreenSize.x / 2 - 16, lpSceneMng.gameScreenSize.y - 16), Vector2(30, 32)));
	


	srand(time(NULL));
	return true;
}

void GameScene::Draw(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_ghGameScreen);	
	ClsDrawScreen(); //画面消去
	//DrawChar("HELLO", {50, 200});
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
