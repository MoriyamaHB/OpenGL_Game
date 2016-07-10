/*
 * game_result.h
 *
 *  Created on: 2016/07/10
 *      Author: mhrbykm
 */

#ifndef SCORE_GAME_RESULT_H_
#define SCORE_GAME_RESULT_H_

class GameResult {
private:
	// フォントのデータ
	FTPixmapFont* pFont; //フォント
	const static unsigned long kFontSize = 40;  //フォントサイズ
	const static char kFontFilePath[256]; //フォントのパス
	const static float x0 = 350; //描画開始位置x
	const static float y0 = 200; //描画開始位置y
	const static float kCharSpace = 10;//行間

public:
	GameResult();
	int Update() const;
	void Draw() const;
	~GameResult();
};

#endif /* SCORE_GAME_RESULT_H_ */
