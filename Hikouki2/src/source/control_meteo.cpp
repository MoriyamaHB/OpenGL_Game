#include "../head/GV.h"

namespace {
std::vector<Meteo*> meteo_;
}

namespace control_meteo {
void Init() {

}
}

namespace control_meteo {
void Update() {
	printf("%d\n", cc_util::GetRandom(0, 100));
}
}
