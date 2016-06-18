#include "../declaration/GV.h"

///////////////////////// キー入力 /////////////////////////

//キーの入力状態記録
namespace {
unsigned int small_alphabet[26];
unsigned int small_alphabet_frame[26];
}

//小文字アルファベットの入力フレーム数を返す
namespace input {
int get_small_alphabet_frame(unsigned char key) {
	if (key < 'a' || 'z' < key) {
		uErrorOut(__FILE__, __func__, __LINE__, "keyの値が不正です");
		return -1;
	}
	return small_alphabet_frame[key - 'a'];
}
}

//OpenGLコールバック関数
namespace input {
void CheckPushKey(unsigned char key, int x, int y) {
	//小文字アルファベットの取得
	if ('a' <= key && key <= 'z') {
		small_alphabet[key - 'a'] = 1;
	}
}
}

//OpenGLコールバック関数
namespace input {
void CheckUpkey(unsigned char key, int x, int y) {
	//小文字アルファベットの取得
	if ('a' <= key && key <= 'z') {
		small_alphabet[key - 'a'] = 0;
	}
}
}

///////////////////////// マウス入力 /////////////////////////

//マウスの移動量
namespace {
int mouse_dx = 0;
int mouse_dy = 0;
bool is_down_mouse_left_button = false;
int mouse_left_button_frame = 0;
}

//前回の呼び出しからのマウス移動量を返します
namespace input {
void TakeMouseMotionAndInit(int *dx, int *dy) {
	*dx = mouse_dx;
	*dy = mouse_dy;
	mouse_dx = mouse_dy = 0;
}
}

//左マウスクリックフレーム数を取得
namespace input {
int get_mouse_left_button_frame() {
	return mouse_left_button_frame;
}
}

//OpenGLコールバック関数
//マウスクリックしたor放した時に呼び出されます
namespace input {
void CheckMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		is_down_mouse_left_button = true;
	} else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		is_down_mouse_left_button = false;
	}
}
}

//OpenGLコールバック関数
//ボタンを押している時 & 押していない時の両方で呼び出されます
namespace input {
void CheckMouseMotion(int x, int y) {
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
}

///////////////////////// 更新 /////////////////////////

//押しているフレームをカウントする
namespace input {
void UpdateFrame() {
	//小文字アルファベットのフレームカウント
	for (int i = 0; i < 26; i++) {
		if (small_alphabet[i] == 1)
			small_alphabet_frame[i]++;
		else
			small_alphabet_frame[i] = 0;
	}
	//左マウスクリック
	if (is_down_mouse_left_button)
		mouse_left_button_frame++;
	else
		mouse_left_button_frame = 0;
}
}

///////////////////////// 初期化 /////////////////////////
namespace input {
void Init() {
	memset(small_alphabet, 0, sizeof(small_alphabet));
	memset(small_alphabet_frame, 0, sizeof(small_alphabet_frame));
	mouse_dx = 0;
	mouse_dy = 0;
	is_down_mouse_left_button = false;
	mouse_left_button_frame = 0;
}
}
