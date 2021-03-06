#include "../declaration/GV.h"

////////////////////////    コンストラクタ,初期化    ////////////////////////

//each_move_angle * speedずつ各座標軸で移動を行います
Meteo::Meteo(Vector3 point, Vector3 each_move_angle) :
		Ball() {
	Init();
	Ball::MoveDiff(point);
	each_move_angle_ = each_move_angle;
}

void Meteo::Init() {
	//フラグ
	set_draw_flag(true);
	//大きさ
	int s = cc_util::GetRandom(1, 8);
	set_scale(s);
	//スピード
	speed_ = cc_util::GetRandom(1, 50) / 100.0;
	//マテリアル
	float r = cc_util::GetRandom(0, 1000) / 1000.0;
	float g = cc_util::GetRandom(0, 1000) / 1000.0;
	float b = cc_util::GetRandom(0, 1000) / 1000.0;
	float mate[4] = { r, g, b, 1.0 };
	set_material(mate);
	//繊細さ
	SetSphereFineness(14, 14);
}

////////////////////////    更新    ////////////////////////

//移動を行う
void Meteo::Move() {
	Vector3 move_diff = speed_ * each_move_angle_;
	Ball::MoveDiff(move_diff);
}

//隕石が範囲外かどうか
bool Meteo::IsOutOfRange(Vector3 v1, Vector3 v2) const {
	if (uOutOfRange(place_, v1, v2))
		return true;
	return false;
}

////////////////////////    描画    ////////////////////////
void Meteo::Draw() const {
	//Ballクラスを描画
	Ball::Draw();
	//影もどきを描画
//	if (place_.y >= 0) {
//		float x = place_.x, y = 0.01, z = place_.z;
//		float radius = scale_;
//		for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 10.0) {
//			float th2 = th1 + 10.0;
//			float th1_rad = th1 / 180.0 * uPI;
//			float th2_rad = th2 / 180.0 * uPI;
//
//			float x1 = radius * cos(th1_rad);
//			float y1 = radius * sin(th1_rad);
//			float x2 = radius * cos(th2_rad);
//			float y2 = radius * sin(th2_rad);
//
//			glNormal3f(0.0, 1.0, 0.0);
//			float t = place_.y / Meteo::kAppearanceHeight;
//			float mate[] = { t, t, t, 1.0f };
//			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mate);
//			glBegin(GL_TRIANGLES);
//			glVertex3f(x, y, z);
//			glVertex3f(x1 + x, y, y1 + z);
//			glVertex3f(x2 + x, y, y2 + z);
//			glEnd();
//		}
//	}
}

