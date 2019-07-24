#pragma once

enum class INPUT_ID
{
	LEFT,	// Å©
	RIGHT,	// Å®
	AIMING,		// Å™
	DOWN,	// Å´
	BTN_1,	// z
	BTN_2,	// x
	BTN_3,	// a
	BTN_4,	// s
	MAX
};

INPUT_ID begin(INPUT_ID);	// INPUT_IDÇÃç≈èâÇÃóvëf
INPUT_ID end(INPUT_ID);		// INPUT_IDÇÃç≈å„ÇÃóvëf
INPUT_ID operator*(INPUT_ID key);	
INPUT_ID operator++(INPUT_ID& key);