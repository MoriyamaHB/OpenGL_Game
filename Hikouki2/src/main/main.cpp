#define GLOBAL_INSTANCE
#include "../declaration/GV.h"

namespace {
Camera3D3P camera;
Fps fps;
Ball ball_test(3.0, 3.0, 0.0);
}

//ゲーム初期化
namespace {
void GameIni() {
	control_meteo::Init();
	control_bullet::Init();
	camera.InitCoordinates();
}
}

namespace {
void UpdateObjects() {
	//球を更新
	ball_test.set_draw_flag(true);
	ball_test.set_scale((float) fps.GetFrameCount() / 1000);
	//隕石更新
	control_meteo::Update(&fps, camera.GetStateCoordinates(),
			camera.GetStateWatchCoordinates());
	//弾更新
	control_bullet::Update(&fps, camera.GetStateCoordinates(),
			camera.GetStateWatchCoordinates());
}
}

//drawが長くなるのでオブジェクトだけ分割
namespace {
static void DrawObjects() {

	//ライト
	//カメラの視点座標に配置
	glPushMatrix();
	GLfloat light0pos[] = { 0.0, 15.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glPopMatrix();

	//赤い箱
	glPushMatrix();
	Vector3 cam_vec = camera.GetStateWatchCoordinates();
	glTranslated(cam_vec.x, cam_vec.y, cam_vec.z);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, uMaterial4fv_red);
	glutSolidCube(0.5);
	glPopMatrix();

	//地面描画
	glPushMatrix();
	uDrawGround(50);
	glPopMatrix();

	//球を描画
	ball_test.Draw();

	//隕石描画
	control_meteo::Draw();
	control_bullet::Draw();
}
}

//ゲームメイン関数
namespace {
void GameMain() {
	//ディスプレイ初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //画面の初期化
	glLoadIdentity(); //モデルビュー変換行列の初期化

	//---------------------------    更新    ---------------------------
	//fps
	fps.Update();
	//カメラ
	camera.TransfarAndRotateByMouse(); //カメラ移動計算(マウス)
	camera.TransfarByKey(); //カメラ移動計算(キー)
	camera.SetGluLookAt(); //視点をセット
	//オブジェクト
	UpdateObjects();

	//---------------------------    描画    ---------------------------
	fps.Draw(10, 25); //fps登録
	camera.DisplayInfo(); //カメラの情報を表示登録
	DrawObjects();	//オブジェクト
	//画面出力文字列描画
	output_display::Draw();
	//ディスプレイ終了処理
	glEnd();
	glEndList();
	glutSwapBuffers();
	if (input::get_small_alphabet_frame('e') == 1)
		exit(0);
}
}

//ゲーム終了
namespace {
void GameFin() {
	output_display::Init();
}
}

//OpenGLコールバック関数
namespace hikouki2_main {
void Draw(void) {
	static MainState main_state = START;

//ゲーム基本処理
	input::UpdateFrame();

	switch (main_state) {
	case START:
		main_state = GAME_INI;
		break;
	case GAME_INI:
		GameIni();
		main_state = GAME;
		break;
	case GAME:
		GameMain();
		break;
	case GAME_FIN:
		GameFin();
		break;
	default:
		uErrorOut(__FILE__, __func__, __LINE__,
				"不明なmain_statです. スタート状態に移行します.");
		main_state = START;
		break;
	}
}
}

//OpenGLコールバック関数
namespace hikouki2_main {
void Resize(int w, int h) {
//ビューポート設定
	glViewport(0, 0, w, h); //ウィンドウ全体をビューポートにする

//透視変換行列設定
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity(); //透視変換行列の初期化
	gluPerspective(80.0, (double) w / (double) h, 0.1, 200.0);

//モデルビュー変換行列の指定
	glMatrixMode (GL_MODELVIEW);
}
}

//OpenGLコールバック関数
//FRAME_PER_SECONDSでdraw関数を呼び出します
namespace hikouki2_main {
void Timer(int value) {
	glutTimerFunc(1000 / FRAME_PER_SECONDS, Timer, 0);
	glutPostRedisplay(); //再描画
}
}

//メイン
int main(int argc, char *argv[]) {
	first_init::FirstInit(argc, argv);
	glutMainLoop();
	return 0;
}
