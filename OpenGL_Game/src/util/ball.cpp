#include "../declaration/GV.h"

////////////////////////    コンストラクタ,初期化    ////////////////////////
Ball::Ball() {
	sphere_slices_ = 24;
	sphere_stacks_ = 24;
}

Ball::Ball(Vector3 point) :
		Solid(point) {
	sphere_slices_ = 24;
	sphere_stacks_ = 24;
}

Ball::Ball(float x, float y, float z) :
		Solid(x, y, z) {
	sphere_slices_ = 24;
	sphere_stacks_ = 24;
}

void Ball::Init() {
	Solid::Init();
	sphere_slices_ = 24;
	sphere_stacks_ = 24;
}

////////////////////////    setter    ////////////////////////
//デフォルト(24,24)
void Ball::SetSphereFineness(float slices, float stacks) {
	sphere_slices_ = slices;
	sphere_stacks_ = stacks;
}

////////////////////////    描画    ////////////////////////

void Ball::Draw() const {
	if (can_draw_ == false)
		return;

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(place_.x, place_.y, place_.z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_);
	glutSolidSphere(scale_, sphere_slices_, sphere_stacks_);
	glPopMatrix();
}
