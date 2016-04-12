//camera.cpp
GLOBAL void initCamerCoordinates();
GLOBAL Camera getStateCameraCoordinates();
GLOBAL void transfarAndRotateCameraByMouse();
GLOBAL void transfarCameraByKey();
GLOBAL void setGluLookAt();

//input.cpp
GLOBAL int getStateKeyOfSmallAlphabet(unsigned char key);
GLOBAL void checkPushKey(unsigned char key, int x, int y);
GLOBAL void checkUpkey(unsigned char key, int x, int y);
GLOBAL void getMouseMotionAndInit(int *dx, int *dy);
GLOBAL void checkMouseMotion(int x, int y);

//main.cpp
GLOBAL void ErrorOut(const char file[], const char func[], int line,
		const char message[]);
