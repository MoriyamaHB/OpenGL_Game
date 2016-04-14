class Fps {
private:
	int GLframe; //フレーム数
	int GLtimenow; //経過時間
	int GLtimebase; //計測開始時間
	double fps; //fps

public:

	Fps() {
		GLframe = 0;
		GLtimenow = 0;
		GLtimebase = 0;
		fps = 0;
	}

	//更新
	void update();

	//描画
	void draw(int x, int y);
};
