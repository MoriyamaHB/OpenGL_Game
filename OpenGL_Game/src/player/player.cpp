#include "../declaration/GV.h"

namespace {
Square square;
int hit_meteo_cnt;
int hit_target_cnt;
}

//プレイヤーの場所を返す
namespace player {
Vector3 get_place() {
	return square.get_place_();
}
}

//プレイヤーの大きさを返す
namespace player {
float get_scale() {
	return square.get_scale_();
}
}

//初期化
namespace player {
void Init() {
	square.Init();
	square.set_draw_flag(true);
	square.set_material(uMaterial4fv_red);
	square.set_scale(0.5);
	hit_meteo_cnt = 0;
	hit_target_cnt = 0;
}
}

//更新
namespace player {
void Update(Vector3 p) {
	//移動
	square.Move(p);
}
}

namespace player {
//隕石衝突時呼び出される
void HitMeteo() {
	hit_meteo_cnt++;
}
//ターゲットにあたった時に呼び出される
void HitTarget() {
	hit_target_cnt++;
}
}

//描画
namespace player {
void Draw() {
	//箱描画
	square.Draw();
	//ヒット情報登録
	char string[24];
	sprintf(string, "hit_meteo_cnt:%d", hit_meteo_cnt);
	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "hit_target_cnt:%d", hit_target_cnt);
	output_display::Regist(string, uColor4fv_green, 1);
}
}

