#include "../head/GV.h"

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
	if (fps->GetFrameCount() % 120 == 0) {
		int x = cc_util::GetRandom(-10, 10);
		int y = Meteo::kMaxHeight;
		int z = cc_util::GetRandom(-10, 10);
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
