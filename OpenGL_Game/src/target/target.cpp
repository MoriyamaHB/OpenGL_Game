#include "../declaration/GV.h"

////////////////////////    コンストラクタ,初期化    ////////////////////////

//each_move_angle * speedずつ各座標軸で移動を行います
Target::Target(Vector3 point, Vector3 each_move_angle) :
		Square() {
	Init();
	Square::MoveDiff(point);
	each_move_angle_ = each_move_angle;
}

void Target::Init() {
	//フラグ
	set_draw_flag(true);
	//大きさ
	int s = cc_util::GetRandom(6, 18);
	set_scale(s);
	//スピード
	speed_ = cc_util::GetRandom(1, 50) / 100.0;
	//マテリアル
	float r = cc_util::GetRandom(0, 1000) / 1000.0;
	float g = cc_util::GetRandom(0, 1000) / 1000.0;
	float b = cc_util::GetRandom(0, 1000) / 1000.0;
	float mate[4] = { r, g, b, 1.0 };
	set_material(mate);
}

////////////////////////    更新    ////////////////////////

//移動を行う
void Target::Move() {
	Vector3 move_diff = speed_ * each_move_angle_;
	Square::MoveDiff(move_diff);
}

//ターゲットが範囲外かどうか
bool Target::IsOutOfRange(Vector3 v1, Vector3 v2) const {
	if (uOutOfRange(place_, v1, v2))
		return true;
	return false;
}

////////////////////////    描画    ////////////////////////
void Target::Draw() const {
	//Ballクラスを描画
	Square::Draw();
}

//============================== control_target ========================================
namespace {
//隕石の範囲,隕石の出現距離を考慮すること
const Vector3 kMeteoRange1(400, 400, 400);
const Vector3 kMeteoRange2(-400, -400, -400);
}

namespace {
std::vector<Target*> target_;
}

namespace control_target {
void Init() {
	//全要素の削除
	for (std::vector<Target*>::iterator itr = target_.begin();
			itr != target_.end();) {
		delete (*itr);
		itr = target_.erase(itr);
	}
}
}

namespace control_target {
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint) {
	//登録
	if (fps->GetFrameCount() % 45 == 0) { //登録フレームである
		if ((int) target_.size() < kMaxTargetNum) { //最大数を下回っている
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
			Target *m = new Target(register_place, each_move_angle);
			target_.push_back(m);
		}
	}

	//更新
	for (std::vector<Target*>::iterator itr = target_.begin();
			itr != target_.end(); ++itr) {
		//プレイヤーへの当たり判定
		if (player::get_player_state() == PLAY) {			//プレイ中なら
			if (uIsCollisionBallAndBall((*itr)->get_place(),
					(*itr)->get_scale(), player::get_place(),
					player::get_scale())) {
				player::HitTarget();
				delete (*itr);
				itr = target_.erase(itr);
				break;
			}
		}
		//移動
		(*itr)->Move();
	}
	//削除
	for (std::vector<Target*>::iterator itr = target_.begin();
			itr != target_.end();) {
		//範囲外の時消滅
		//プレイヤーの場所を足して考える
		Vector3 range1 = kMeteoRange1 + camera_place;
		Vector3 range2 = kMeteoRange2 + camera_place;
		if ((*itr)->IsOutOfRange(range1, range2)) {
			delete (*itr);
			itr = target_.erase(itr);
		} else
			itr++;
	}
}
}

namespace control_target {
void Draw() {
	//描画
	for (std::vector<Target*>::iterator itr = target_.begin();
			itr != target_.end(); ++itr) {
		(*itr)->Draw();
	}
	//隕石数を表示登録
	char string[256];
	sprintf(string, "target:%d", target_.size());
	output_display::Regist(string, uColor4fv_blue, 1);
}
}

