#ifndef OPENGLGAME_SCORE_SCORE_H_
#define OPENGLGAME_SCORE_SCORE_H_

enum ScoreType {
	GET_TARGET = 0, NEAR_METEO = 1, COUNT
};

class Score {
public:
	Score();
	//初期化
	void Init();
	//更新
	void Update();
	void Draw() const;
	//getter,setterなど
	int get_total_score() const;
	void add_score(int add_para, ScoreType st);
private:
	int total_score_;
	int each_score_[COUNT];
};

#endif
