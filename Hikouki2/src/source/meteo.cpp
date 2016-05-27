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
	set_material(uMaterial4fv_brown);
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

////////////////////////    描画    ////////////////////////
void Meteo::Draw() {
	static_cast<Ball>(*this).Draw(); //Ballクラスを描画
	if (place_.y >= 0) {
		float x = place_.x, y = 0.01, z = place_.z;
		float radius = scale_;
		for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 1.0) {
			float th2 = th1 + 10.0;
			float th1_rad = th1 / 180.0 * uPI;
			float th2_rad = th2 / 180.0 * uPI;

			float x1 = radius * cos(th1_rad);
			float y1 = radius * sin(th1_rad);
			float x2 = radius * cos(th2_rad);
			float y2 = radius * sin(th2_rad);
			//float mate[]={
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, uMaterial4fv_red);
			glBegin(GL_TRIANGLES);
			glVertex3f(x, y, z);
			glVertex3f(x1 + x, y, y1 + z);
			glVertex3f(x2 + x, y, y2 + z);
			glEnd();
		}
	}
}

