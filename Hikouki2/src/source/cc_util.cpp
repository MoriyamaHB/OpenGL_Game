#include "../head/GV.h"

namespace cc_util {

//乱数を取得する
int GetRandom(int min, int max) {
	static bool has_inited = false;
	if (!has_inited) {
		srand((unsigned int) time(NULL));
		has_inited = true;
		rand(); //何故か最初だけ65固定になっていたのでここで一度呼び出しておく
	}
	return min + (int) (rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
}
