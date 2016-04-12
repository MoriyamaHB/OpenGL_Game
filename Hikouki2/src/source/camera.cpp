#include"../head/GV.h"

//カメラ座標を初期化する
void Camera::initCoordinates() {
	x = 0;
	y = 3;
	z = -10;
	gx = 0;
	gy = 0;
	gz = 0;
	ux = 0;
	uy = 1;
	uz = 0;
	angle_h = PI / 2;
	angle_w = 0;
}

//カメラ座標を取得する
Vector3 Camera::getStateCoordinates() const {
	return Vector3(x, y, z);
}

//カメラ座標をマウスの移動から計算する(3人称視点)
void Camera::transfarAndRotateByMouse() {

	//マウス移動の取得
	int mouse_dx, mouse_dy;
	getMouseMotionAndInit(&mouse_dx, &mouse_dy);

	//マウスの動きをカメラ角度に変換
	angle_h += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
	angle_w += ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

	//カメラ角度を視点位置に反映
	gx = cos(angle_h) * cos(angle_w) + x;
	gz = sin(angle_h) * cos(angle_w) + z;
	gy = sin(angle_w) + y;

}

//カメラ座標をキー入力から計算する(3人称視点)
void Camera::transfarByKey() {
	//カメラの移動
	if (getStateKeyOfSmallAlphabet('w') == 1) {
		x -= CAMERA_SP * cos(angle_h) * cos(angle_w);
		z -= CAMERA_SP * sin(angle_h) * cos(angle_w);
		y -= CAMERA_SP * sin(angle_w);
	}
	if (getStateKeyOfSmallAlphabet('s') == 1) {
		x += CAMERA_SP * cos(angle_h) * cos(angle_w);
		z += CAMERA_SP * sin(angle_h) * cos(angle_w);
		y += CAMERA_SP * sin(angle_w);
	}
	if (getStateKeyOfSmallAlphabet('a') == 1) {
		x += CAMERA_SP * cos(angle_h - PI / 2) * cos(angle_w);
		z += CAMERA_SP * sin(angle_h - PI / 2) * cos(angle_w);
	}
	if (getStateKeyOfSmallAlphabet('d') == 1) {
		x -= CAMERA_SP * cos(angle_h + PI / 2) * cos(angle_w);
		z -= CAMERA_SP * sin(angle_h + PI / 2) * cos(angle_w);
	}

	//q入力時_カメラの初期化
	if (getStateKeyOfSmallAlphabet('q') == 1)
		initCoordinates();
}

//gluLookAtを設定する
void Camera::setGluLookAt() const {
	gluLookAt(gx, gy, gz, x, y, z, ux, uy, uz);
}
