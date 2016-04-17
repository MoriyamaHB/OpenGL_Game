#include "../head/GV.h"

/*
 * キー入力
 */

//キーの入力状態記録
static unsigned char small_alphabet[26];

//小文字アルファベットの入力状態取得
//入力なら1,非入力なら0を返します
int getStateKeyOfSmallAlphabet(unsigned char key) {
	if (key < 'a' || 'z' < key) {
		uErrorOut(__FILE__, __func__, __LINE__, "keyの値が不正です");
		return -1;
	}
	return small_alphabet[key - 'a'];
}

//OpenGLコールバック関数
void checkPushKey(unsigned char key, int x, int y) {
	//小文字アルファベットの取得
	if ('a' <= key && key <= 'z') {
		small_alphabet[key - 'a'] = 1;
	}
}

//OpenGLコールバック関数
void checkUpkey(unsigned char key, int x, int y) {
	//小文字アルファベットの取得
	if ('a' <= key && key <= 'z') {
		small_alphabet[key - 'a'] = 0;
	}
}

/*
 * マウス入力
 */

//マウスの移動量
static int mouse_dx = 0;
static int mouse_dy = 0;

//前回の呼び出しからのマウス移動量を返します
void getMouseMotionAndInit(int *dx, int *dy) {
	*dx = mouse_dx;
	*dy = mouse_dy;
	mouse_dx = mouse_dy = 0;
}

//OpenGLコールバック関数
//ボタンを押している時 & 押していない時の両方で呼び出されます
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
