#include "../declaration/GV.h"

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
	distance_ = 1.5;
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

//カメラ角度をgetする
void Camera3D3P::GetAngle(double *angle_w, double *angle_h) const {
	*angle_w = angle_w_;
	*angle_h = angle_h_;
}

//カメラ速度をgetする
double Camera3D3P::get_speed() const {
	return speed_;
}

//カメラ速度をsetする
void Camera3D3P::set_speed(double sp) {
	speed_ = sp;
	WrapSpeed();
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
	if (input::get_keyboard_frame('w')) {
		speed_ += kAcceleration;
	}
	if (input::get_keyboard_frame('s')) {
		speed_ -= kAcceleration;
	}

	//スピードラップ
	WrapSpeed();

	//カメラの移動
	gx_ -= speed_ * cos(angle_w_) * cos(angle_h_);
	gz_ -= speed_ * sin(angle_w_) * cos(angle_h_);
	gy_ -= speed_ * sin(angle_h_);
}

//カメラの情報を表示（速度)
void Camera3D3P::DisplayInfo() const {
	uDrawString("speed:", 910, 20, uColor4fv_red);
	uSquareFill2D(980, 10, (int) (980 + 200 * (speed_ - kMinSpeed) / kMaxSpeed),
			15, uColor4fv_green);
	uSquareFill2D(980, 10, 980 + 200, 15, uColor4fv_brack);
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
//速度が上がると離れるようにspeed*2をdistance_に足している
	gx_ = (distance_ + speed_ * 2) * cos(angle_w_) * cos(angle_h_) + x_;
	gz_ = (distance_ + speed_ * 2) * sin(angle_w_) * cos(angle_h_) + z_;
	gy_ = (distance_ + speed_ * 2) * sin(angle_h_) + y_;

}

//カメラ座標をキー入力から計算する(3人称視点)
//qが入力されているときはここでカメラが初期化されます
void Camera3D1P::TransfarByKey() {

//スピード変更
	if (input::get_keyboard_frame('w')) {
		speed_ += kAcceleration;
	}
	if (input::get_keyboard_frame('s')) {
		speed_ -= kAcceleration;
	}

//スピードラップ
	WrapSpeed();

//カメラの移動
	x_ += speed_ * cos(angle_w_) * cos(angle_h_);
	z_ += speed_ * sin(angle_w_) * cos(angle_h_);
	y_ += speed_ * sin(angle_h_);

//q入力時_カメラの初期化
	if (input::get_keyboard_frame('q') == 1)
		InitCoordinates();
}
