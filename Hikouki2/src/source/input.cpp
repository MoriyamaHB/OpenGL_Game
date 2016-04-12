#include "../head/GV.h"

//キーの入力
static unsigned char small_alphabet[26]; //小文字アルファベット

//マウスの移動量
static int mouse_dx = 0;
static int mouse_dy = 0;

//小文字アルファベットの入力状態取得
int getStateKeyOfSmallAlphabet(unsigned char key) {
	if (key < 'a' || 'z' < key) {
		ErrorOut(__FILE__, __func__, __LINE__, "keyの値が不正です");
		return -1;
	}
	return small_alphabet[key - 'a'];
}

//キー入力判定
void checkPushKey(unsigned char key, int x, int y) {
	//小文字アルファベットの取得
	if ('a' <= key && key <= 'z') {
		small_alphabet[key - 'a'] = 1;
	}
}

//キー放す判定
void checkUpkey(unsigned char key, int x, int y) {
	//小文字アルファベットの取得
	if ('a' <= key && key <= 'z') {
		small_alphabet[key - 'a'] = 0;
	}
}

//マウス移動量取得&初期化
void getMouseMotionAndInit(int *dx, int *dy) {
	*dx = mouse_dx;
	*dy = mouse_dy;
	mouse_dx = mouse_dy = 0;
}

//マウス移動
void checkMouseMotion(int x, int y) {
	static int wrap_flag = 0;

	if (!wrap_flag) {
		int ww = glutGet(GLUT_WINDOW_WIDTH);
		int wh = glutGet(GLUT_WINDOW_HEIGHT);
		mouse_dx += x - (ww / 2);
		mouse_dy += y - (wh / 2);
		wrap_flag = 1;
		glutWarpPointer(ww / 2, wh / 2);
	} else {
		wrap_flag = 0;
	}
}
