#include "../declaration/GV.h"

////////////////////////    コンストラクタ,初期化    ////////////////////////
Bullet::Bullet(float ang_w, float ang_h) :
		Ball() {
	Init(ang_w, ang_h);
}

Bullet::Bullet(float x, float y, float z, float ang_w, float ang_h) :
		Ball(x, y, z) {
	Init(ang_w, ang_h);
}

Bullet::Bullet(Vector3 point, float ang_w, float ang_h) :
		Ball(point) {
	Init(ang_w, ang_h);
}

void Bullet::Init(float ang_w, float ang_h) {
	//フラグ
	set_draw_flag(true);
	//スピード
	speed_ = 10;
	//角度
	angle_w_ = ang_w;
	angle_h_ = ang_h;
}

////////////////////////    更新    ////////////////////////

//移動
void Bullet::Move() {
	float vx = speed_ * cos(angle_w_) * cos(angle_h_);
	float vz = speed_ * sin(angle_w_) * cos(angle_h_);
	float vy = speed_ * sin(angle_h_);
	Ball::Move(vx, vy, vz);
}

//隕石が範囲外かどうか
bool Bullet::IsOutOfRange(Vector3 v1, Vector3 v2) const {
	if (uOutOfRange(place_, v1, v2))
		return true;
	return false;
}
