#include "../declaration/GV.h"

namespace {
int start_rand_solid;
float start_rand_mate[4];
const GLfloat kLight0Pos[] = { 0.0, 15.0, 0.0, 1.0 };	//ライト位置
}

//ゲーム初期化
namespace start {
void StartIni(Camera3D3P *camera) {
	//カメラ位置
	camera->TransfarAndRotateByParam(0, 300);
	//描画図形乱数
	start_rand_solid = cc_util::GetRandom(0, 5);
	start_rand_mate[0] = cc_util::GetRandom(0, 1000) / 1000.0;
	start_rand_mate[1] = cc_util::GetRandom(0, 1000) / 1000.0;
	start_rand_mate[2] = cc_util::GetRandom(0, 1000) / 1000.0;
	start_rand_mate[3] = cc_util::GetRandom(0, 1000) / 1000.0;
}
}

//スタートメイン部分
namespace start {
int StartMain(Camera3D3P *camera) {
	if (input::get_keyboard_frame('a') == 1)
		return -1;

	//カメラ
	camera->TransfarAndRotateByParam(3, 0); //カメラ移動計算(マウス)
	camera->SetGluLookAt(); //視点をセット
	//地面描画
	uDrawGround(20);
	//ランダムで図形描画
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslated(0, 0.5, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, start_rand_mate);
	switch (start_rand_solid) {
	case 0:
		glutSolidDodecahedron();
		break;
	case 1:
		glutSolidTeapot(1);
		break;
	case 2:
		glutSolidCone(1, 1, 24, 24);
		break;
	case 3:
		glutSolidIcosahedron();
		break;
	case 4:
		glutSolidRhombicDodecahedron();
		break;
	case 5:
		glutSolidTetrahedron();
		break;
	default:
		uErrorOut(__FILE__, __func__, __LINE__, "表示する図形の指定ミス");
		break;
	}
	glPopMatrix();
	//ライト
	glLightfv(GL_LIGHT0, GL_POSITION, kLight0Pos);
	//文字描画
	uDrawString2("Aキーを押してください", 450, 100, uColor4fv_red);
	return 0;
}
}
