class Camera {
public:

	//デフォルトコンストラクタ
	Camera(){
		initCoordinates();
	}
	//カメラ座標を初期化する
	void initCoordinates();

	//カメラ座標を取得する
	Vector3 getStateCoordinates() const;

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
	double angle_h;
	double angle_w;
};
