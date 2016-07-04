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
	for (auto itr = bullet_.begin(); itr != bullet_.end();) {
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
		if ((int) bullet_.size() < kMaxBulletNum) { //最大数を下回っている
			if (player::get_player_state() == player::PLAY) { //プレイ中なら
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
	}
	//更新
	for (auto itr_b = bullet_.begin(); itr_b != bullet_.end(); ++itr_b) {
		(*itr_b)->Move();
	}
	//削除
	//範囲外の時消滅
	for (auto itr = bullet_.begin(); itr != bullet_.end();) {
		//プレイヤーの場所を足して考える
		Vector3 range1 = kBulletRange1 + camera_place;
		Vector3 range2 = kBulletRange2 + camera_place;
		if ((*itr)->IsOutOfRange(range1, range2)) {
			delete (*itr);
			itr = bullet_.erase(itr);
		} else {
			itr++;
		}
	}
	//隕石との当たり判定による削除
	bool is_loop_end = false;
	for (auto itr_b = bullet_.begin(); itr_b != bullet_.end();) {
		for (auto itr_m = control_meteo::meteo_.begin();
				itr_m != control_meteo::meteo_.end();) {
			if (uIsCollisionBallAndBall((*itr_b)->get_place(),
					(*itr_b)->get_scale(), (*itr_m)->get_place(),
					(*itr_m)->get_scale(), NULL)) {			//当たっていたら
				//削除
				opengl_game_main::score.add_score(
						(int) (kDestructMeteoScoreFactor * (*itr_m)->get_scale()),
						Score::kDestructMeteo);	//スコア加算
				delete (*itr_m);
				delete (*itr_b);
				itr_m = control_meteo::meteo_.erase(itr_m);
				itr_b = bullet_.erase(itr_b);
				is_loop_end = true;
				break;
			} else {
				itr_m++;
			}
		}
		if (is_loop_end) {
			is_loop_end = false;
			break;
		}
		itr_b++;
	}
}
}

namespace control_bullet {
void Draw() {
//描画
	for (auto itr = bullet_.begin(); itr != bullet_.end(); ++itr) {
		(*itr)->Draw();
	}
//弾数を表示登録
	char string[256];
	sprintf(string, "出現弾数:%d", (int)bullet_.size());
	output_display::Regist(string, uColor4fv_blue, 1);
}
}
