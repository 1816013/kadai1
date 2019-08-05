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


Player::Player(const Vector2_D& vec, const Vector2& size)
{
	//animKey(ANIM::NOMAL);
	init();
	_inputState = std::make_unique<KeyState>();
	_pos = vec;
	_size = size;
	_alive = true;
	_speed = { 4,4 };
	//TRACE("vec.x %d\n", vec.x);
}

Player::~Player()
{
}

void Player::Update(void)
{
	if (!_alive)
	{
		animKey(ANIM::DEATH);
	}
	if (DestroyProc())
	{
		return;
	}
	if (_inputState->state(INPUT_ID::BTN_1).first && !_inputState->state(INPUT_ID::BTN_1).second)
	{
		_shotF = true;
	}
	else
	{
		_shotF = false;
	}

	_inputState->Update();
	if (_inputState->state(INPUT_ID::LEFT).first)
	{
		_pos.x -= _speed.x;
	}
	if (_inputState->state(INPUT_ID::RIGHT).first)
	{
		_pos.x += _speed.x;
	}
	if (_inputState->state(INPUT_ID::UP).first)
	{
		_pos.y--;
	}
	if (_inputState->state(INPUT_ID::DOWN).first)
	{
		_pos.y++;
	}
	_dbgDrawFormatString(0, 0, 0xffffff, "plauyerPos: x %f, y%f", _pos.x, _pos.y);
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
bool Player::HitCheck(std::vector<shared_Obj> list)
{
	return false;
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
