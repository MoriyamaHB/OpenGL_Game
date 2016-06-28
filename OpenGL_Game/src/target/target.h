#ifndef OPENGLGAME_TARGET_TARGET_H_
#define OPENGLGAME_TARGET_TARGET_H_

class Square;
class Vector3;
class Fps;

class Target: public Square {
public:
	//コンストラクタ,初期化
	Target(Vector3 point, Vector3 each_move_angle);
	void Init();
	//更新
	void Move();
	bool IsOutOfRange(Vector3 v1, Vector3 v2) const;
	//描画
	void Draw() const;
	//定数
	constexpr const static float kAppearanceDistance = 150; //プレイヤーとターゲットの出現距離,削除距離を考慮すること
private:
	//each_move_angle * speedずつ各座標軸で移動を行います
	float speed_; //移動するスピード
	Vector3 each_move_angle_; //毎フレームの移動角度
};

namespace control_target {
const int kMaxTargetNum = 1000;
const int kGetTargetScoreFactor = 100;

void Init();
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint);
void Draw();
}

#endif

