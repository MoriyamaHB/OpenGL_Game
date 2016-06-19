class Square: public Solid {
public:
	//コンストラクタ,初期化
	Square();
	Square(float x, float y, float z);
	Square(Vector3 point);

	//描画
	void Draw() const;
};
