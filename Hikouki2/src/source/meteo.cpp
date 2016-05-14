#include "../head/GV.h"

////////////////////////    コンストラクタ,初期化    ////////////////////////
Meteo::Meteo() {
	Init();
}

Meteo::Meteo(float x, float y, float z) :
		Ball(x, y, z) {
	Init();
}

Meteo::Meteo(Vector3 point) :
		Ball(point) {
	Init();
}

void Meteo::Init() {
	fall_speed_ = 0.01;
	set_material (uMaterial4fv_brown);
}
////////////////////////    setter    ////////////////////////

void Meteo::set_fall_speed(float speed) {
	fall_speed_ = speed;
}

////////////////////////    移動    ////////////////////////

//重力による移動を行う
//テストとしてy方向に毎フレーム0.01ずつ移動する
void Meteo::Fall() {
	Move(0.0, -fall_speed_, 0.0);
}
