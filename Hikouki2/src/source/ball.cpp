#include"../head/GV.h"

/*************************    コンストラクタ,初期化    *************************/
Ball::Ball() {
	init();
}

Ball::Ball(Vector3 point) {
	init();
	place = point;
}

Ball::Ball(float x, float y, float z) {
	init();
	place.x = x;
	place.y = y;
	place.z = z;
}

void Ball::init() {
	place.zero();
	scale = 1;
	for (int i = 0; i < 4; i++)
		material[i] = uMaterial4fv_white[i];
	sphere_slices = 24;
	sphere_stacks = 24;
}
/*************************    setter    *************************/

//デフォルト(1)
void Ball::setScale(float s) {
	scale = s;
}

//デフォルト(uMaterial4fv_white)
void Ball::setMaterial(float mat[]) {
	for (int i = 0; i < 4; i++)
		material[i] = mat[i];
}

//デフォルト(24,24)
void Ball::setSphereFineness(float slices, float stacks) {
	sphere_slices = slices;
	sphere_stacks = stacks;
}

/*************************    描画    *************************/

void Ball::draw() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(place.x, place.y, place.z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);
	glutSolidSphere(scale, sphere_slices, sphere_stacks);
	glPopMatrix();
}
