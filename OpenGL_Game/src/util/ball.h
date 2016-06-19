class Vector3;

class Ball {
protected:
	Vector3 place_;
	bool can_draw_;
	float scale_;
	float material_[4];
	float sphere_slices_, sphere_stacks_;
	//移動させる
	void Move(float vx, float vy, float vz);
public:
	//コンストラクタ,初期化
	Ball();
	Ball(float x, float y, float z);
	Ball(Vector3 point);
	void Init();

	//設定
	void set_draw_flag(bool tf);
	void set_scale(float s);
	void set_material(float mat[]);
	void SetSphereFineness(float slices, float stacks);

	//get
	Vector3 get_place_();
	float get_scale_();

	//描画
	void Draw() const;
};

