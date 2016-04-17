class Vector3;

//3人称 & 自由飛行のカメラ移動計算を行います
class Camera3D3P {
public:
	Camera3D3P();

	//初期化
	void initCoordinates();

	//getter
	Vector3 getStateWatchCoordinates() const;

	//カメラ移動
	void transfarAndRotateByMouse();
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
	const static double kMinWrapAngleH = -PI / 2 + 0.0001;
	const static double kMaxWrapAngleH = PI / 2 - 0.0001;
};

//1人称 & 自由飛行のカメラ移動計算を行います
class Camera3D1P {
public:
	Camera3D1P();

	//初期化
	void initCoordinates();

	//getter
	Vector3 getStateWatchCoordinates() const;

	//カメラ移動
	void transfarAndRotateByMouse();
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
	const static double kMinWrapAngleH = -PI / 2 + 0.0001;
	const static double kMaxWrapAngleH = PI / 2 - 0.0001;
};
