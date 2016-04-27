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
	float x_;
	float y_;
	float z_;
	float gx_;
	float gy_;
	float gz_;
	float ux_;
	float uy_;
	float uz_;
	double angle_w_;
	double angle_h_;
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
	float x_;
	float y_;
	float z_;
	float gx_;
	float gy_;
	float gz_;
	float ux_;
	float uy_;
	float uz_;
	double angle_w_;
	double angle_h_;
	const static double kMinWrapAngleH = -PI / 2 + 0.0001;
	const static double kMaxWrapAngleH = PI / 2 - 0.0001;
};
