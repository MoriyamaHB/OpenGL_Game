//first_init
GLOBAL void FirstInit(int argc, char *argv[]);

//input.cpp
GLOBAL int get_small_alphabet(unsigned char key);
GLOBAL void CheckPushKey(unsigned char key, int x, int y);
GLOBAL void CheckUpkey(unsigned char key, int x, int y);
GLOBAL void TakeMouseMotionAndInit(int *dx, int *dy);
GLOBAL void CheckMouseMotion(int x, int y);

//main.cpp
GLOBAL void Draw(void);
GLOBAL void Resize(int w, int h);
GLOBAL void Timer(int value);
