#pragma once
#include "BaseScene.h"
#include <string>
#include <common/VECTOR2.h>
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own) override;	// 各ｱｯﾌﾟﾃﾞｰﾄをまとめる
	void Draw(void);								// ﾀｲﾄﾙｽｸﾘｰﾝでの描画
	SCN_ID GetSceneID(void);						// 今のｼｰﾝを取得
	SCN_ID NextSceneID(void);						// 次のｼｰﾝを取得
private:
	void DrawChar(std::string str, Vector2 pos);	// 文字列の描画用
	int _ghTitleScreen;			// ｹﾞｰﾑﾀｲﾄﾙ用ｽｸﾘｰﾝ
};

