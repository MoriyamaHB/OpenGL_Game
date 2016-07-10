/*
 * game_result.cpp
 *
 *  Created on: 2016/07/10
 *      Author: mhrbykm
 */

#include "../declaration/GV.h"

GameResult::GameResult() {
	//フォントのパス(ポインタ定数の場合このように定義する必要があるらしい)
	const static char kFontFilePath[256] = "font/hui.ttf";
	// フォントの初期化
	pFont = new FTPixmapFont(kFontFilePath);
	if (pFont->Error()) {
		char es[256];
		sprintf(es, "%sが開けません", kFontFilePath);
		uErrorOut(__FILE__, __func__, __LINE__, es);
	} else {
		pFont->FaceSize(kFontSize);
	}
}

//更新
int GameResult::Update() const {
	if (input::get_keyboard_frame(13)) { //エンターキーが押されたら
		return -1;
	}
	return 0;
}

//描画
void GameResult::Draw() const {
	if (pFont->Error())
		return;
	u3Dto2D();
	char string[256];

	//ゲーム結果描画開始
	glColor4fv(uColor4fv_red);
	glRasterPos2f(x0, y0);
	pFont->Render("<ゲーム結果>");

	//ターゲット獲得スコア
	glColor4fv(uColor4fv_blue);
	glRasterPos2f(x0, y0 + kFontSize + kCharSpace);
	sprintf(string, "ターゲット獲得スコア : %d",
			opengl_game_main::score.get_score(Score::kGetTarget));
	pFont->Render(string);
	//Meteoとのかすりスコア
	glRasterPos2f(x0, y0 + kFontSize * 2 + kCharSpace);
	sprintf(string, "Meteoとのかすりスコア : %d",
			opengl_game_main::score.get_score(Score::kNearMeteo));
	pFont->Render(string);
	//Meteo破壊スコア
	glRasterPos2f(x0, y0 + kFontSize * 3 + kCharSpace);
	sprintf(string, "Meteo破壊スコア : %d",
			opengl_game_main::score.get_score(Score::kDestructMeteo));
	pFont->Render(string);
	//残機ボーナススコア
	glRasterPos2f(x0, y0 + kFontSize * 4 + kCharSpace);
	sprintf(string, "残機ボーナススコア : %d",
			opengl_game_main::score.get_score(Score::kRemainingLives));
	pFont->Render(string);
	//----------------
	glRasterPos2f(x0, y0 + kFontSize * 5 + kCharSpace);
	pFont->Render("-------------------------------");
	//合計スコア
	glColor4fv(uColor4fv_red);
	glRasterPos2f(x0, y0 + kFontSize * 6 + kCharSpace);
	sprintf(string, "合計スコア : %d", opengl_game_main::score.get_total_score());
	pFont->Render(string);
	//評価
	glColor4fv(uColor4fv_red);
	glRasterPos2f(x0, y0 + kFontSize * 7 + kCharSpace);
	sprintf(string, "評価 : %c", 'A');
	pFont->Render(string);

	//終了案内
	glColor4fv(uColor4fv_yellow);
	glRasterPos2f(x0 + 200, y0 + kFontSize * 9 + kCharSpace);
	pFont->Render("再度プレイ : エンターキー");
	glRasterPos2f(x0 + 200, y0 + kFontSize * 10 + kCharSpace);
	pFont->Render("終了 : Escキー");
	u2Dto3D();
}

//終了処理
GameResult::~GameResult() {
	delete pFont;
}