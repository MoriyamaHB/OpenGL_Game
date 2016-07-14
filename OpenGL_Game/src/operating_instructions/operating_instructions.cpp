/*
 * operating_instructions.cpp
 *
 *  Created on: 2016/07/14
 *      Author: mhrbykm
 */
#include "../declaration/GV.h"

OperatingInstructions::OperatingInstructions() {
	// フォント作成
	font_ = new FTPixmapFont("font/jkgl.ttf");
	// フォントの初期化
	if (font_->Error())
		uErrorOut(__FILE__, __func__, __LINE__, "タイトルフォントが開けません");
	else
		font_->FaceSize(kFontSize);
}

//描画
void OperatingInstructions::Draw() {
	if (font_->Error())
		return;

	u3Dto2D();
	glColor4fv(uColor4fv_purple);
	glRasterPos2f(x0-30, y0);
	font_->Render("操作説明");
	glRasterPos2f(x0, y0 + line_space);
	font_->Render("[w/sキー]=加速/減速");
	glRasterPos2f(x0, y0 + line_space*2);
	font_->Render("[a/dキー]=左/右移動");
	glRasterPos2f(x0, y0 + line_space*3);
	font_->Render("[マウス移動]=視点移動");
	glRasterPos2f(x0, y0 + line_space*4);
	font_->Render("[マウスクリック]=弾発射");
	u2Dto3D();
}

OperatingInstructions::~OperatingInstructions() {
	delete font_;
}

