class Vector3;

class Ball: public Solid {
protected:
	float sphere_slices_, sphere_stacks_;
public:
	//コンストラクタ,初期化
	Ball();
	Ball(float x, float y, float z);
	Ball(Vector3 point);
	void Init();

	//設定
	void SetSphereFineness(float slices, float stacks);

	//描画
	void Draw() const;
};

