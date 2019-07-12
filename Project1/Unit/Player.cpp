#include <DxLib.h>
#include <memory>
#include "Player.h"
#include "common/ImageMng.h"
#include "_DebugConOut.h"
#include "_DebugDispOut.h"



Player::Player()
{
	init();
	_inputState = std::make_unique<KeyState>();
	_alive = true;
}

Player::Player(Vector2 vec, Vector2 size)
{
	//animKey(ANIM::NOMAL);
	init();
	_inputState = std::make_unique<KeyState>();
	_pos = vec;
	_size = size;
	_alive = true;
	//TRACE("vec.x %d\n", vec.x);
}

Player::~Player()
{
}

void Player::Update(void)
{
	/*if (DestroyProc())
	{
		return;
	}
	if (rand() % 600 == 0)
	{
		_alive = false;
		animKey(ANIM::DEATH);
	}*/


	_inputState->Update();
	if (_inputState->state(INPUT_ID::LEFT).first)
	{
		_pos.x--;
	}
	if (_inputState->state(INPUT_ID::RIGHT).first)
	{
		_pos.x++;
	}
	if (_inputState->state(INPUT_ID::UP).first)
	{
		_pos.y--;
	}
	if (_inputState->state(INPUT_ID::DOWN).first)
	{
		_pos.y++;
	}
	_TdbgDrawFormatString(0, 0, 0xffffff, "plauyerPos: x %d, y%d", _pos.x, _pos.y);
	_dbgDrawBox(_pos.x - _size.x / 2, _pos.y - _size.y / 2, _pos.x + _size.x / 2, _pos.y + _size.y / 2, 0x00ff00, true);
}

void Player::Draw(void)
{
	//DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("ｷｬﾗ" /*,"image/char.png",Vector2(10, 10), Vector2(30, 32)*/)[0], true);
	
}



UNIT Player::GetUnitType(void)
{
	return UNIT::PLAYER;
}

bool Player::init(void)
{
	AnimVector data;
	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("player")[0], 30));
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[1], 60);

	SetAnim(ANIM::NOMAL, data);

	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("player")[0], 30));
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[2], 60);
	SetAnim(ANIM::EX, data);

	data.reserve(5);
	data.emplace_back(IMAGE_ID("自機爆発")[0], 5);
	data.emplace_back(IMAGE_ID("自機爆発")[1], 15);
	data.emplace_back(IMAGE_ID("自機爆発")[2], 25);
	data.emplace_back(IMAGE_ID("自機爆発")[3], 35);
	data.emplace_back(-1, 45);
	SetAnim(ANIM::DEATH, data);
	return true;
}
