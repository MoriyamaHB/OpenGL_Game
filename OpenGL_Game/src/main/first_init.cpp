#include "../declaration/GV.h"

//初期化
namespace first_init {
void FirstInit(int argc, char *argv[]) {

	//openGLの初期化,ウィンドウ生成
	glutInitWindowSize(WINDOW_INI_HEIGHT, WINDOW_INI_WIDTH);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);

	//openGLイベント関数
	glutDisplayFunc(opengl_game_main::DisplayFunc);
	glutKeyboardFunc(input::CheckPushKey);
	glutKeyboardUpFunc(input::CheckUpkey);
	glutPassiveMotionFunc(input::CheckMouseMotion);
	glutMouseFunc(input::CheckMouse);
	glutMotionFunc(input::CheckMouseMotion);
	glutReshapeFunc(opengl_game_main::Resize);
	glutTimerFunc(100, opengl_game_main::Timer, 0);

	//その他openGLの設定
	glutIgnoreKeyRepeat (GL_TRUE); //繰り返しのキー入力を無視する
	glutSetCursor (GLUT_CURSOR_CROSSHAIR);
	glClearColor(uColor4fv_sky_brue[0], uColor4fv_sky_brue[1],
			uColor4fv_sky_brue[2], uColor4fv_sky_brue[3]);
	//塗りつぶし色を空色に設定
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_CULL_FACE);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glDisable(GL_CULL_FACE); //裏表の麺を描画

	//プロジェクト上で必要な初期化
	input::Init();
	output_display::Init();
}
}
