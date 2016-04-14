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
	}

	//更新
	void update() {
		GLframe++; //フレーム数を＋１
		GLtimenow = glutGet(GLUT_ELAPSED_TIME); //経過時間を取得

		if (GLtimenow - GLtimebase > 1000){ //１秒以上たったらfpsを出力
			fps = GLframe * 1000.0 / (GLtimenow - GLtimebase);
			GLtimebase = GLtimenow; //基準時間を設定
			GLframe = 0; //フレーム数をリセット
		}
	}

	//描画
	void draw(int x, int y) {
		char str[48];
		sprintf(str, "%.2f", fps);
		uDrawString(str, x, y, uColor4fv_red);
	}
};

