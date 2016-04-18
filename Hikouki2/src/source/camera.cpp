#include "../head/GV.h"

//カメラ座標を初期化する
void Camera3D3P::initCoordinates() {
	x = 0;
	y = 5;
	z = 0;
	gx = 0;
	gy = 1;
	gz = 0;
	ux = 0;
	uy = 1;
	uz = 0;
	angle_w = PI / 2;
	angle_h = 0;
}

Camera3D3P::Camera3D3P() {
	initCoordinates();
}

//カメラ視点座標をVector3クラスで返します
Vector3 Camera3D3P::getStateWatchCoordinates() const {
	return Vector3(gx, gy, gz);
}

//カメラ座標をマウスの移動から計算する(3人称視点)
void Camera3D3P::transfarAndRotateByMouse() {

	//マウス移動の取得
	int mouse_dx, mouse_dy;
	getMouseMotionAndInit(&mouse_dx, &mouse_dy);

	//マウスの動きをカメラ角度に変換
	angle_w += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
	angle_h += ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

	//angle_hの角度範囲ををラップする
	//これによりカメラが縦方向に一周しなくなる
	if (angle_h < kMinWrapAngleH)
		angle_h = kMinWrapAngleH;
	else if (angle_h > kMaxWrapAngleH)
		angle_h = kMaxWrapAngleH;

	//カメラ角度を視点位置に反映
	x = cos(angle_w) * cos(angle_h) + gx;
	z = sin(angle_w) * cos(angle_h) + gz;
	y = sin(angle_h) + gy;

	//todo 一時的なカメラの当たり判定
	if (y < 0.05)
		y = 0.05;

}

//カメラ座標をキー入力から計算する(3人称視点)
//qが入力されているときはここでカメラが初期化されます
void Camera3D3P::transfarByKey() {

	//カメラの移動
	if (getStateKeyOfSmallAlphabet('w') == 1) {
		gx -= CAMERA_SP * cos(angle_w) * cos(angle_h);
		gz -= CAMERA_SP * sin(angle_w) * cos(angle_h);
		gy -= CAMERA_SP * sin(angle_h);
	}
	if (getStateKeyOfSmallAlphabet('s') == 1) {
		gx += CAMERA_SP * cos(angle_w) * cos(angle_h);
		gz += CAMERA_SP * sin(angle_w) * cos(angle_h);
		gy += CAMERA_SP * sin(angle_h);
	}
	if (getStateKeyOfSmallAlphabet('a') == 1) {
		gx -= CAMERA_SP * cos(angle_w - PI / 2);
		gz -= CAMERA_SP * sin(angle_w - PI / 2);
	}
	if (getStateKeyOfSmallAlphabet('d') == 1) {
		gx -= CAMERA_SP * cos(angle_w + PI / 2);
		gz -= CAMERA_SP * sin(angle_w + PI / 2);
	}

	//todo 一時的なカメラ視点位置の当たり判定
	if (gy < 0)
		gy = 0;

	//q入力時_カメラの初期化
	if (getStateKeyOfSmallAlphabet('q') == 1)
		initCoordinates();
}

//gluLookAtを設定する
void Camera3D3P::setGluLookAt() const {
	gluLookAt(x, y, z, gx, gy, gz, ux, uy, uz);
}

//-------------------------------------------------------------------------------------------

Camera3D1P::Camera3D1P() {
	initCoordinates();
}

//カメラ座標を初期化する
void Camera3D1P::initCoordinates() {
	x = 0;
	y = 3;
	z = -10;
	gx = 0;
	gy = 0;
	gz = 0;
	ux = 0;
	uy = 1;
	uz = 0;
	angle_w = PI / 2;
	angle_h = 0;
}

//カメラ視点座標をVector3クラスで返します
Vector3 Camera3D1P::getStateWatchCoordinates() const {
	return Vector3(gx, gy, gz);
}

//カメラ座標をマウスの移動から計算する(3人称視点)
void Camera3D1P::transfarAndRotateByMouse() {

	//マウス移動の取得
	int mouse_dx, mouse_dy;
	getMouseMotionAndInit(&mouse_dx, &mouse_dy);

	//マウスの動きをカメラ角度に変換
	angle_w += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
	angle_h -= ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

	//angle_hの角度範囲ををラップする
	//これによりカメラが縦方向に一周しなくなる
	if (angle_h < kMinWrapAngleH)
		angle_h = kMinWrapAngleH;
	else if (angle_h > kMaxWrapAngleH)
		angle_h = kMaxWrapAngleH;

	//カメラ角度を視点位置に反映
	gx = cos(angle_w) * cos(angle_h) + x;
	gz = sin(angle_w) * cos(angle_h) + z;
	gy = sin(angle_h) + y;

	//todo 一時的なカメラの当たり判定
	if (gy < -0.9)
		gy = -0.9;

}

//カメラ座標をキー入力から計算する(3人称視点)
//qが入力されているときはここでカメラが初期化されます
void Camera3D1P::transfarByKey() {

	//カメラの移動
	if (getStateKeyOfSmallAlphabet('w') == 1) {
		x += CAMERA_SP * cos(angle_w) * cos(angle_h);
		z += CAMERA_SP * sin(angle_w) * cos(angle_h);
		y += CAMERA_SP * sin(angle_h);
	}
	if (getStateKeyOfSmallAlphabet('s') == 1) {
		x -= CAMERA_SP * cos(angle_w) * cos(angle_h);
		z -= CAMERA_SP * sin(angle_w) * cos(angle_h);
		y -= CAMERA_SP * sin(angle_h);
	}
	if (getStateKeyOfSmallAlphabet('a') == 1) {
		x += CAMERA_SP * cos(angle_w - PI / 2);
		z += CAMERA_SP * sin(angle_w - PI / 2);
	}
	if (getStateKeyOfSmallAlphabet('d') == 1) {
		x += CAMERA_SP * cos(angle_w + PI / 2);
		z += CAMERA_SP * sin(angle_w + PI / 2);
	}

	//todo 一時的なカメラ視点位置の当たり判定
	if (y < 0.1)
		y = 0.1;

	//q入力時_カメラの初期化
	if (getStateKeyOfSmallAlphabet('q') == 1)
		initCoordinates();
}

//gluLookAtを設定する
void Camera3D1P::setGluLookAt() const {
	gluLookAt(x, y, z, gx, gy, gz, ux, uy, uz);
}

