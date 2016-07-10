#include "../declaration/GV.h"

namespace {
//隕石の範囲,隕石の出現距離を考慮すること
const Vector3 kBulletRange1(400, 400, 400);
const Vector3 kBulletRange2(-400, -400, -400);
Sound *bullet_to_meteo_se = NULL;
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
	//効果音読み込み
	if (bullet_to_meteo_se == NULL)
		bullet_to_meteo_se = new Sound("sound/bullet_meteo.wav");
}
}

namespace control_bullet {
void Update(const Camera3D3P *camera) {
	//登録
	if (input::get_mouse_left_button_frame() == 1) {
		if ((int) bullet_.size() < kMaxBulletNum) { //最大数を下回っている
			if (player::get_player_state() == player::PLAY) { //プレイ中なら
				//毎フレームの移動角度(3座標)を計算
				Vector3 each_move_angle = camera->GetStateWatchCoordinates()
						- camera->GetStateCoordinates();
				//登録場所を少し上にずらす
				Vector3 wc = camera->GetStateWatchCoordinates();
				wc.y += 2;
				//登録
				Bullet *b = new Bullet(wc, each_move_angle,
						camera->get_speed());
				bullet_.push_back(b);
			}
		}
	}
	//更新
	for (std::vector<Bullet*>::iterator itr_b = bullet_.begin();
			itr_b != bullet_.end(); ++itr_b) {
		(*itr_b)->Move();
	}
	//削除
	//範囲外の時消滅
	for (std::vector<Bullet*>::iterator itr = bullet_.begin();
			itr != bullet_.end();) {
		//プレイヤーの場所を足して考える
		Vector3 range1 = kBulletRange1 + camera->GetStateCoordinates();
		Vector3 range2 = kBulletRange2 + camera->GetStateCoordinates();
		if ((*itr)->IsOutOfRange(range1, range2)) {
			delete (*itr);
			itr = bullet_.erase(itr);
		} else {
			itr++;
		}
	}
	//隕石との当たり判定による削除
	bool is_loop_end = false;
	for (std::vector<Bullet*>::iterator itr_b = bullet_.begin();
			itr_b != bullet_.end();) {
		for (std::vector<Meteo*>::iterator itr_m =
				control_meteo::meteo_.begin();
				itr_m != control_meteo::meteo_.end();) {
			if (uIsCollisionBallAndBall((*itr_b)->get_place(),
					(*itr_b)->get_scale(), (*itr_m)->get_place(),
					(*itr_m)->get_scale(), NULL)) {			//当たっていたら
				//効果音を鳴らす
				bullet_to_meteo_se->SetListener(camera);
				bullet_to_meteo_se->SetSource((*itr_b)->get_place());
				bullet_to_meteo_se->Play();
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
	for (std::vector<Bullet*>::iterator itr = bullet_.begin();
			itr != bullet_.end(); ++itr) {
		(*itr)->Draw();
	}
	//弾数を表示登録
	char string[256];
	sprintf(string, "出現弾数:%d", (int) bullet_.size());
	output_display::Regist(string, uColor4fv_blue, 1);
}
}

namespace control_bullet{
void Fin(){
	//効果音削除
	delete bullet_to_meteo_se;
}
}
