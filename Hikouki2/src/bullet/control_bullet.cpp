#include "../declaration/GV.h"

namespace {
//隕石の範囲,隕石の出現距離を考慮すること
const Vector3 kBulletRange1(400, 400, 400);
const Vector3 kBulletRange2(-400, -400, -400);
}

namespace {
std::vector<Bullet*> bullet_;
}

namespace control_bullet {
void Init() {
	//全要素の削除
	for (std::vector<Bullet*>::iterator itr = bullet_.begin();
			itr != bullet_.end();) {
		delete (*itr);
		itr = bullet_.erase(itr);
	}
}
}

namespace control_bullet {
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint) {
	//登録
	//更新
	for (std::vector<Bullet*>::iterator itr = bullet_.begin();
			itr != bullet_.end(); ++itr) {
	}
	//削除
	for (std::vector<Bullet*>::iterator itr = bullet_.begin();
			itr != bullet_.end();) {
		//範囲外の時消滅
		//プレイヤーの場所を足して考える
		Vector3 range1 = kBulletRange1 + camera_place;
		Vector3 range2 = kBulletRange2 + camera_place;
		if ((*itr)->IsOutOfRange(range1, range2)) {
			delete (*itr);
			itr = bullet_.erase(itr);
		} else
			itr++;
	}
}
}

namespace control_bullet {
void Draw() {
	//描画
	for (std::vector<Bullet*>::iterator itr = bullet_.begin();
			itr != bullet_.end(); ++itr) {
		(*itr)->Draw();
	}
	//弾数を表示登録
	char string[256];
	sprintf(string, "bullet:%d", bullet_.size());
	output_display::Regist(string, uColor4fv_blue, 1);
}
}
