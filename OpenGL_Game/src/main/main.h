#ifndef OPENGLGAME_MAIN_MAIN_H_
#define OPENGLGAME_MAIN_MAIN_H_

class Score;

namespace opengl_game_main {
enum MainState {
	kProjectIni, kStartIni, kStart, kGameIni, kGame
};
enum MainBgm {
	kGameBgm = 0, MainBgmNum
};
extern Score score;
void DisplayFunc(void);
void Resize(int w, int h);
void Timer(int value);
}

#endif
