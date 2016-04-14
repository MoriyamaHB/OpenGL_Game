#include "../head/GV.h"

//更新
void Fps::update() {
	GLframe++; //フレーム数を＋１
	GLtimenow = glutGet(GLUT_ELAPSED_TIME); //経過時間を取得

	if (GLtimenow - GLtimebase > 1000) { //１秒以上たったらfpsを出力
		fps = GLframe * 1000.0 / (GLtimenow - GLtimebase);
		GLtimebase = GLtimenow; //基準時間を設定
		GLframe = 0; //フレーム数をリセット
	}
}

//描画
void Fps::draw(int x, int y) {
	char str[48];
	sprintf(str, "%.2f", fps);
	out_disp.regist(str, uColor4fv_blue);
}
