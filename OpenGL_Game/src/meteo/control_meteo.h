#ifndef OPENGLGAME_METEO_CONTROLMETEO_H_
#define OPENGLGAME_METEO_CONTROLMETEO_H_

class Fps;

namespace control_meteo {

const int kMaxMeteoNum = 1000;
extern std::vector<CollisionBall*> collision_meteo_; //当たり判定用のグローバルデータ

void Init();
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint);
void Draw();
}

#endif
