class Vector3;

class Ball {

private:
	Vector3 place;
	bool draw_flag;
	float scale;
	float material[4];
	float sphere_slices, sphere_stacks;
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

