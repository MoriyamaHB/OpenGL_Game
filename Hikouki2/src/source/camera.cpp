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
	speed_ = 0;
	distance_=1.5;
}

Camera3D3P::Camera3D3P() {
	InitCoordinates();
}

//カメラ視点座標をVector3クラスで返します
Vector3 Camera3D3P::GetStateWatchCoordinates() const {
	return Vector3(gx_, gy_, gz_);
}

//カメラ座標をVector3クラスで返します
Vector3 Camera3D3P::GetStateCoordinates() const {
	return Vector3(x_, y_, z_);
}

//カメラ座標をマウスの移動から計算する(3人称視点)
void Camera3D3P::TransfarAndRotateByMouse() {

	//マウス移動の取得
	int mouse_dx, mouse_dy;
	input::TakeMouseMotionAndInit(&mouse_dx, &mouse_dy);

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
	x_ = distance_ * cos(angle_w_) * cos(angle_h_) + gx_;
	z_ = distance_ * sin(angle_w_) * cos(angle_h_) + gz_;
	y_ = distance_ * sin(angle_h_) + gy_;

}

//カメラ座標をキー入力から計算する(3人称視点)
//qが入力されているときはここでカメラが初期化されます
void Camera3D3P::TransfarByKey() {

	//スピード変更
	if (input::get_small_alphabet_frame('w')) {
		speed_ += kAcceleration;
	}
	if (input::get_small_alphabet_frame('s')) {
		speed_ -= kAcceleration;
	}

	//スピードラップ
	WrapSpeed();

	//カメラの移動
	gx_ -= speed_ * cos(angle_w_) * cos(angle_h_);
	gz_ -= speed_ * sin(angle_w_) * cos(angle_h_);
	gy_ -= speed_ * sin(angle_h_);

	//q入力時_カメラの初期化
	if (input::get_small_alphabet_frame('q') == 1)
		InitCoordinates();
}

//gluLookAtを設定する
void Camera3D3P::SetGluLookAt() const {
	gluLookAt(x_, y_, z_, gx_, gy_, gz_, ux_, uy_, uz_);
}

//速度をラップする
void Camera3D3P::WrapSpeed() {
	if (speed_ < kMinSpeed)
		speed_ = kMinSpeed;
	if (speed_ > kMaxSpeed)
		speed_ = kMaxSpeed;
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
	speed_ = 0;
	angle_w_ = PI / 2;
	angle_h_ = 0;
	distance_=1.5;
	//UpdateDistance();
}

//カメラ視点座標をVector3クラスで返します
Vector3 Camera3D1P::GetStateWatchCoordinates() const {
	return Vector3(gx_, gy_, gz_);
}

//カメラ座標をVector3クラスで返します
Vector3 Camera3D1P::GetStateCoordinates() const {
	return Vector3(x_, y_, z_);
}

//カメラ座標をマウスの移動から計算する(3人称視点)
void Camera3D1P::TransfarAndRotateByMouse() {

	//マウス移動の取得
	int mouse_dx, mouse_dy;
	input::TakeMouseMotionAndInit(&mouse_dx, &mouse_dy);

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
	gx_ = distance_ * cos(angle_w_) * cos(angle_h_) + x_;
	gz_ = distance_ * sin(angle_w_) * cos(angle_h_) + z_;
	gy_ = distance_ * sin(angle_h_) + y_;

}

//カメラ座標をキー入力から計算する(3人称視点)
//qが入力されているときはここでカメラが初期化されます
void Camera3D1P::TransfarByKey() {

	//スピード変更
	if (input::get_small_alphabet_frame('w')) {
		speed_ += kAcceleration;
	}
	if (input::get_small_alphabet_frame('s')) {
		speed_ -= kAcceleration;
	}

	//スピードラップ
	WrapSpeed();

	//カメラの移動
	x_ += speed_ * cos(angle_w_) * cos(angle_h_);
	z_ += speed_ * sin(angle_w_) * cos(angle_h_);
	y_ += speed_ * sin(angle_h_);

	//q入力時_カメラの初期化
	if (input::get_small_alphabet_frame('q') == 1)
		InitCoordinates();
}

//gluLookAtを設定する
void Camera3D1P::SetGluLookAt() const {
	gluLookAt(x_, y_, z_, gx_, gy_, gz_, ux_, uy_, uz_);
}

//速度をラップする
void Camera3D1P::WrapSpeed() {
	if (speed_ < kMinSpeed)
		speed_ = kMinSpeed;
	if (speed_ > kMaxSpeed)
		speed_ = kMaxSpeed;
}


