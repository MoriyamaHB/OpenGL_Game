class Ball;
class Vector3;

class Meteo: public Ball {
public:
	//コンストラクタ,初期化
	Meteo();
	Meteo(float x, float y, float z);
	Meteo(Vector3 point);
	void Init();
	//移動
	void Fall();
private:
	float fall_speed_;
};
