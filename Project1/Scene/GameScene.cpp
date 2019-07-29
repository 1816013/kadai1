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
	Vector2_D _pos[6] = 
	{
		{ (double)0 - 16,(double)0  - 16},
		{ (double)0 - 16, (double)lpSceneMng.gameScreenSize.y / 2 - 16},
		{ (double)0 - 16, (double)lpSceneMng.gameScreenSize.y - 48},
		{ (double)lpSceneMng.gameScreenSize.x + 16, (double)0 - 16},
		{ (double)lpSceneMng.gameScreenSize.x + 16,(double)lpSceneMng.gameScreenSize.y / 2 - 16},
		{ (double)lpSceneMng.gameScreenSize.x + 16, (double)lpSceneMng.gameScreenSize.y - 48}
	};
	Vector2_D aim[42];
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			aim[y * 7 + x] = {(double) 32 + (x * 32), (double)32 + (y * 32) };
		}
	}

	Vector2_D sigAim[2];
	Vector2_D sigAim2[2];
	sigAim[1] = {(double)300, (double)lpSceneMng.gameScreenSize.y / 2 - 16 };
	sigAim[0] = {(double)200, (double)lpSceneMng.gameScreenSize.y / 2 - 16 };
	sigAim2[1] = { (double)100, (double)lpSceneMng.gameScreenSize.y - 48 };
	sigAim2[0] = { (double)400, (double)lpSceneMng.gameScreenSize.y - 48 };

	_lastKey = _newKey;
	_newKey = CheckHitKey(KEY_INPUT_R);
	if (_newKey && !_lastKey)
	{
		
		int no = rand() % 6;
		for (int i = 0; i < 3; i++)
		{
			// ��������֐��\��
			E_TYPE randType = static_cast<E_TYPE>(rand() % static_cast<int>(E_TYPE::MAX));
			if (randType == E_TYPE::BOSS)
			{
				if (_bossAim.size() < 4)
				{
					_bossAim.emplace_back(Vector2_D(32 * _bossAim.size() + lpSceneMng.gameScreenSize.x / 2 - 48, 32));
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
				}
			}
			// �����܂Ŋ֐��\��
			if (no < 3)
			{
				eMoveCon.emplace_back(sigAim[0], E_MOVE_TYPE::WAIT);
				eMoveCon.emplace_back(sigAim[0], E_MOVE_TYPE::SIGMOID);
				eMoveCon.emplace_back(sigAim2[0], E_MOVE_TYPE::SIGMOID);
				eMoveCon.emplace_back(sigAim2[0], E_MOVE_TYPE::SWIRL);
			}
			else
			{
				eMoveCon.emplace_back(sigAim[0], E_MOVE_TYPE::WAIT);
				eMoveCon.emplace_back(sigAim[1], E_MOVE_TYPE::SIGMOID);
				eMoveCon.emplace_back(sigAim2[1], E_MOVE_TYPE::SIGMOID);
				eMoveCon.emplace_back(sigAim2[1], E_MOVE_TYPE::SWIRL);
			}

			_dbgDrawFormatString(0, 15, 0xffffff, "randType%d", randType);
			if (randType == E_TYPE::BOSS)
			{
				eMoveCon.emplace_back(_bossAim[_bossAim.size() - 1], E_MOVE_TYPE::AIMING);
			}
			if (randType == E_TYPE::GOEI)
			{
				eMoveCon.emplace_back(_goeiAim[_goeiAim.size() - 1], E_MOVE_TYPE::AIMING);
			}
			if (randType == E_TYPE::ZAKO)
			{
				eMoveCon.emplace_back(_zakoAim[_zakoAim.size() - 1], E_MOVE_TYPE::AIMING);
			}

			EnemyInstance({ _pos[no], Vector2(30, 32),randType, move(eMoveCon), i * 15 });
		}
	}
	

	Vector2_D pPos;
 	for (auto& itr : _objList)		// �͈�for��shared_ptr���g���Ƃł���unique_ptr�ł�auto&���g���΂ł���
	{
		itr->Update();
		if (itr->GetUnitType() == UNIT::PLAYER)
		{
			pPos = itr->pos();
		}
	}
	_objList.erase(std::remove_if(
				   _objList.begin(),
				   _objList.end(),
					[](shared_Obj& obj) { return (*obj).isDeath(); }), 
				   _objList.end());

	size_t s_count = std::count_if(_objList.begin(), _objList.end(),
		[](shared_Obj& obj)->bool {return ((*obj).GetUnitType() == UNIT::SHOT); }
	);
	size_t p_count = std::count_if(_objList.begin(), _objList.end(),
		[](shared_Obj& obj)->bool {return ((*obj).GetUnitType() == UNIT::PLAYER); }
	);


	pPos.y -= 16;
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (s_count < 2 * p_count)
		{
			_objList.emplace_back(new Shot(pPos, Vector2(3, 8), UNIT::PLAYER));
		}
	}
	Draw();

	return std::move(own);
}

SCN_ID GameScene::GetSceneID(void)
{
	return SCN_ID::GAME;
}

void GameScene::EnemyInstance(ENEMY_T state)
{
	_objList.emplace_back(new Enemy(state));	// 0�Ԗ�
	_cnt++;
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
	_objList.emplace_back(new Player(Vector2_D(200, 300), Vector2(30, 32)));
	
	srand(time(NULL));
	return true;
}

void GameScene::Draw(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_ghGameScreen);	
	ClsDrawScreen(); //��ʏ���

	//for (auto itr = _objList.begin();	// unique_ptr���Ƃ�����x�ׂ�����
	//	itr != _objList.end();
	//	itr++)
	//{
	//	(*itr)->Draw;
	//}
	for (auto& itr : _objList)		// �͈�for��shared_ptr���g���Ƃł���unique_ptr�ł�auto&���g���΂ł���
	{
		//itr->Draw();
		itr->Obj::Draw();
	}
	lpSceneMng.addDrawQue({ _ghGameScreen, lpSceneMng.gameScreenPos.x, lpSceneMng.gameScreenPos.y });
	SetDrawScreen(ghBefor);
}
