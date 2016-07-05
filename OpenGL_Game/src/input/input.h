#ifndef OPENGLGAME_INPUT_INPUT_H_
#define OPENGLGAME_INPUT_INPUT_H_

namespace input {
int get_keyboard_frame(unsigned char key);
int get_special_keyboard_frame(int key);
void CheckPushKey(unsigned char key, int x, int y);
void CheckUpkey(unsigned char key, int x, int y);
void CheckPushSpecialKey(int key, int x, int y);
void CheckUpSpecialkey(int key, int x, int y);
void TakeMouseMotionAndInit(int *dx, int *dy);
int get_mouse_left_button_frame();
void CheckMouse(int button, int state, int x, int y);
void CheckMouseMotion(int x, int y);
void UpdateFrame();
void Init();
}

#endif
