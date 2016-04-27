#include"../head/GV.h"

/*************************    コンストラクタ,初期化    *************************/
Ball::Ball() {
	init();
}

Ball::Ball(Vector3 point) {
	init();
	place_ = point;
}

Ball::Ball(float x, float y, float z) {
	init();
	place_.x = x;
	place_.y = y;
	place_.z = z;
}

void Ball::init() {
	place_.zero();
	draw_flag_ = false;
	scale_ = 1;
	for (int i = 0; i < 4; i++)
		material_[i] = uMaterial4fv_white[i];
	sphere_slices_ = 24;
	sphere_stacks_ = 24;
}
/*************************    setter    *************************/

//デフォルト(false)
void Ball::setDrawFlag(bool tf) {
	draw_flag_ = tf;
}
//デフォルト(1)
void Ball::setScale(float s) {
	scale_ = s;
}

//デフォルト(uMaterial4fv_white)
void Ball::setMaterial(float mat[]) {
	for (int i = 0; i < 4; i++)
		material_[i] = mat[i];
}

//デフォルト(24,24)
void Ball::setSphereFineness(float slices, float stacks) {
	sphere_slices_ = slices;
	sphere_stacks_ = stacks;
}
/*************************    移動    *************************/
void Ball::Move(float vx, float vy, float vz) {
	place_.x += vx;
	place_.y += vy;
	place_.z += vz;
}

/*************************    描画    *************************/

void Ball::draw() {
	if (draw_flag_ == false)
		return;

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(place_.x, place_.y, place_.z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_);
	glutSolidSphere(scale_, sphere_slices_, sphere_stacks_);
	glPopMatrix();
}
