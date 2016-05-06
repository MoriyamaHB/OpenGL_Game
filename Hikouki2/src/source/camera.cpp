#include "../head/GV.h"

//カメラ座標を初期化する
void Camera3D3P::InitCoordinates() {
	x_ = 0;
	y_ = 5;
	z_ = 0;
	gx_ = 0;
	gy_ = 1;
	gz_ = 0;
	ux_ = 0;
	uy_ = 1;
	uz_ = 0;
	angle_w_ = PI / 2;
	angle_h_ = 0;
}

Camera3D3P::Camera3D3P() {
	InitCoordinates();
}

//カメラ視点座標をVector3クラスで返します
Vector3 Camera3D3P::GetStateWatchCoordinates() const {
	return Vector3(gx_, gy_, gz_);
}

//カメラ座標をマウスの移動から計算する(3人称視点)
void Camera3D3P::TransfarAndRotateByMouse() {

	//マウス移動の取得
	int mouse_dx, mouse_dy;
	TakeMouseMotionAndInit(&mouse_dx, &mouse_dy);

	//マウスの動きをカメラ角度に変換
	angle_w_ += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
	angle_h_ += ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

	//angle_hの角度範囲ををラップする
	//これによりカメラが縦方向に一周しなくなる
	if (angle_h_ < kMinWrapAngleH)
		angle_h_ = kMinWrapAngleH;
	else if (angle_h_ > kMaxWrapAngleH)
		angle_h_ = kMaxWrapAngleH;

	//カメラ角度を視点位置に反映
	x_ = cos(angle_w_) * cos(angle_h_) + gx_;
	z_ = sin(angle_w_) * cos(angle_h_) + gz_;
	y_ = sin(angle_h_) + gy_;

	//todo 一時的なカメラの当たり判定
	if (y_ < 0.05)
		y_ = 0.05;

}

//カメラ座標をキー入力から計算する(3人称視点)
//qが入力されているときはここでカメラが初期化されます
void Camera3D3P::TransfarByKey() {

	//カメラの移動
	if (get_small_alphabet('w') == 1) {
		gx_ -= CAMERA_SP * cos(angle_w_) * cos(angle_h_);
		gz_ -= CAMERA_SP * sin(angle_w_) * cos(angle_h_);
		gy_ -= CAMERA_SP * sin(angle_h_);
	}
	if (get_small_alphabet('s') == 1) {
		gx_ += CAMERA_SP * cos(angle_w_) * cos(angle_h_);
		gz_ += CAMERA_SP * sin(angle_w_) * cos(angle_h_);
		gy_ += CAMERA_SP * sin(angle_h_);
	}
	if (get_small_alphabet('a') == 1) {
		gx_ -= CAMERA_SP * cos(angle_w_ - PI / 2);
		gz_ -= CAMERA_SP * sin(angle_w_ - PI / 2);
	}
	if (get_small_alphabet('d') == 1) {
		gx_ -= CAMERA_SP * cos(angle_w_ + PI / 2);
		gz_ -= CAMERA_SP * sin(angle_w_ + PI / 2);
	}

	//todo 一時的なカメラ視点位置の当たり判定
	if (gy_ < 0)
		gy_ = 0;

	//q入力時_カメラの初期化
	if (get_small_alphabet('q') == 1)
		InitCoordinates();
}

//gluLookAtを設定する
void Camera3D3P::SetGluLookAt() const {
	gluLookAt(x_, y_, z_, gx_, gy_, gz_, ux_, uy_, uz_);
}

//-------------------------------------------------------------------------------------------

Camera3D1P::Camera3D1P() {
	InitCoordinates();
}

//カメラ座標を初期化する
void Camera3D1P::InitCoordinates() {
	x_ = 0;
	y_ = 3;
	z_ = -10;
	gx_ = 0;
	gy_ = 0;
	gz_ = 0;
	ux_ = 0;
	uy_ = 1;
	uz_ = 0;
	angle_w_ = PI / 2;
	angle_h_ = 0;
}

//カメラ視点座標をVector3クラスで返します
Vector3 Camera3D1P::GetStateWatchCoordinates() const {
	return Vector3(gx_, gy_, gz_);
}

//カメラ座標をマウスの移動から計算する(3人称視点)
void Camera3D1P::TransfarAndRotateByMouse() {

	//マウス移動の取得
	int mouse_dx, mouse_dy;
	TakeMouseMotionAndInit(&mouse_dx, &mouse_dy);

	//マウスの動きをカメラ角度に変換
	angle_w_ += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
	angle_h_ -= ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

	//angle_hの角度範囲ををラップする
	//これによりカメラが縦方向に一周しなくなる
	if (angle_h_ < kMinWrapAngleH)
		angle_h_ = kMinWrapAngleH;
	else if (angle_h_ > kMaxWrapAngleH)
		angle_h_ = kMaxWrapAngleH;

	//カメラ角度を視点位置に反映
	gx_ = cos(angle_w_) * cos(angle_h_) + x_;
	gz_ = sin(angle_w_) * cos(angle_h_) + z_;
	gy_ = sin(angle_h_) + y_;

	//todo 一時的なカメラの当たり判定
	if (gy_ < -0.9)
		gy_ = -0.9;

}

//カメラ座標をキー入力から計算する(3人称視点)
//qが入力されているときはここでカメラが初期化されます
void Camera3D1P::TransfarByKey() {

	//カメラの移動
	if (get_small_alphabet('w') == 1) {
		x_ += CAMERA_SP * cos(angle_w_) * cos(angle_h_);
		z_ += CAMERA_SP * sin(angle_w_) * cos(angle_h_);
		y_ += CAMERA_SP * sin(angle_h_);
	}
	if (get_small_alphabet('s') == 1) {
		x_ -= CAMERA_SP * cos(angle_w_) * cos(angle_h_);
		z_ -= CAMERA_SP * sin(angle_w_) * cos(angle_h_);
		y_ -= CAMERA_SP * sin(angle_h_);
	}
	if (get_small_alphabet('a') == 1) {
		x_ += CAMERA_SP * cos(angle_w_ - PI / 2);
		z_ += CAMERA_SP * sin(angle_w_ - PI / 2);
	}
	if (get_small_alphabet('d') == 1) {
		x_ += CAMERA_SP * cos(angle_w_ + PI / 2);
		z_ += CAMERA_SP * sin(angle_w_ + PI / 2);
	}

	//todo 一時的なカメラ視点位置の当たり判定
	if (y_ < 0.1)
		y_ = 0.1;

	//q入力時_カメラの初期化
	if (get_small_alphabet('q') == 1)
		InitCoordinates();
}

//gluLookAtを設定する
void Camera3D1P::SetGluLookAt() const {
	gluLookAt(x_, y_, z_, gx_, gy_, gz_, ux_, uy_, uz_);
}

