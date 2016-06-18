class Ball;
class Vector3;

class Bullet: public Ball {
public:
	//コンストラクタ,初期化
	Bullet(Vector3 point, Vector3 each_move_angle, double camera_speed);
	void Init();
	//更新
	void Move();
	bool IsOutOfRange(Vector3 v1, Vector3 v2) const;
private:
	float speed_; //スピード
	Vector3 each_move_angle_; //毎フレームの移動角度
};
