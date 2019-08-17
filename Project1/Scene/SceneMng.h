#pragma once
#include <memory>
#include <vector>
#include <Scene/BaseScene.h>
#include <common/VECTOR2.h>

#define lpSceneMng SceneMng::GetInstance()

using DrawQueT = std::tuple<int, int, int>;	// ｸﾞﾗﾌｨｯｸﾊﾝﾄﾞﾙ, x座標, y座標

enum class DRAW_QUE
{
	IMAGE,	// ﾊﾝﾄﾞﾙ
	X,		// X座標
	Y		// Y座標
};


class SceneMng
{
public:
	static SceneMng &GetInstance(void)	
	{
		return (*s_Instance);
	}
	void Run(void);	// 初期設定

	bool addDrawQue(DrawQueT dQue);		// 描画用のｷｭｰに情報を挿入する

	const Vector2 screenSize;		// ｳｲﾝﾄﾞｳのｻｲｽﾞ(800, 600)
	const Vector2 gameScreenSize;	// ｹﾞｰﾑｽｸﾘｰﾝのｻｲｽﾞ(500, 390)
	const Vector2 gameScreenPos;	// ｹﾞｰﾑｽｸﾘｰﾝの左上のpos

	int Frame(void);				// ｱﾆﾒｰｼｮﾝ用ﾌﾚｰﾑを渡す
private:
	struct SceneDeleter							// ﾃﾞﾘｰﾀｰ
	{
		void operator()(SceneMng* sceneMng)
		{
			delete sceneMng;
		}
	};
	SceneMng();
	~SceneMng();

	bool SysInit(void);	// ｼｽﾃﾑ初期化(最初のみ初期化するもの)
	void Draw(void);	// 描画のｷｭｰをもとに描画していく
	std::vector <DrawQueT> _drawList;	// 描画のｷｭｰ

	// 変数
	static std::unique_ptr<SceneMng, SceneDeleter> s_Instance;		
	unique_Base _activeScene;		// 現在のｼｰﾝ
	SCN_ID _nowScnID;						// 現在のｼｰﾝID
	SCN_ID _nextScnID;						// 現在のｼｰﾝID
	int frame = 0;		// ｱﾆﾒｰｼｮﾝ用ﾌﾚｰﾑ


};

