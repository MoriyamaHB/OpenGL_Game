#include "../declaration/GV.h"

Fps::Fps() {
	GLframe = 0;
	GLtimenow = 0;
	GLtimebase = 0;
	frame_count = 0;
	fps = 0;
}

void Fps::Init() {
	GLframe = 0;
	GLtimenow = 0;
	GLtimebase = 0;
	frame_count = 0;
	fps = 0;
}

int Fps::GetFrameCount() const {
	return frame_count;
}

//計測したいスレッドにある関数から毎フレーム呼び出してください
void Fps::Update() {
	GLframe++; //フレーム数を＋１
	frame_count++; //フレームカウント
	GLtimenow = glutGet(GLUT_ELAPSED_TIME); //経過時間を取得
	if (GLtimenow - GLtimebase > 1000) { //１秒以上たったらfpsを出力
		fps = GLframe * 1000.0 / (GLtimenow - GLtimebase);
		GLtimebase = GLtimenow; //基準時間を設定
		GLframe = 0; //フレーム数をリセット
	}
}

//x,yの位置に計測したfpsの描画を登録します
void Fps::Draw(int x, int y) const {
	char str[48];
	sprintf(str, "fps:%.2f", fps);
	output_display::Regist(str, uColor4fv_blue);
}