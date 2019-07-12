#pragma once
#include <map>
#include "INPUT_ID.h"

using KeyPair = std::pair<int, int>;		// ’†‚Ì(int, int) ‚Í (now, old)
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual void Update(void) = 0;
	virtual ~InputState();

	const KeyMap& state(void)const;				// stateæ“¾
	const KeyPair state(INPUT_ID id)const;		// KeyPair‚Ì’†g‚Ìæ“¾
	bool state(INPUT_ID id, int input);			// “ü—ÍÃŞ°À‚Ì¾¯Ä
	void SetOld(void);							// 1ÌÚ°Ñ‘O‚Ì“ü—ÍÃŞ°À‚Ì¾¯Ä


private:
	KeyMap _state;

};

