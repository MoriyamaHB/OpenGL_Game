#define GLOBAL_INSTANCE
#include "../declaration/GV.h"

//staticグローバル変数
namespace {
Camera3D3P camera;
Fps fps;
LimitedTime ltime; //制限時間
Bgm bgm;
GameResult game_result; //ゲーム結果
bool can_draw_game_result;
const GLfloat kLight0Pos[] = { 0.0, 15.0, 0.0, 1.0 };	//ライト位置
}

//グローバル変数
namespace opengl_game_main {
Score score;
}

//ゲーム初期化
namespace {
void GameIni() {
	control_meteo::Init();
	control_target::Init();
	control_bullet::Init();
	camera.InitCoordinates();
	player::Init(&camera);
	opengl_game_main::score.Init();
	ltime.Init(6);	//制限時間を設定
	can_draw_game_result = true;	//結果出力をfalseに設定
}
}

//ゲームメイン関数
namespace {
int GameMain() {

	//---------------------------    更新    ---------------------------

	//カメラ
	camera.TransfarByKey(); //カメラ移動計算(キー)
	camera.TransfarAndRotateByMouse(); //カメラ移動計算(マウス)
	camera.SetGluLookAt(); //視点をセット
	//隕石更新
	control_meteo::Update(&fps, camera.GetStateCoordinates(),
			camera.GetStateWatchCoordinates());
	//ターゲット更新
	control_target::Update(&fps, camera.GetStateCoordinates(),
			camera.GetStateWatchCoordinates());
	//弾更新
	control_bullet::Update(&camera);
	//プレイヤー更新
	if (player::Update(camera.GetStateWatchCoordinates(), fps.GetFrameCount())
			== -1)
		can_draw_game_result = true;	//結果描画をtrueに設定
	//スコア更新
	opengl_game_main::score.Update();
	//制限時間更新
	if (ltime.Update() == -1) {
		can_draw_game_result = true;	//結果描画をtrueに設定
		player::SetPlayerStateFin();	//プレイヤーの状態を終了に設定
	}

	//---------------------------    描画    ---------------------------

	//ライト
	glLightfv(GL_LIGHT0, GL_POSITION, kLight0Pos);
	//カメラの情報を表示登録
	camera.DisplayInfo();
	//地面描画
	uDrawGround(20);
	//隕石描画
	control_meteo::Draw();
	control_target::Draw();
	control_bullet::Draw();
	//プレイヤー描画
	player::Draw();
	//スコア描画
	opengl_game_main::score.Draw();
	//制限時間描画
	ltime.Draw();

	//結果を描画
	if (can_draw_game_result) {
		if (game_result.Update() == -1)//更新
			return -1;	//ゲーム終了
		game_result.Draw();//描画
	}

	return 0;
}
}

//プロジェクトで必要な終了処理
namespace opengl_game_main {
void ProjectFin() {
	bgm.Stop();	//Bgmを削除
	control_bullet::Fin();	//効果音削除
	player::Fin();
	alutExit();
}
}

//OpenGLコールバック関数
namespace opengl_game_main {
void DisplayFunc(void) {
	static opengl_game_main::MainState main_state =
			opengl_game_main::kProjectIni;

	//ディスプレイ初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //画面の初期化
	glLoadIdentity(); //モデルビュー変換行列の初期化

	//基本処理
	input::UpdateFrame(); //入力状態更新
	fps.Update(); //fps

	switch (main_state) {
	case opengl_game_main::kProjectIni: //プロジェクト上で必要な初期化
		input::Init();
		output_display::Init();
		fps.Init();
		bgm.Stop();
		main_state = kStartIni;
		break;
	case opengl_game_main::kStartIni: //スタート画面初期化
		control_meteo::Init();
		control_target::Init();
		control_bullet::Init();
		camera.InitCoordinates();
		player::Init(&camera);
		opengl_game_main::score.Init();
		start::StartIni(&camera);
		main_state = opengl_game_main::kStart;
		break;
	case opengl_game_main::kStart:		//スタート画面
		if (start::StartMain(&camera) == -1) {
			bgm.Stop();
			main_state = opengl_game_main::kGameIni;
		}
		break;
	case opengl_game_main::kGameIni:		//ゲーム初期化
		GameIni();
		bgm.Play(Bgm::kGameBgm);
		main_state = opengl_game_main::kGame;
		break;
	case opengl_game_main::kGame:		//ゲーム
		if (GameMain() == -1) {
			main_state = kProjectIni;
			bgm.Stop();
		}
		break;
	default:
		uErrorOut(__FILE__, __func__, __LINE__, "不明なmain_stateです. 初期状態に移行します.");
		main_state = opengl_game_main::kStartIni;
		break;
	}

	//基本描画
	fps.Draw(); //fps登録
	output_display::Draw(); //画面出力文字列描画

	//Bgm更新
	bgm.Update();

	//Soundクラスのリスナー位置を更新
	Sound::SetListener(&camera);

	//ディスプレイ終了処理
	glEnd();
	glEndList();
	glutSwapBuffers();
	//エスケープキーで終了
	if (input::get_keyboard_frame('\033') == 1) {
		ProjectFin();
		exit(1);
	}
	//q入力で初期状態に移行
	if (input::get_keyboard_frame('q') == 1)
		main_state = kProjectIni;
}
}

//OpenGLコールバック関数
namespace opengl_game_main {
void Resize(int w, int h) {
	//ビューポート設定
	glViewport(0, 0, w, h); //ウィンドウ全体をビューポートにする

	//透視変換行列設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //透視変換行列の初期化
	gluPerspective(75.0, (double) w / (double) h, 0.1, 200.0);

	//モデルビュー変換行列の指定
	glMatrixMode(GL_MODELVIEW);
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

