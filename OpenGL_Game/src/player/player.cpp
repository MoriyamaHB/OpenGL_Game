#include "../declaration/GV.h"

namespace {
float scale;
Vector3 place;
int hit_meteo_cnt;
}

//プレイヤーの場所を返す
namespace player {
Vector3 get_place() {
	return place;
}
}

//プレイヤーの大きさを返す
namespace player {
float get_scale() {
	return scale;
}
}

//初期化
namespace player {
void Init() {
	scale = 0.5;
	place.zero();
	hit_meteo_cnt = 0;
}
}

//更新
namespace player {
void Update(Vector3 p) {
	//移動
	::place = p;
}
}

//隕石衝突時呼び出される
namespace player {
void HitMeteo() {
	hit_meteo_cnt++;
}
}

//描画
namespace player {
void Draw() {
	//箱描画
	glPushMatrix();
	glTranslated(place.x, place.y, place.z);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, uMaterial4fv_red);
	glutSolidCube(0.5);
	glPopMatrix();
	//ヒット情報登録
	char string[24];
	sprintf(string, "hit_meteo_cnt:%d", hit_meteo_cnt);
	output_display::Regist(string, uColor4fv_green, 1);
}
}

