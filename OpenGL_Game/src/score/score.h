#ifndef OPENGLGAME_SCORE_SCORE_H_
#define OPENGLGAME_SCORE_SCORE_H_

class Score{
public:
	Score();
	//初期化
	void Init();
	//更新
	void Update();
	void Draw() const;
	//getter,setterなど
	int get_score() const;
	void add_score(int add_para);
private:
	int score_;
};

#endif
