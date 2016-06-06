class OutputDisplay;

class Fps {
private:
	int GLframe; //フレーム数
	int GLtimenow; //経過時間
	int GLtimebase; //計測開始時間
	int frame_count; //Updateが呼ばれた回数=開始からのフレーム数
	double fps; //fps

public:
	Fps();

	//getter
	int GetFrameCount() const;

	//更新
	void Update();

	//描画
	void Draw(int x, int y, OutputDisplay &output) const;
};

