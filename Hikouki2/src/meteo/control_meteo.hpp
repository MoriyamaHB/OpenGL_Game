class Fps;

namespace control_meteo {
const static int kMaxMeteoNum = 10000;

void Init();
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint);
void Draw();
}
