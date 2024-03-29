#pragma once

enum class INPUT_ID
{
	LEFT,	// ©
	RIGHT,	// ¨
	UP,		// ª
	DOWN,	// «
	BTN_1,	// z
	BTN_2,	// x
	BTN_3,	// a
	BTN_4,	// s
	MAX
};

INPUT_ID begin(INPUT_ID);	// INPUT_IDÌÅÌvf
INPUT_ID end(INPUT_ID);		// INPUT_IDÌÅãÌvf
INPUT_ID operator*(INPUT_ID key);	
INPUT_ID operator++(INPUT_ID& key);