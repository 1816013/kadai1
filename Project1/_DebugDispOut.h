#pragma once
#ifdef _DEBUG
#include <Windows.h>
#include <memory>
#include <tuple>
#include <chrono>	// ���x��1ms���炢

// ��ذݐݒ�
#define _dbgStartDrawDebug() _DebugDispOut::GetInstance().StartDrawDebug()
#define _dbgAddDrawDebug() _DebugDispOut::GetInstance().AddDrawDebug()
#define _dbgSetAlpha(alpha) _DebugDispOut::GetInstance().SetAlpha(alpha)
#define _dbgSetUp(alpha) _DebugDispOut::GetInstance().SetUp(alpha)

// DxLib�֐�ׯ��
#define _dbgDrawLine(fmt, ...) _DebugDispOut::GetInstance().DrawLine(fmt,  __VA_ARGS__)
#define _dbgDrawGraph(fmt, ...) _DebugDispOut::GetInstance().DrawGraph(fmt,  __VA_ARGS__)
#define _dbgDrawBox(fmt, ...) _DebugDispOut::GetInstance().DrawBox(fmt,  __VA_ARGS__)
#define _dbgDrawCircle(fmt, ...) _DebugDispOut::GetInstance().DrawCircle(fmt,  __VA_ARGS__)
#define _dbgDrawTriangle(fmt, ...) _DebugDispOut::GetInstance().DrawTriangle(fmt,  __VA_ARGS__)
#define _dbgDrawPixel(fmt, ...) _DebugDispOut::GetInstance().DrawPixel(fmt,  __VA_ARGS__)
//#define _TdbgDrawFormatString(fmt, ...) _DebugDispOut::GetInstance().DrawFormatString(fmt,  __VA_ARGS__)	
#define _dbgDrawFormatString(fmt, ...) _DebugDispOut::GetInstance().SetScreen();\
										DxLib::DrawFormatString(fmt, __VA_ARGS__);\
										_DebugDispOut::GetInstance().RevScreen();

//�۰�@�\
#define _dbgWaitMode _DebugDispOut::GetInstance().WaitMode()



										
using ChronoSysTime = std::chrono::system_clock::time_point;

class _DebugDispOut
{
public:
	static _DebugDispOut& GetInstance(void)
	{
		return (*s_Instance);
	}
	// DxLibׯ�ߗp�֐���DxLib���̧�ݽ����Ƃ��Ă���̂ł킩��Ȃ������炻������邱��
	int DrawLine(int x1, int y1, int x2, int y2, unsigned int Color);	// ��
	int DrawGraph(int x, int y, int GrHandle, int TransFlag);	// �摜
	int DrawBox(int x1, int y1, int x2, int y2,unsigned int Color, int FillFlag);	// ��(�����`)
	int DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag);			// �~
	int DrawTriangle(int x1, int y1, int x2, int y2,int x3, int y3, unsigned int Color, int FillFlag);	// �O�p
	int DrawPixel(int x, int y, unsigned int Color);	// �_
	int DrawString(int x, int y, char *String, unsigned int Color);	// ����
	int DrawFormatString(int x, int y, unsigned int Color, const char *FormatString, ...);	// ����(%d �Ȃǂ��g����)

	void WaitMode(void);		// �۰�@�\
	
	// ��ذݐݒ�
	bool StartDrawDebug(void);	// ���ޯ�޽�ذ݂̏�����
	bool AddDrawDebug(void);	// ���ޯ�޽�ذ݂̏���drawQue�ɒǉ�
	bool SetAlpha(int alpha);	// �����x�̐ݒ�
	bool SetUp(int alpha);		// ���ޯ�޽�ذ݂̍쐬

	void SetScreen(void);		// ���̽�ذ݂��L�^�������ޯ�޽�ذ݂ɕύX
	void RevScreen(void);		// �L�^���Ă�����ذ݂Ɉړ����L�^���Ă��Ȃ�������Ăяo���ƕs��l�������Ă��Ċ댯



private:
	struct _DebugDispOutDeleter		// ��ذ��
	{
		void operator()(_DebugDispOut* _debugContOut) const
		{
			delete _debugContOut;
		}
	};
	_DebugDispOut();
	~_DebugDispOut();

	FILE* _debugFp = nullptr;
	//static _DebugConOut *s_Instance;
	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeleter> s_Instance;

	// ���ޯ�޽�ذ�
	int _alpha;			// �����x
	int _dbgScreen;		// ���ޯ�ޗp�̕\�������齸ذ�
	bool _dbgFlag;		// true: ���ޯ�ތn�̕\���@false:��\��
	int ghBefor;		// �O�̽�ذ�

	// �۰�����n
	ChronoSysTime _startTime;	// �v���͂���old���
	ChronoSysTime _endTime;		// �v���I���new���
	double _waitTime;			// �ҋ@����
};
#else
// Relese�̂Ƃ��͋�ǂ݂���
#define _dbgStartDrawDebug()
#define _dbgAddDrawDebug() 
#define _dbgSetAlpha(alpha) 
#define _dbgSetUp(alpha)
#define _dbgDrawLine(fmt, ...)
#define _dbgDrawGraph(fmt, ...)
#define _dbgDrawBox(fmt, ...)
#define _dbgDrawCircle(fmt, ...)
#define _dbgDrawTriangle(fmt, ...)
#define _dbgDrawPixel(fmt, ...)
//#define _dbgDrawFormatString(fmt, ...)
#define _dbgDrawFormatString(fmt, ...)
#endif	// _DEBUG

