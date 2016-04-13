class Camera3D3P {
public:

	//デフォルトコンストラクタ
	Camera3D3P() {
		initCoordinates();
	}

	//カメラ座標を初期化する
	void initCoordinates() {
		gx = 0;
		gy = 1;
		gz = 0;
		x = 0;
		y = 5;
		z = 0;
		ux = 0;
		uy = 1;
		uz = 0;
		angle_h = PI / 2;
		angle_w = 0;
	}

	//カメラ視点座標を取得する
	Vector3 getStateWatchCoordinates() const {
		return Vector3(gx, gy, gz);
	}

	//カメラ座標をマウスの移動から計算する(3人称視点)
	void transfarAndRotateByMouse() {

		//マウス移動の取得
		int mouse_dx, mouse_dy;
		getMouseMotionAndInit(&mouse_dx, &mouse_dy);

		//マウスの動きをカメラ角度に変換
		angle_h += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
		angle_w += ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

		//カメラ角度を視点位置に反映
		x = cos(angle_h) * cos(angle_w) + gx;
		z = sin(angle_h) * cos(angle_w) + gz;
		y = sin(angle_w) + gy;

		//yの範囲を限定
		if (y < 0.05)
			y = 0.05;

	}

	//カメラ座標をキー入力から計算する(3人称視点)
	void transfarByKey() {

		//カメラの移動
		if (getStateKeyOfSmallAlphabet('w') == 1) {
			gx -= CAMERA_SP * cos(angle_h) * cos(angle_w);
			gz -= CAMERA_SP * sin(angle_h) * cos(angle_w);
			gy -= CAMERA_SP * sin(angle_w);
		}
		if (getStateKeyOfSmallAlphabet('s') == 1) {
			gx += CAMERA_SP * cos(angle_h) * cos(angle_w);
			gz += CAMERA_SP * sin(angle_h) * cos(angle_w);
			gy += CAMERA_SP * sin(angle_w);
		}
		if (getStateKeyOfSmallAlphabet('a') == 1) {
			gx -= CAMERA_SP * cos(angle_h - PI / 2) * cos(angle_w);
			gz -= CAMERA_SP * sin(angle_h - PI / 2) * cos(angle_w);
		}
		if (getStateKeyOfSmallAlphabet('d') == 1) {
			gx -= CAMERA_SP * cos(angle_h + PI / 2) * cos(angle_w);
			gz -= CAMERA_SP * sin(angle_h + PI / 2) * cos(angle_w);
		}

		//yの範囲を限定
		if (gy < 0)
			gy = 0;

		//q入力時_カメラの初期化
		if (getStateKeyOfSmallAlphabet('q') == 1)
			initCoordinates();
	}

	//gluLookAtを設定する
	void setGluLookAt() const {
		gluLookAt(x, y, z, gx, gy, gz, ux, uy, uz);
	}

private:
	float x;
	float y;
	float z;
	float gx;
	float gy;
	float gz;
	float ux;
	float uy;
	float uz;
	double angle_h;
	double angle_w;
};

class Camera3D1P {
public:

	//デフォルトコンストラクタ
	Camera3D1P() {
		initCoordinates();
	}

	//カメラ座標を初期化する
	void initCoordinates() {
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
	Vector3 getStateCoordinates() const {
		return Vector3(x, y, z);
	}

	//カメラ座標をマウスの移動から計算する(3人称視点)
	void transfarAndRotateByMouse() {

		//マウス移動の取得
		int mouse_dx, mouse_dy;
		getMouseMotionAndInit(&mouse_dx, &mouse_dy);

		//マウスの動きをカメラ角度に変換
		angle_h += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
		angle_w -= ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

		//カメラ角度を視点位置に反映
		gx = cos(angle_h) * cos(angle_w) + x;
		gz = sin(angle_h) * cos(angle_w) + z;
		gy = sin(angle_w) + y;

		//yの範囲を限定
		if (gy < -0.9)
			gy = -0.9;

	}

	//カメラ座標をキー入力から計算する(3人称視点)
	void transfarByKey() {

		//カメラの移動
		if (getStateKeyOfSmallAlphabet('w') == 1) {
			x += CAMERA_SP * cos(angle_h) * cos(angle_w);
			z += CAMERA_SP * sin(angle_h) * cos(angle_w);
			y += CAMERA_SP * sin(angle_w);
		}
		if (getStateKeyOfSmallAlphabet('s') == 1) {
			x -= CAMERA_SP * cos(angle_h) * cos(angle_w);
			z -= CAMERA_SP * sin(angle_h) * cos(angle_w);
			y -= CAMERA_SP * sin(angle_w);
		}
		if (getStateKeyOfSmallAlphabet('a') == 1) {
			x += CAMERA_SP * cos(angle_h - PI / 2) * cos(angle_w);
			z += CAMERA_SP * sin(angle_h - PI / 2) * cos(angle_w);
		}
		if (getStateKeyOfSmallAlphabet('d') == 1) {
			x += CAMERA_SP * cos(angle_h + PI / 2) * cos(angle_w);
			z += CAMERA_SP * sin(angle_h + PI / 2) * cos(angle_w);
		}

		//yの範囲を限定
		if (y < 0.1)
			y = 0.1;

		//q入力時_カメラの初期化
		if (getStateKeyOfSmallAlphabet('q') == 1)
			initCoordinates();
	}

	//gluLookAtを設定する
	void setGluLookAt() const {
		gluLookAt(x, y, z, gx, gy, gz, ux, uy, uz);
	}

private:
	float x;
	float y;
	float z;
	float gx;
	float gy;
	float gz;
	float ux;
	float uy;
	float uz;
	double angle_h;
	double angle_w;
};
