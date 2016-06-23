#ifndef OPENGLGAME_DISPLAY_OUTPUTDISPLAY_H_
#define OPENGLGAME_DISPLAY_OUTPUTDISPLAY_H_

namespace output_display {
void Init();
void Regist(const char str[], const float color[], int life = 1);
void Draw();
}

#endif
