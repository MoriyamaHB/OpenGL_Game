#ifndef OPENGLGAME_UTIL_FPS_H_
#define OPENGLGAME_UTIL_FPS_H_

class Fps {
private:
	int GLframe_; //フレーム数
	int GLtimenow_; //経過時間
	int GLtimebase_; //計測開始時間
	int frame_count_; //Updateが呼ばれた回数=開始からのフレーム数
	double fps_; //fps

public:
	Fps();

	//初期化
	void Init();

	//getter
	int get_frame_count() const;

	//更新
	void Update();

	//描画
	void Draw() const;
};

#endif

