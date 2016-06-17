#include "../head/GV.h"

namespace {
//隕石の範囲,隕石の出現距離を考慮すること
const Vector3 kMeteoRange1(200, 200, 200);
const Vector3 kMeteoRange2(-200, -200, -200);
}

namespace {
std::vector<Meteo*> meteo_;
}

namespace control_meteo {
void Init() {

}
}

namespace control_meteo {
void Update(Fps *fps, Vector3 player_place) {
	//登録
	if (fps->GetFrameCount() % 3 == 0) {
		Meteo *m = new Meteo(player_place);
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
		Vector3 range1 = kMeteoRange1 + player_place;
		Vector3 range2 = kMeteoRange2 + player_place;
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
