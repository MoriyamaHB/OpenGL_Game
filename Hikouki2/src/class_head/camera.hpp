class Vector3;
class OutputDisplay;

//3人称 & 自由飛行のカメラ移動計算を行います
class Camera3D3P {
public:
	Camera3D3P();

	//初期化
	void InitCoordinates();

	//getter
	Vector3 GetStateWatchCoordinates() const;
	Vector3 GetStateCoordinates() const;

	//カメラ移動
	void TransfarAndRotateByMouse();
	void TransfarByKey();

	//カメラの情報を表示（速度)
	void DisplayInfo(OutputDisplay &disp) const;

	//gluLookAtを設定する
	void SetGluLookAt() const;

protected:
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
	double speed_;
	double distance_;
	//カメラの角度限度
	const static double kMinWrapAngleH = -PI / 2 + 0.0001;
	const static double kMaxWrapAngleH = PI / 2 - 0.0001;
	//カメラの速度関連
	const static double kAcceleration = 0.01; //加速度
	const static double kMaxSpeed = 1; //最高速度
	const static double kMinSpeed = 0; //最低速度

	//速度をラップする
	void WrapSpeed();
};

//1人称 & 自由飛行のカメラ移動計算を行います
class Camera3D1P: public Camera3D3P {
public:
	//カメラ移動
	void TransfarAndRotateByMouse();
	void TransfarByKey();

private:
};
