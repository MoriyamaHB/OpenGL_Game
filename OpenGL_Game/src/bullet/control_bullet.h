#ifndef OPENGLGAME_BULLET_CONTROLBULLET_H_
#define OPENGLGAME_BULLET_CONTROLBULLET_H_

class Camera3D3P;

namespace control_bullet {
const int kMaxBulletNum = 1000;
const double kDestructMeteoScoreFactor = 20;

void Init();
void Update(const Camera3D3P *camera);
void Draw();
void Fin();
}

#endif
