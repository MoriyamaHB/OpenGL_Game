#define GLOBAL_INSTANCE
#include "../head/GV.h"

GLfloat light0pos[] = { 5.0, 3.0, 0.0, 1.0 };

//ディスプレイ関数
void draw(void) {

	//ディスプレイ初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //画面の初期化
	glLoadIdentity(); //モデルビュー変換行列の初期化

	//カメラ
	transfarAndRotateCameraByMouse(); //カメラ移動計算(マウス)
	transfarCameraByKey(); //カメラ移動計算(キー)
	setGluLookAt(); //視点をセット

	//ライト
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

	//赤い箱
	glPushMatrix();
	Camera camera = getStateCameraCoordinates();
	glTranslated(camera.x, camera.y, camera.z);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, uMaterial4fv_red);
	glutSolidCube(0.1);
	glPopMatrix();

	//地面描画
	glPushMatrix();
	uDrawGround(50);
	glPopMatrix();

	//ディスプレイ終了処理
	glEnd();
	glEndList();
	glutSwapBuffers();
}

//リサイズ
void resize(int w, int h) {
	//ビューポート設定
	glViewport(0, 0, w, h); //ウィンドウ全体をビューポートにする

	//透視変換行列設定
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity(); //透視変換行列の初期化
	gluPerspective(30.0, (double) w / (double) h, 0.1, 100.0);

	//モデルビュー変換行列の指定
	glMatrixMode (GL_MODELVIEW);
}

//タイマー
void timer(int value) {
	glutTimerFunc(1000 / FRAME_PER_SECONDS, timer, 0);
	glutPostRedisplay(); //再描画
}

//初期化
void init(int argc, char *argv[]) {

	//openGLの初期化,ウィンドウ生成
	glutInitWindowSize(WINDOW_INI_HEIGHT, WINDOW_INI_WIDTH);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);

	//openGLイベント関数
	glutDisplayFunc(draw);
	glutKeyboardFunc (checkPushKey);
	glutKeyboardUpFunc (checkUpkey);
	glutPassiveMotionFunc (checkMouseMotion);
	glutMotionFunc(checkMouseMotion);
	glutReshapeFunc(resize);
	glutTimerFunc(100, timer, 0);

	//その他openGLの設定
	glutIgnoreKeyRepeat (GL_TRUE); //繰り返しのキー入力を無視する
	glutSetCursor (GLUT_CURSOR_CROSSHAIR);
	glClearColor(1.0, 1.0, 1.0, 0.0); //塗りつぶし色を白に設定
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_CULL_FACE);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);

	//カメラ初期化
	initCamerCoordinates();
}

//メイン
int main(int argc, char *argv[]) {
	init(argc, argv);
	glutMainLoop();
	return 0;
}

//エラー出力
void ErrorOut(const char file[], const char func[], int line,
		const char message[]) {
	fprintf(stderr, "<file:%s func:%s line:%d>\n", file, func, line);
	fprintf(stderr, "Error:%s\n\n", message);
}
