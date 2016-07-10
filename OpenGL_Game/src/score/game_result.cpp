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
int GameResult::Update() {
	if (input::get_keyboard_frame(13)) { //エンターキーが押されたら
		return -1;
	}
	return 0;
}

//描画
void GameResult::Draw() {
	if (pFont->Error())
		return;
	u3Dto2D();

	//ゲーム結果描画開始
	glColor4fv(uColor4fv_green);
	glRasterPos2f(400, 200);
	pFont->Render("ゲーム結果");


	u2Dto3D();
}

//終了処理
GameResult::~GameResult() {
	delete pFont;
}
