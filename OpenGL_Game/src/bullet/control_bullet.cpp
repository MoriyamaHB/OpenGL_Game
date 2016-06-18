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
void Update(Vector3 camera_place, Vector3 camera_viewpoint,
		double camera_speed) {
	//登録
	if (input::get_mouse_left_button_frame() == 1) {
		if (bullet_.size() < kMaxBulletNum) { //最大数を下回っている
			//登録場所を少し上にずらす
			camera_viewpoint.y += 0.5;
			//毎フレームの移動角度(3座標)を計算
			Vector3 each_move_angle = camera_viewpoint - camera_place;
			//登録
			Bullet *b = new Bullet(camera_viewpoint, each_move_angle,
					camera_speed);
			bullet_.push_back(b);
		}
	}
	//更新
	for (std::vector<Bullet*>::iterator itr = bullet_.begin();
			itr != bullet_.end(); ++itr) {
		(*itr)->Move();
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
