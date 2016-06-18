#include "../declaration/GV.h"

namespace {
//隕石の範囲,隕石の出現距離を考慮すること
const Vector3 kMeteoRange1(400, 400, 400);
const Vector3 kMeteoRange2(-400, -400, -400);
}

namespace {
std::vector<Meteo*> meteo_;
}

namespace control_meteo {
void Init() {

}
}

namespace control_meteo {
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint) {
	//登録
	if (fps->GetFrameCount() % 3 == 0) {
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
		meteo_.push_back(m);
	}
	//更新
	for (std::vector<Meteo*>::iterator itr = meteo_.begin();
			itr != meteo_.end(); ++itr) {
		(*itr)->Fall();
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
}
}
