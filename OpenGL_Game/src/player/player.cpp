#include "../declaration/GV.h"

namespace {
Camera3D3P *camera;
Sound *player_die_se = NULL;
Sound *get_target_se = NULL;
Square square; //playerの四角
int hit_meteo; //隕石衝突回数
int get_target; //ターゲット獲得数
player::PlayerState player_state; //プレイヤーの状態
int die_cnt; //死んだ時のフレームカウント
int now_frame_cnt; //フレームカウント
int remaining_lives; //残機数

const int kRestorationCount = 150; //死んでから復活までのカウント数
const int kInitRemainingLives = 5; //初期残機数
}

//プレイヤーの場所を返す
namespace player {
Vector3 get_place() {
	return square.get_place();
}
}

//プレイヤーの大きさを返す
namespace player {
float get_scale() {
	return square.get_scale();
}
}

//プレイヤーの状態を返す
namespace player {
PlayerState get_player_state() {
	return player_state;
}
}

//初期化
namespace player {
void Init(Camera3D3P *c) {
	//効果音読み込み
	if (player_die_se == NULL)
		player_die_se = new Sound("sound/player_die.wav");
	if (get_target_se == NULL)
		get_target_se = new Sound("sound/get_target_se.wav");

	camera = c;
	player_state = kPlay;
	square.Init();
	square.set_draw_flag(true);
	square.set_material(uMaterial4fv_red);
	square.set_scale(0.20);
	hit_meteo = 0;
	get_target = 0;
	die_cnt = 0;
	now_frame_cnt = 0;
	remaining_lives = kInitRemainingLives;
}
}

//更新
namespace player {
int Update(Vector3 p, int now_cnt) {
	now_frame_cnt = now_cnt; //カウント更新
	square.Move(p); //移動
	//効果音の場所をリスナー位置に同期
	player_die_se->SetSourceToListener();
	get_target_se->SetSourceToListener();
	//die中
	if (player_state == kDie) {
		//点滅処理
		if (now_frame_cnt % 5 == 0)
			square.set_draw_flag(!square.get_draw_flag());
		//復活処理
		if (now_frame_cnt - die_cnt >= kRestorationCount) {
			player_state = kPlay;
			square.set_draw_flag(true);
		}
	}
	//ゲーム終了時
	if (player_state == kFin) {
		return -1;
	}
	return 0;
}
}

//隕石に衝突した時呼び出される
namespace player {
void HitMeteo() {
	if (player_state == kPlay) {
		hit_meteo++;
		player_state = kDie;
		die_cnt = now_frame_cnt;
		camera->set_speed(0);
		remaining_lives--;
		//効果音再生
		player_die_se->Play();
		if (remaining_lives <= 0) { //残機が0以下なら
			player_state = kFin;
			square.set_draw_flag(false);
		}
	}
}
}

//プレイヤの状態をゲーム終了に設定
namespace player {
void SetPlayerStateFin() {
	player_state = kFin;
	square.set_draw_flag(false);
	//残り残機数分をスコアに加算
	opengl_game_main::score.set_score(5000 * remaining_lives,
			Score::kRemainingLives);
}
}

namespace player {
//ターゲットにあたった時に呼び出される
void HitTarget() {
	get_target_se->Play(); //効果音再生
	if (player_state == kPlay)
		get_target++;
}
}

//描画
namespace player {
void Draw() {
	//箱描画
	square.Draw();
	//ヒット情報登録
	char string[256];
//	sprintf(string, "球破壊:%d", hit_meteo);
//	output_display::Regist(string, uColor4fv_green, 1);
//	sprintf(string, "ターゲット獲得:%d", get_target);
//	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "残機数:%d", remaining_lives);
	output_display::Regist(string, uColor4fv_red, 1);
}
}

//終了処理
namespace player {
void Fin() {
	//効果音削除
	delete player_die_se;
	player_die_se = NULL;
	delete get_target_se;
	get_target_se = NULL;
}
}

