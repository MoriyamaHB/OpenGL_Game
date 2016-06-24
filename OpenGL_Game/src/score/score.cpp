#include "../declaration/GV.h"

Score::Score() {
	Init();
}

void Score::Init() {
	total_score_ = 0;
}

void Score::Update() {
	//合計スコア計算
	total_score_ = 0;
	for (int i = 0; i < COUNT; i++) {
		total_score_ += each_score_[i];
	}
	//各スコア表示
	char string[256];
	sprintf(string, "total_score: %d", total_score_);
	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "near_meteo_score: %d", each_score_[NEAR_METEO]);
	output_display::Regist(string, uColor4fv_green, 1);
	sprintf(string, "get_target_score: %d", each_score_[GET_TARGET]);
	output_display::Regist(string, uColor4fv_green, 1);
}

void Score::Draw() const {

}

int Score::get_total_score() const {
	return total_score_;
}

void Score::add_score(int add_para, ScoreType st) {
	if (0 <= st && st < COUNT)
		each_score_[st] += add_para;
}
