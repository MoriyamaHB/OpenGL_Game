#include "../declaration/GV.h"

Score::Score() {
	Init();
}

void Score::Init() {
	score_ = 0;
}

void Score::Update() {
	char string[256];
	sprintf(string, "score: %d", score_);
	output_display::Regist(string, uColor4fv_green, 1);
}

void Score::Draw() const {

}

int Score::get_score() const {
	return score_;
}

void Score::add_score(int add_para) {
	score_ += add_para;
}
