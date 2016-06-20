namespace input {
int get_keyboard_frame(unsigned char key);
void CheckPushKey(unsigned char key, int x, int y);
void CheckUpkey(unsigned char key, int x, int y);
void TakeMouseMotionAndInit(int *dx, int *dy);
int get_mouse_left_button_frame();
void CheckMouse(int button, int state, int x, int y);
void CheckMouseMotion(int x, int y);
void UpdateFrame();
void Init();
}
