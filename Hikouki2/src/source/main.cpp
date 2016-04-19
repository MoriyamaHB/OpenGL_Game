#define GLOBAL_INSTANCE
#include "../head/GV.h"

GLfloat light0pos[] = { 5.0, 3.0, 0.0, 1.0 };
Ball ball_test(3.0f,2.0f,0.0f);//テストです.あとで削除予定

//drawが長くなるのでオブジェクトだけ分割
static void drawObjects() {

	//赤い箱
	glPushMatrix();
	Vector3 cam_vec = camera.getStateWatchCoordinates();
	glTranslated(cam_vec.x, cam_vec.y, cam_vec.z);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, uMaterial4fv_red);
	glutSolidCube(0.01);
	glPopMatrix();

	//地面描画
	glPushMatrix();
	uDrawGround(50);
	glPopMatrix();

	//球を描画
	ball_test.setScale((float)fps.getFrameCount()/1000);
	ball_test.draw();
}

//OpenGLコールバック関数
void draw(void) {

	//ディスプレイ初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //画面の初期化
	glLoadIdentity(); //モデルビュー変換行列の初期化

	//fps
	fps.update();
	fps.draw(10, 25);

	//カメラ
	camera.transfarAndRotateByMouse(); //カメラ移動計算(マウス)
	camera.transfarByKey(); //カメラ移動計算(キー)
	camera.setGluLookAt(); //視点をセット

	//ライト
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

	//オブジェクト描画
	drawObjects();

	//画面出力文字列描画
	out_disp.draw();

	//ディスプレイ終了処理
	glEnd();
	glEndList();
	glutSwapBuffers();
	if (getStateKeyOfSmallAlphabet('e') == 1)
		exit(0);
}

//OpenGLコールバック関数
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

//OpenGLコールバック関数
//FRAME_PER_SECONDSでdraw関数を呼び出します
void timer(int value) {
	glutTimerFunc(1000 / FRAME_PER_SECONDS, timer, 0);
	glutPostRedisplay(); //再描画
}

//メイン
int main(int argc, char *argv[]) {
	first_init(argc, argv);
	glutMainLoop();
	return 0;
}

