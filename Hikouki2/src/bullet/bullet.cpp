#include "../declaration/GV.h"

////////////////////////    コンストラクタ,初期化    ////////////////////////
Bullet::Bullet(Vector3 point, Vector3 each_move_angle, double camera_speed) {
	Init();
	speed_ = camera_speed + 0.1; //スピード
	Ball::Move(point.x, point.y, point.z);
	each_move_angle_ = each_move_angle;
}

void Bullet::Init() {
	//フラグ
	set_draw_flag(true);
	//大きさ
	set_scale(0.3);
	//マテリアル
	set_material (uMaterial4fv_red);
	//繊細さ
	SetSphereFineness(4, 2);
}

////////////////////////    更新    ////////////////////////

//移動
void Bullet::Move() {
	Ball::Move(speed_ * each_move_angle_.x, speed_ * each_move_angle_.y,
			speed_ * each_move_angle_.z);
}

//隕石が範囲外かどうか
bool Bullet::IsOutOfRange(Vector3 v1, Vector3 v2) const {
	if (uOutOfRange(place_, v1, v2))
		return true;
	return false;
}
