#ifndef OPENGLGAME_UTIL_SOLID_H_
#define OPENGLGAME_UTIL_SOLID_H_

class Vector3;

class Solid {
protected:
	Vector3 place_;
	bool can_draw_;
	float scale_;
	float material_[4];
public:
	//コンストラクタ,初期化
	Solid();
	Solid(float x, float y, float z);
	Solid(Vector3 point);
	virtual ~Solid() {
	}
	void Init();

	//設定
	void set_draw_flag(bool tf);
	void set_scale(float s);
	void set_material(const float mat[]);

	//移動させる
	void MoveDiff(Vector3 v);
	void Move(Vector3 v);

	//get
	Vector3 get_place() const;
	float get_scale() const;
	bool get_draw_flag() const;

	//描画
	virtual void Draw() const=0;
};

#endif
