#include "../declaration/GV.h"

////////////////////////    コンストラクタ,初期化    ////////////////////////
Square::Square() {
}

Square::Square(Vector3 point) :
		Solid(point) {
}

Square::Square(float x, float y, float z) :
		Solid(x, y, z) {
}

////////////////////////    描画    ////////////////////////

void Square::Draw() const {
	if (can_draw_ == false)
		return;

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(place_.x, place_.y, place_.z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_);
	glutSolidCube(0.5);
	glPopMatrix();
}
