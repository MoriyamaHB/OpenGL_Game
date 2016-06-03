class Ball;
class Vector3;

class Meteo: public Ball {
public:
	//コンストラクタ,初期化
	Meteo();
	Meteo(float x, float y, float z);
	Meteo(Vector3 point);
	void Init();
	//更新
	void Fall();
	bool IsOutOfRange(Vector3 v1, Vector3 v2);
	//描画
	void Draw();
	//定数
	const static float kAppearanceHeight = 70; //隕石の出現高度
private:
	float fall_speed_;
};
