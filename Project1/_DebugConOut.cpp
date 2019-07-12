#ifdef _DEBUG
#include <Windows.h>
#include "_DebugConOut.h"

std::unique_ptr<_DebugConOut, _DebugConOut::_DebugConOutDeleter> _DebugConOut::s_Instance(new _DebugConOut);

_DebugConOut::_DebugConOut()
{
	//HWND hWnd = GetForegroundWindow();	// �\������Ă��鳲��޳
	AllocConsole();
	freopen_s(&_debugFp, "CONOUT$", "w", stdout);
	freopen_s(&_debugFp, "CONIN$", "r", stdin);
	//SetForegroundWindow(hWnd);			// ���̳���޳��O��
}

_DebugConOut::~_DebugConOut()
{
	FreeConsole();
}

#endif	// _DEBUG