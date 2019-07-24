#include "_DebugConOut.h"
#include "InputState.h"

InputState::InputState()
{
	//new = 0;old = 1;
	for (auto id : INPUT_ID())
	{
		_state.try_emplace(INPUT_ID::LEFT, KeyPair{ 0,1 });
	}
	/*
	_state.try_emplace(INPUT_ID::LEFT, std::make_pair(0, 1));
	_state.try_emplace(INPUT_ID::RIGHT, std::make_pair(0, 1));
	_state.try_emplace(INPUT_ID::AIMING, std::make_pair(0, 1));
	_state.try_emplace(INPUT_ID::DOWN, std::make_pair(0, 1));
	_state.try_emplace(INPUT_ID::BTN_1, std::make_pair(0, 1));
	_state.try_emplace(INPUT_ID::BTN_2, std::make_pair(0, 1));
	_state.try_emplace(INPUT_ID::BTN_3, std::make_pair(0, 1));
	_state.try_emplace(INPUT_ID::BTN_4, std::make_pair(0, 1));
	*/
}


InputState::~InputState()
{
}

const KeyMap& InputState::state(void)const
{
	return _state;
}


const KeyPair InputState::state(INPUT_ID id) const
{
	try
	{
		return _state.at(id);
	}
	catch(...)
	{
		AST();
	}
	return { 0,0 };
}

bool InputState::state(INPUT_ID id, int input)
{
	if (_state.find(id) != _state.end())
	{
		_state[id].first = input;
		return true;
	}
	return false;
}

void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			AST();
			_state.emplace(id, KeyPair{ 0,1 });
		}
	}
}
