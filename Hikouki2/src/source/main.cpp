#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include"../head_2/vector3.h"
#include<iostream>
#include"../head_2/uGL.h"

#define WINDOW_INI_HEIGHT 1200
#define WINDOW_INI_WIDTH 800
#define FRAME_PER_SECONDS 60
#define CAMERA_SP 0.05//カメラスピード
#define CAMERA_ROTATE_PX 4000//カメラが一周回るためのマウス移動ピクセル量
#define PI 3.14159265
#define CAMERA_SP_D 0.1 //加速、減速キーを押しているときに1フレームの変化量
/* ディスプレイリスト番号 */
GLuint objects;

/* 物体の色 */

GLfloat light0pos[] = { 5.0, 3.0, 0.0, 1.0 };
float CameraX = 0;
float CameraY = 0;
float CameraZ = -10;
float CameraGx = 0;
float CameraGy = 0;
float CameraGz = 0;
float CameraRx = 0;
float CameraRy = 1;
float CameraRz = 0;

typedef struct {
	float x;
	float y;
	float z;
} D3;

typedef struct {
	float x;
	float y;
} D2;

//wasdキーの入力
int key_w = 0;
int key_a = 0;
int key_s = 0;
int key_d = 0;

int key_q = 0; //リセットキー
//マウスの移動量
int mouse_dx = 0;
int mouse_dy = 0;

double k = 1; //速度係数

//カメラの角度
double camera_angle = PI / 2;
double camera_angleY = 0;

//ループカウント
int loop_count = 0;

//カメラ移動、視点変更
void camera_TR() {
	//カメラの視点変更
	camera_angle += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
	camera_angleY -= ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;
	mouse_dx = mouse_dy = 0;
	CameraGx = cos(camera_angle) * cos(camera_angleY) + CameraX;
	CameraGz = sin(camera_angle) * cos(camera_angleY) + CameraZ;
	CameraGy = sin(camera_angleY) + CameraY;
	if (key_q != 0) { //リセットキーが押されたら
		//視点,座標を初期化
		CameraX = CameraY = 0;
		CameraZ = -10;
		camera_angle = PI / 2;
		camera_angleY = 0;
		key_q = 0;
	}

	//カメラの移動

	//前進する
	if (key_w == 1) {
		CameraX += CAMERA_SP * cos(camera_angle) * cos(camera_angleY) * k;
		CameraZ += CAMERA_SP * sin(camera_angle) * cos(camera_angleY) * k;
		CameraY += CAMERA_SP * sin(camera_angleY) * k;
	}
	if (key_s == 1) {
		CameraX -= CAMERA_SP * cos(camera_angle) * cos(camera_angleY) * k;
		CameraZ -= CAMERA_SP * sin(camera_angle) * cos(camera_angleY) * k;
		CameraY -= CAMERA_SP * sin(camera_angleY) * k;
	}
	if (key_a == 1) {
		CameraX += CAMERA_SP * cos(camera_angle - PI / 2) * cos(camera_angleY)
				* k;
		CameraZ += CAMERA_SP * sin(camera_angle - PI / 2) * cos(camera_angleY)
				* k;
		//CameraY += CAMERA_SP * sin(camera_angleY + PI / 2) * k;
	}
	if (key_d == 1) {
		CameraX += CAMERA_SP * cos(camera_angle + PI / 2) * cos(camera_angleY)
				* k;
		CameraZ += CAMERA_SP * sin(camera_angle + PI / 2) * cos(camera_angleY)
				* k;
		//CameraY += CAMERA_SP * sin(camera_angleY - PI / 2) * k;
	}
}

//ディスプレイ関数
void draw(void) {
	static int frc = 0;
	loop_count++;
	camera_TR();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(CameraX, CameraY, CameraZ, CameraGx, CameraGy, CameraGz, CameraRx,
			CameraRy, CameraRz);
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

	/* 赤い箱 */
	glPushMatrix();
	glTranslated(CameraGx, CameraGy, CameraGz);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, uMaterial4fv_red);
	glutSolidCube(0.1);
	glPopMatrix();

	//地面描画
	glPushMatrix();
	uDrawGround(20);
	glPopMatrix();

	glEnd();
	glEndList();
	glutSwapBuffers();
	frc++;

}

void resize(int w, int h) {
	/* ウィンドウ全体をビューポートにする */
	glViewport(0, 0, w, h);

	/* 透視変換行列の指定 */
	glMatrixMode(GL_PROJECTION);

	/* 透視変換行列の初期化 */
	glLoadIdentity();
	gluPerspective(30.0, (double) w / (double) h, 0.1, 100.0);

	/* モデルビュー変換行列の指定 */
	glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
	glutTimerFunc(1000 / FRAME_PER_SECONDS, timer, 0);
	glutPostRedisplay(); //再描画
}

void motion(int x, int y) {
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

//キー入力
void key(unsigned char key, int x, int y) {
	if (key == 'w')
		key_w = 1;
	if (key == 's')
		key_s = 1;
	if (key == 'a')
		key_a = 1;
	if (key == 'd')
		key_d = 1;
	if (key == 'q')
		key_q = 1;
}

//キー放す
void keyup(unsigned char key, int x, int y) {
	if (key == 'w')
		key_w = 0;
	if (key == 's')
		key_s = 0;
	if (key == 'a')
		key_a = 0;
	if (key == 'd')
		key_d = 0;
}

//初期化
void init(int argc, char *argv[]) {

	//openGLの初期化,ウィンドウ生成
	glutInitWindowSize(WINDOW_INI_HEIGHT, WINDOW_INI_WIDTH);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(draw);

	//キーボード、マウス入力
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyup);
	glutPassiveMotionFunc(motion);
	glutMotionFunc(motion);
	glutIgnoreKeyRepeat(GL_TRUE); //繰り返しのキー入力を無視する

	glutReshapeFunc(resize);
	glClearColor(1.0, 1.0, 1.0, 0.0); //塗りつぶし色を白に設定
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutTimerFunc(100, timer, 0);
}

//メイン
int main(int argc, char *argv[]) {
	init(argc, argv);
	glutMainLoop();
	return 0;
}
