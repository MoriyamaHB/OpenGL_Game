#include "../declaration/GV.h"

Score::Score() {
	Init();
}

void Score::Init() {
	total_score_ = 0;
	memset(each_score_, 0, sizeof(each_score_));
}

void Score::Update() {
	//合計スコア計算
	total_score_ = 0;
	for (int i = 0; i < kCount; i++) {
		total_score_ += each_score_[i];
	}
	//各スコア表示
	char string[256];
	sprintf(string, "合計スコア: %d", total_score_);
	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "かすりスコア: %d", each_score_[kNearMeteo]);
	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "ターゲット獲得スコア: %d", each_score_[kGetTarget]);
	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "球破壊スコア: %d", each_score_[kDestructMeteo]);
	output_display::Regist(string, uColor4fv_green, 1);
}

void Score::Draw() const {

}

int Score::get_total_score() const {
	return total_score_;
}

int Score::get_score(Score::ScoreType st) const {
	if (0 <= st && st < kCount)
		return each_score_[st];
	uErrorOut(__FILE__, __func__, __LINE__, "存在しないスコアです");
	return -1;
}

void Score::set_score(int set_para, Score::ScoreType st) {
	if (0 <= st && st < kCount)
		each_score_[st] = set_para;
	else
		uErrorOut(__FILE__, __func__, __LINE__, "存在しないスコアです");
}

void Score::add_score(int add_para, Score::ScoreType st) {
	if (0 <= st && st < kCount)
		each_score_[st] += add_para;
	else
		uErrorOut(__FILE__, __func__, __LINE__, "存在しないスコアです");
}
