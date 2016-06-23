#include "../declaration/GV.h"

namespace {
//隕石の範囲,隕石の出現距離を考慮すること
const Vector3 kMeteoRange1(400, 400, 400);
const Vector3 kMeteoRange2(-400, -400, -400);
//実際に隕石を格納するデータ構造
std::vector<Meteo*> meteo_;
}

namespace control_meteo {
std::vector<CollisionBall*> collision_meteo_; //当たり判定用のグローバルデータ
}

namespace control_meteo {
void Init() {
	//全要素の削除
	for (std::vector<Meteo*>::iterator itr = meteo_.begin();
			itr != meteo_.end();) {
		delete (*itr);
		itr = meteo_.erase(itr);
	}
}
}

namespace control_meteo {
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint) {
	//登録
	if (fps->GetFrameCount() % 3 == 0) { //登録フレームである
		if ((int) meteo_.size() < kMaxMeteoNum) { //最大数を下回っている
			//登録場所を計算
			//視点の先の場所を計算
			Vector3 register_place = 100 * (camera_viewpoint - camera_place)
					+ camera_place;
			//乱数によりバラけさせる
			register_place.x += cc_util::GetRandom(-30, 30);
			register_place.y += cc_util::GetRandom(-30, 30);
			register_place.z += cc_util::GetRandom(-30, 30);
			//毎フレームの移動角度(3座標)を計算
			Vector3 each_move_angle = camera_place - camera_viewpoint;
			//登録
			Meteo *m = new Meteo(register_place, each_move_angle);
			//CollisionBall *cb = new CollisionBall { register_place,
			//m->get_scale() };
			meteo_.push_back(m);
			//collision_meteo_.push_back(cb);
		}
	}

	//更新
	for (std::vector<Meteo*>::iterator itr = meteo_.begin();
			itr != meteo_.end(); ++itr) {
		//プレイヤーへの当たり判定
		if (player::get_player_state() == PLAY) {			//プレイ中なら
			if (uIsCollisionBallAndBall((*itr)->get_place(),
					(*itr)->get_scale(), player::get_place(),
					player::get_scale())) {
				player::HitMeteo();
			}
		}
		//移動
		(*itr)->Move();
	}
	//削除
	//eraseを使うため場合分けして次のitrを決める
	//for文でitr++すると削除した次の要素に移動できない可能性があるのでeraseの戻り値を使う
	for (std::vector<Meteo*>::iterator itr = meteo_.begin();
			itr != meteo_.end();) {
		//範囲外の時消滅
		//プレイヤーの場所を足して考える
		Vector3 range1 = kMeteoRange1 + camera_place;
		Vector3 range2 = kMeteoRange2 + camera_place;
		if ((*itr)->IsOutOfRange(range1, range2)) {
			delete (*itr);
			itr = meteo_.erase(itr);
		} else
			itr++;
	}
}
}

namespace control_meteo {
void Draw() {
	//描画
	for (std::vector<Meteo*>::iterator itr = meteo_.begin();
			itr != meteo_.end(); ++itr) {
		(*itr)->Draw();
	}
	//隕石数を表示登録
	output_display::Regist(uPrintfString("meteo:%d", meteo_.size()),
			uColor4fv_blue, 1);
}
}
