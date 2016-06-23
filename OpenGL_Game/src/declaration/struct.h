//ディスプレイに使う構造体
typedef struct {
	char str[128];
	float color[4];
	int life; //描画回数
	int flag;
} OutputItem;

//当たり判定の球
typedef struct {
	Vector3 place;
	float radius;
} CollisionBall;
