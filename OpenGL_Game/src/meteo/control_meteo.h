#ifndef OPENGLGAME_METEO_CONTROLMETEO_H_
#define OPENGLGAME_METEO_CONTROLMETEO_H_

class Fps;
class Meteo;

namespace control_meteo {

const int kMaxMeteoNum = 1000; //隕石の最大出現数
const double kAddScoreMaxDistance = 10; //スコアを加算するプレイヤーと隕石の最大距離
const int kAddScoreFactor = 20;

//実際に隕石を格納するデータ構造
//当たり判定に困り仕方なくグローバルで宣言
extern std::vector<Meteo*> meteo_;

void Init();
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint);
void Draw();
}

#endif
