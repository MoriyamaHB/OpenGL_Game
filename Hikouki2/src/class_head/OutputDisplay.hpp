#include "../head/GV.h"

class OutputDisplay {
public:

	//画面出力文字の登録
	void regist(const char str[], const float color[]) {
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
	void draw() {
		for (int i = 0; i < num; i++)
			uDrawString(item[i].str, START_WIDTH,
					START_HEIGHT + LINE_HEIGHT * i, item[i].color);
		num = 0;
	}
private:
	const static int MAX_ITEM = 10; //最大登録数
	const static int LINE_HEIGHT = 30; //一行分の高さ
	const static int START_WIDTH = 10; //描画開始座標x
	const static int START_HEIGHT = 23; //描画開始座標y
	int num;
	OutputItem item[MAX_ITEM];
};
