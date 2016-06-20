enum PlayerState {
	PLAY, DIE
};

namespace player {
Vector3 get_place(); //playerの場所を返す
float get_scale(); //playerの大きさを返す
PlayerState get_player_state();
void Init(); //初期化
void Update(Vector3 p, int now_cnt); //更新
void HitMeteo(); //隕石があたった時に呼び出す
void HitTarget(); //ターゲットがあたった時に呼び出す
void Draw(); //描画
}