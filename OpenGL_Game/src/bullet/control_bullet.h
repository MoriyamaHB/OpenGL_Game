#ifndef OPENGLGAME_BULLET_CONTROLBULLET_H_
#define OPENGLGAME_BULLET_CONTROLBULLET_H_

namespace control_bullet {
const int kMaxBulletNum = 1000;
const double kDestructMeteoScoreFactor = 20;

void Init();
void Update(Vector3 camera_place, Vector3 camera_viewpoint,
		double camera_speed);
void Draw();
}

#endif
