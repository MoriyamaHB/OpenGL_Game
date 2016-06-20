#define GLOBAL_INSTANCE
#include "../declaration/GV.h"

namespace {
Camera3D3P camera;
Fps fps;
}

//ゲーム初期化
namespace {
void GameIni() {
	control_meteo::Init();
	control_target::Init();
	control_bullet::Init();
	camera.InitCoordinates();
	player::Init();
}
}

//ゲームメイン関数
namespace {
void GameMain() {

	//---------------------------    更新    ---------------------------

	//カメラ
	camera.TransfarAndRotateByMouse(); //カメラ移動計算(マウス)
	camera.TransfarByKey(); //カメラ移動計算(キー)
	camera.SetGluLookAt(); //視点をセット
	//隕石更新
	control_meteo::Update(&fps, camera.GetStateCoordinates(),
			camera.GetStateWatchCoordinates());
	//ターゲット更新
	control_target::Update(&fps, camera.GetStateCoordinates(),
			camera.GetStateWatchCoordinates());
	//弾更新
	control_bullet::Update(camera.GetStateCoordinates(),
			camera.GetStateWatchCoordinates(), camera.get_speed());
	//プレイヤー更新
	player::Update(camera.GetStateWatchCoordinates());

	//---------------------------    描画    ---------------------------

	//カメラの情報を表示登録
	camera.DisplayInfo();
	//ライト
	glPushMatrix();
	GLfloat light0pos[] = { 0.0, 15.0, 0.0, 1.0 };	//カメラの視点座標に配置
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glPopMatrix();
	//地面描画
	glPushMatrix();
	uDrawGround(20);
	glPopMatrix();
	//プレイヤー描画
	player::Draw();
	//隕石描画
	control_meteo::Draw();
	control_target::Draw();
	control_bullet::Draw();

}
}

//ゲーム終了
namespace {
void GameFin() {
	output_display::Init();
}
}

//OpenGLコールバック関数
namespace opengl_game_main {
void DisplayFunc(void) {
	static MainState main_state = START_INI;

	//ディスプレイ初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //画面の初期化
	glLoadIdentity(); //モデルビュー変換行列の初期化

	//基本処理
	input::UpdateFrame(); //入力状態更新
	fps.Update(); //fps

	switch (main_state) {
	case START_INI:
		//プロジェクト上で必要な初期化
		input::Init();
		output_display::Init();
		fps.Init();
		//次に進む
		main_state = START;
		break;
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
		main_state = START_INI;
		break;
	}

	//基本描画
	fps.Draw(10, 25); //fps登録
	output_display::Draw(); //画面出力文字列描画

	//ディスプレイ終了処理
	glEnd();
	glEndList();
	glutSwapBuffers();
	//エスケープキーで終了
	if (input::get_keyboard_frame('\033') == 1)
		exit(0);
	//q入力で初期状態に移行
	if (input::get_keyboard_frame('q') == 1)
		main_state = START_INI;
}
}

//OpenGLコールバック関数
namespace opengl_game_main {
void Resize(int w, int h) {
//ビューポート設定
	glViewport(0, 0, w, h); //ウィンドウ全体をビューポートにする

//透視変換行列設定
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity(); //透視変換行列の初期化
	gluPerspective(75.0, (double) w / (double) h, 0.1, 200.0);

//モデルビュー変換行列の指定
	glMatrixMode (GL_MODELVIEW);
}
}

//OpenGLコールバック関数
//FRAME_PER_SECONDSでDisplayFunc関数を呼び出します
namespace opengl_game_main {
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

