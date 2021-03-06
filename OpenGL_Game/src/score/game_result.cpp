/*
 * game_result.cpp
 *
 *  Created on: 2016/07/10
 *      Author: mhrbykm
 */

#include "../declaration/GV.h"

GameResult::GameResult() {
	//フォントのパス(ポインタ定数の場合このように定義する必要があるらしい)
	const static char kFontFilePath[256] = "font/jkgm.ttf";
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

//評価を計算
const char* GameResult::GetRating(int score) const {
	static char str[24];
	static int static_score = 0;

	//前回と同じならそれを返す
	if (static_score == score)
		return str;

	//前回と違うとき
	static_score = score;
	if (score >= 70000)
		strcpy(str, "+++");
	else if (score >= 67500)
		strcpy(str, "SSS");
	else if (score >= 65000)
		strcpy(str, "SS+");
	else if (score >= 62500)
		strcpy(str, "SS");
	else if (score >= 60000)
		strcpy(str, "SS-");
	else if (score >= 57500)
		strcpy(str, "S+");
	else if (score >= 55000)
		strcpy(str, "S");
	else if (score >= 52500)
		strcpy(str, "S-");
	else if (score >= 50000)
		strcpy(str, "A+");
	else if (score >= 47500)
		strcpy(str, "A");
	else if (score >= 45000)
		strcpy(str, "A-");
	else if (score >= 42500)
		strcpy(str, "B+");
	else if (score >= 40000)
		strcpy(str, "B");
	else if (score >= 37500)
		strcpy(str, "B-");
	else if (score >= 35000)
		strcpy(str, "C+");
	else if (score >= 32500)
		strcpy(str, "C");
	else if (score >= 30000)
		strcpy(str, "C-");
	else if (score >= 27500)
		strcpy(str, "D+");
	else if (score >= 25000)
		strcpy(str, "D");
	else if (score >= 22500)
		strcpy(str, "D-");
	else if (score >= 20000)
		strcpy(str, "E+");
	else if (score >= 17500)
		strcpy(str, "E");
	else if (score >= 15000)
		strcpy(str, "E-");
	else if (score >= 12500)
		strcpy(str, "F+");
	else if (score >= 10000)
		strcpy(str, "F");
	else if (score >= 7500)
		strcpy(str, "F-");
	else if (score >= 5000)
		strcpy(str, "G+");
	else if (score >= 2500)
		strcpy(str, "G");
	else
		strcpy(str, "G-");

	return str;
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
	char string[128];

	//ゲーム結果描画開始
	glColor4fv (uColor4fv_red);
	glRasterPos2f(x0, y0);
	pFont->Render("<ゲーム結果>");

	//ターゲット獲得スコア
	glColor4fv (uColor4fv_blue);
	glRasterPos2f(x0, y0 + kFontSize + kCharSpace);
	sprintf(string, "ターゲット獲得スコア : %d", opengl_game_main::score.get_score(Score::kGetTarget));
	pFont->Render(string);
	//Meteoとのかすりスコア
	glRasterPos2f(x0, y0 + kFontSize * 2 + kCharSpace);
	sprintf(string, "Meteoとのかすりスコア : %d", opengl_game_main::score.get_score(Score::kNearMeteo));
	pFont->Render(string);
	//Meteo破壊スコア
	glRasterPos2f(x0, y0 + kFontSize * 3 + kCharSpace);
	sprintf(string, "Meteo破壊スコア : %d", opengl_game_main::score.get_score(Score::kDestructMeteo));
	pFont->Render(string);
	//残機ボーナススコア
	glRasterPos2f(x0, y0 + kFontSize * 4 + kCharSpace);
	sprintf(string, "残機ボーナススコア : %d", opengl_game_main::score.get_score(Score::kRemainingLives));
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
	sprintf(string, "評価 : %s", GetRating(opengl_game_main::score.get_total_score()));
	pFont->Render(string);

	//終了案内
	glColor4fv (uColor4fv_yellow);
	glRasterPos2f(x0 + 100, y0 + kFontSize * 9 + kCharSpace);
	pFont->Render("再度プレイ : エンターキー");
	glRasterPos2f(x0 + 100, y0 + kFontSize * 10 + kCharSpace);
	pFont->Render("終了 : Escキー");
	u2Dto3D();
}

//終了処理
GameResult::~GameResult() {
	delete pFont;
}
