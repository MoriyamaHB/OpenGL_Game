//first_init
GLOBAL void FirstInit(int argc, char *argv[]);

//input.cpp
GLOBAL int getStateKeyOfSmallAlphabet(unsigned char key);
GLOBAL void CheckPushKey(unsigned char key, int x, int y);
GLOBAL void CheckUpkey(unsigned char key, int x, int y);
GLOBAL void getMouseMotionAndInit(int *dx, int *dy);
GLOBAL void CheckMouseMotion(int x, int y);

//main.cpp
GLOBAL void Draw(void);
GLOBAL void Resize(int w, int h);
GLOBAL void Timer(int value);
