class Vector3;

class Camera3D3P {
public:

	//デフォルトコンストラクタ
	Camera3D3P();

	//カメラ座標を初期化する
	void initCoordinates();

	//カメラ視点座標を取得する
	Vector3 getStateWatchCoordinates() const;

	//カメラ座標をマウスの移動から計算する(3人称視点)
	void transfarAndRotateByMouse();

	//カメラ座標をキー入力から計算する(3人称視点)
	void transfarByKey();

	//gluLookAtを設定する
	void setGluLookAt() const;

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
	double angle_w;
	double angle_h;
	const static double min_wrap_angle_h = -PI / 2 + 0.0001;
	const static double max_wrap_angle_h = PI / 2 - 0.0001;
};

class Camera3D1P {
public:

	//デフォルトコンストラクタ
	Camera3D1P();

	//カメラ座標を初期化する
	void initCoordinates();

	//カメラ視点座標を取得する
	Vector3 getStateWatchCoordinates() const;

	//カメラ座標をマウスの移動から計算する(3人称視点)
	void transfarAndRotateByMouse();

	//カメラ座標をキー入力から計算する(3人称視点)
	void transfarByKey();

	//gluLookAtを設定する
	void setGluLookAt() const;

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
	double angle_w;
	double angle_h;
	const static double min_wrap_angle_h = -PI / 2 + 0.0001;
	const static double max_wrap_angle_h = PI / 2 - 0.0001;
};
