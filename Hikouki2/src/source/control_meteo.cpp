#include "../head/GV.h"

namespace {
//隕石の範囲
const Vector3 kMeteoRange1(200, 200, 200);
const Vector3 kMeteoRange2(-200, -10, -200);
}

namespace {
std::vector<Meteo*> meteo_;
}

namespace control_meteo {
void Init() {

}
}

namespace control_meteo {
void Update(Fps *fps) {
	//登録
	if (fps->GetFrameCount() % 10 == 0) {
		int x = cc_util::GetRandom(-20, 20);
		int y = Meteo::kAppearanceHeight;
		int z = cc_util::GetRandom(-20, 20);
		int s = cc_util::GetRandom(1, 5);
		float speed = cc_util::GetRandom(1, 50) / 100.0;
		Meteo *m = new Meteo(x, y, z);
		m->set_draw_flag(true);
		m->set_scale(s);
		m->set_fall_speed(speed);
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
		if ((*itr)->IsOutOfRange(kMeteoRange1, kMeteoRange2)) {
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
