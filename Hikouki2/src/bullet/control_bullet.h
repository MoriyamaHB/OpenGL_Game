namespace control_bullet {
const int kMaxBulletNum = 1000;

void Init();
void Update(Fps *fps, Vector3 camera_place, Vector3 camera_viewpoint);
void Draw();
}
