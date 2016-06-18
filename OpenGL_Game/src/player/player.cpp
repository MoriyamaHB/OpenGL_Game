#include "../declaration/GV.h"

namespace {
float scale;
Vector3 place;
}

namespace player {
void Init() {
	scale = 0.5;
	place.zero();
}
}

namespace player {
void Update(Vector3 p) {
	::place = p;
}
}

namespace player {
void Draw() {
	//箱描画
	glPushMatrix();
	glTranslated(place.x, place.y, place.z);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, uMaterial4fv_red);
	glutSolidCube(0.5);
	glPopMatrix();
}
}

