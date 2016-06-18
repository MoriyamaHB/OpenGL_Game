namespace control_bullet {
const int kMaxBulletNum = 1000;

void Init();
void Update(Vector3 camera_place, Vector3 camera_viewpoint,
		double camera_speed);
void Draw();
}
