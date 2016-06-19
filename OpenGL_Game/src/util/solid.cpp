#include "../declaration/GV.h"

////////////////////////    コンストラクタ,初期化    ////////////////////////
Solid::Solid() {
	Init();
}

Solid::Solid(Vector3 point) {
	Init();
	place_ = point;
}

Solid::Solid(float x, float y, float z) {
	Init();
	place_.x = x;
	place_.y = y;
	place_.z = z;
}

Solid::~Solid() {
}

void Solid::Init() {
	place_.zero();
	can_draw_ = false;
	scale_ = 1;
	memcpy(material_, uMaterial4fv_white, sizeof(float) * 4);
}
////////////////////////    setter    ////////////////////////

//デフォルト(false)
void Solid::set_draw_flag(bool tf) {
	can_draw_ = tf;
}
//デフォルト(1)
void Solid::set_scale(float s) {
	scale_ = s;
}

//デフォルト(uMaterial4fv_white)
void Solid::set_material(float mat[]) {
	memcpy(material_, mat, sizeof(float) * 4);
}

////////////////////////    getter    ////////////////////////
Vector3 Solid::get_place_() const {
	return place_;
}

float Solid::get_scale_() const {
	return scale_;
}
////////////////////////    移動    ////////////////////////
void Solid::MoveDiff(Vector3 v) {
	place_ += v;
}

void Solid::Move(Vector3 place) {
	place_ = place;
}
