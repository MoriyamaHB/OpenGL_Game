class Vector3;

class Ball {

private:
	Vector3 place_;
	bool draw_flag_;
	float scale_;
	float material_[4];
	float sphere_slices_, sphere_stacks_;
protected:
	//移動させる
	void Move(float vx, float vy, float vz);
public:
	//コンストラクタ,初期化
	Ball();
	Ball(float x, float y, float z);
	Ball(Vector3 point);
	void init();

	//設定
	void setDrawFlag(bool tf);
	void setScale(float s);
	void setMaterial(float mat[]);
	void setSphereFineness(float slices, float stacks);

	//描画
	void draw();
};

