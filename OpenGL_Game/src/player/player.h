namespace player {
Vector3 get_place(); //playerの場所を返す
float get_scale(); //playerの大きさを返す
void Init(); //初期化
void Update(Vector3 p); //更新
void HitMeteo(); //隕石があたった時に呼び出す
void Draw(); //描画
}
