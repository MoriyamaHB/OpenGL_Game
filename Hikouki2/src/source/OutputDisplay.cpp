#include "../head/GV.h"

//画面出力文字の登録
void OutputDisplay::regist(const char str[], const float color[], int life) {
	int n = this->serchEmptyItem();
	if (n == -1) { //満杯なら
		uErrorOut(__FILE__, __func__, __LINE__, "出力文字は満杯です");
		return;
	}

	//項目に登録する
	strcpy(item[n].str, str);
	for (int i = 0; i < 4; i++)
		item[n].color[i] = color[i];
	item[n].life = life;
	item[n].flag = 1;
}

//登録された文字列を描画します
//描画life=0でも一度は描画されます
//例)lefe=0→1,life=1→1,life=2→2
void OutputDisplay::draw() {
	int dn = 0; //描画回数
	for (int i = 0; i < kMaxItem; i++)
		if (item[i].flag == 1) {
			//項目描画
			uDrawString(item[i].str, kStartWidth,
					kStartHeight + kLineHeight * dn, item[i].color);
			dn++;
			//削除処理
			if (--item[i].life <= 0)
				item[i].flag = 0;
		}
}

//空のitemの添字を返します
//なければ-1を返します
int OutputDisplay::serchEmptyItem() {
	for (int i = 0; i < kMaxItem; i++)
		if (item[i].flag == 0)
			return i;
	return -1;
}
