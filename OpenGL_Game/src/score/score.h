#ifndef OPENGLGAME_SCORE_SCORE_H_
#define OPENGLGAME_SCORE_SCORE_H_

class Score {
public:
	enum ScoreType {
		kGetTarget = 0, kNearMeteo = 1, kCount
	};

	Score();
	//初期化
	void Init();
	//更新
	void Update();
	void Draw() const;
	//getter,setterなど
	int get_total_score() const;
	void add_score(int add_para, Score::ScoreType st);
private:
	int total_score_;
	int each_score_[kCount];
};

#endif
