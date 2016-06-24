#include "../declaration/GV.h"

namespace {
Camera3D3P *camera;
Square square; //playerの四角
int hit_meteo; //隕石衝突回数
int get_target; //ターゲット獲得数
player::PlayerState player_state; //プレイヤーの状態
int die_cnt; //死んだ時のフレームカウント
int now_frame_cnt; //フレームカウント
int remaining_lives; //残機数

const int kRestorationCount = 150; //死んでから復活までのカウント数
const int kInitRemainingLives = 1; //初期残機数
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
	camera = c;
	player_state = PLAY;
	square.Init();
	square.set_draw_flag(true);
	square.set_material(uMaterial4fv_red);
	square.set_scale(0.5);
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
	if(remaining_lives<0)//残機がマイナスなら
		return -1;
	now_frame_cnt = now_cnt; //カウント更新
	square.Move(p);	//移動
	//die中
	if (player_state == DIE) {
		//点滅処理
		if (now_frame_cnt % 5 == 0)
			square.set_draw_flag(!square.get_draw_flag());
		//復活処理
		if (now_frame_cnt - die_cnt >= kRestorationCount) {
			player_state = PLAY;
			square.set_draw_flag(true);
		}
	}
	return 0;
}
}

namespace player {
//隕石に衝突した時呼び出される
void HitMeteo() {
	if (player_state == PLAY) {
		hit_meteo++;
		player_state = DIE;
		die_cnt = now_frame_cnt;
		camera->set_speed(0);
		remaining_lives--;
	}
}
//ターゲットにあたった時に呼び出される
void HitTarget() {
	if (player_state == PLAY)
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
	sprintf(string, "hit_meteo:%d", hit_meteo);
	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "get_target:%d", get_target);
	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "zanki_num:%d", remaining_lives);
	output_display::Regist(string, uColor4fv_red, 1);
}
}

