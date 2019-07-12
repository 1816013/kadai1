#pragma once
#ifdef _DEBUG
#include <Windows.h>
#include <memory>

#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__) // ���Ѻ��۰����ق�printf�ŕ`��

#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d�s��\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "���ĕ\��", MB_OK);\
	}

class _DebugConOut
{
public:
	static _DebugConOut& GetInstance(void)
	{
		return (*s_Instance);
	}
private:
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugContOut) const
		{
			delete _debugContOut;
		}
	};
	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;
	//static _DebugConOut *s_Instance;
	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter> s_Instance;

};
#else
#define TRACE(fmt, ...)
#define AST() 
#endif	// _DEBUG