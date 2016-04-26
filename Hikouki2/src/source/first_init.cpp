#include "../head/GV.h"

//初期化
void first_init(int argc, char *argv[]) {

	//openGLの初期化,ウィンドウ生成
	glutInitWindowSize(WINDOW_INI_HEIGHT, WINDOW_INI_WIDTH);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);

	//openGLイベント関数
	glutDisplayFunc (draw);
	glutKeyboardFunc (checkPushKey);
	glutKeyboardUpFunc (checkUpkey);
	glutPassiveMotionFunc (checkMouseMotion);
	glutMotionFunc(checkMouseMotion);
	glutReshapeFunc (resize);
	glutTimerFunc(100, timer, 0);

	//その他openGLの設定
	glutIgnoreKeyRepeat (GL_TRUE); //繰り返しのキー入力を無視する
	glutSetCursor (GLUT_CURSOR_CROSSHAIR);
	glClearColor(1.0, 1.0, 1.0, 0.0); //塗りつぶし色を白に設定
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_CULL_FACE);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glDisable(GL_CULL_FACE); //裏表の麺を描画
}
