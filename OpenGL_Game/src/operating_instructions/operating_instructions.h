/*
 * operating_instructions.h
 *
 *  Created on: 2016/07/14
 *      Author: mhrbykm
 */

#ifndef OPENGLGAME_OPERATING_INSTRUCTIONS_OPERATING_INSTRUCTIONS_H_
#define OPENGLGAME_OPERATING_INSTRUCTIONS_OPERATING_INSTRUCTIONS_H_

class OperatingInstructions {
private:
	FTPixmapFont *font_;
	const static unsigned long kFontSize = 35;  //タイトルフォントサイズ
	const static int x0 = 1100;  //描画開始座標x
	const static int y0 = 600;  //描画開始座標y
	const static float line_space = kFontSize + 10;  //行間
public:
	OperatingInstructions();
	void Draw();
	~OperatingInstructions();
};

#endif /* OPERATING_INSTRUCTIONS_OPERATING_INSTRUCTIONS_H_ */
