#ifndef OPENGLGAME_METEO_METEO_H_
#define OPENGLGAME_METEO_METEO_H_

class Ball;
class Vector3;

class Meteo: public Ball {
public:
	//コンストラクタ,初期化
	Meteo(Vector3 point, Vector3 each_move_angle);
	void Init();
	//更新
	void Move();
	bool IsOutOfRange(Vector3 v1, Vector3 v2) const;
	//描画
	void Draw() const;
	//定数
	constexpr const static float kAppearanceDistance = 150; //プレイヤーと隕石の出現距離,削除距離を考慮すること
private:
	//each_move_angle * speedずつ各座標軸で移動を行います
	float speed_; //移動するスピード
	Vector3 each_move_angle_; //毎フレームの移動角度
};

#endif
