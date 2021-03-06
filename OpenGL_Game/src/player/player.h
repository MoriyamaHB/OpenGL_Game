#ifndef OPENGLGAME_PLAYER_PLAYER_H_
#define OPENGLGAME_PLAYER_PLAYER_H_

namespace player {
enum PlayerState {
	kPlay, kDie, kFin
};
Vector3 get_place(); //playerの場所を返す
float get_scale(); //playerの大きさを返す
PlayerState get_player_state();
void Init(Camera3D3P *c); //初期化
int Update(Vector3 p, int now_cnt); //更新
void HitMeteo(); //隕石があたった時に呼び出す
void SetPlayerStateFin(); //プレイヤーをゲーム終了に設定
void HitTarget(); //ターゲットがあたった時に呼び出す
void Draw(); //描画
void Fin(); //終了処理
}

#endif
