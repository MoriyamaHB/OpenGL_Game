#include "../head/GV.h"

//画面出力文字の登録
void OutputDisplay::regist(const char str[], const float color[]) {
	if (num >= MAX_ITEM) { //満杯なら
		uErrorOut(__FILE__, __func__, __LINE__, "出力文字は満杯です");
		return;
	}
	strcpy(item[num].str, str);
	for (int i = 0; i < 4; i++)
		item[num].color[i] = color[i];
	num++;
}

//画面出力文字の描画
void OutputDisplay::draw() {
	for (int i = 0; i < num; i++)
		uDrawString(item[i].str, START_WIDTH, START_HEIGHT + LINE_HEIGHT * i,
				item[i].color);
	num = 0;
}
