class Ball;
class Vector3;

class Bullet: public Ball {
public:
	//コンストラクタ,初期化
	Bullet(float ang_w, float ang_h);
	Bullet(float x, float y, float z, float ang_w, float ang_h);
	Bullet(Vector3 point, float ang_w, float ang_h);
	void Init(float ang_w, float ang_h);
	//更新
	void Move();
	bool IsOutOfRange(Vector3 v1, Vector3 v2) const;
private:
	float speed_;
	float angle_w_;
	float angle_h_;
};
