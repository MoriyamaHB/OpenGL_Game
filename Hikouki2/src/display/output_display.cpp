#include "../declaration/GV.h"

namespace {
const int kMaxItem = 24; 	//最大登録数
const int kLineHeight = 30; 	//一行分の高さ
const int kStartWidth = 10; 	//描画開始座標x
const int kStartHeight = 23; //描画開始座標y
OutputItem item_[kMaxItem];
}

//空のitemの添字を返します
//なければ-1を返します
namespace {
int SerchEmptyItem() {
	for (int i = 0; i < kMaxItem; i++)
		if (item_[i].flag == 0)
			return i;
	return -1;
}
}

//画面出力文字の登録
namespace output_display {
void Regist(const char str[], const float color[], int life) {
	int n = SerchEmptyItem();
	if (n == -1) { //満杯なら
		uErrorOut(__FILE__, __func__, __LINE__, "出力文字は満杯です");
		return;
	}

	//項目に登録する
	strcpy(item_[n].str, str);
	for (int i = 0; i < 4; i++)
		item_[n].color[i] = color[i];
	item_[n].life = life;
	item_[n].flag = 1;
}
}

//登録された文字列を描画します
//描画life=0でも一度は描画されます
//例)lefe=0→1,life=1→1,life=2→2
namespace output_display {
void Draw() {
	int dn = 0; //描画回数
	for (int i = 0; i < kMaxItem; i++)
		if (item_[i].flag == 1) {
			//項目描画
			uDrawString(item_[i].str, kStartWidth,
					kStartHeight + kLineHeight * dn, item_[i].color);
			dn++;
			//削除処理
			if (--item_[i].life <= 0)
				item_[i].flag = 0;
		}
}
}

