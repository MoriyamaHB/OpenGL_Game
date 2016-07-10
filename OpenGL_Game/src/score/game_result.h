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
public:
	GameResult();
	int Update();
	void Draw();
	~GameResult();
};

#endif /* SCORE_GAME_RESULT_H_ */
