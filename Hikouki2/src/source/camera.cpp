#include"../head/GV.h"

//カメラ座標
static Camera camera;

//カメラの角度
static double camera_angle;
static double camera_angleY;

//カメラ座標を初期化する
void initCamerCoordinates() {
	camera.x = 0;
	camera.y = 3;
	camera.z = -10;
	camera.gx = 0;
	camera.gy = 0;
	camera.gz = 0;
	camera.ux = 0;
	camera.uy = 1;
	camera.uz = 0;
	camera_angle = PI / 2;
	camera_angleY = 0;
}

//カメラ座標を取得する
Camera getStateCameraCoordinates() {
	return camera;
}

//カメラ座標をマウスの移動から計算する(１人称視点)
void transfarAndRotateCameraByMouse() {

	//マウス移動の取得
	int mouse_dx, mouse_dy;
	getMouseMotionAndInit(&mouse_dx, &mouse_dy);

	//マウスの動きをカメラ角度に変換
	camera_angle += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
	camera_angleY -= ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

	//カメラ角度を視点位置に反映
	camera.gx = cos(camera_angle) * cos(camera_angleY) + camera.x;
	camera.gz = sin(camera_angle) * cos(camera_angleY) + camera.z;
	camera.gy = sin(camera_angleY) + camera.y;

}

//カメラ座標をキー入力から計算する(１人称視点)
void transfarCameraByKey() {
	//カメラの移動
	if (getStateKeyOfSmallAlphabet('w') == 1) {
		camera.x += CAMERA_SP * cos(camera_angle) * cos(camera_angleY);
		camera.z += CAMERA_SP * sin(camera_angle) * cos(camera_angleY);
		camera.y += CAMERA_SP * sin(camera_angleY);
	}
	if (getStateKeyOfSmallAlphabet('s') == 1) {
		camera.x -= CAMERA_SP * cos(camera_angle) * cos(camera_angleY);
		camera.z -= CAMERA_SP * sin(camera_angle) * cos(camera_angleY);
		camera.y -= CAMERA_SP * sin(camera_angleY);
	}
	if (getStateKeyOfSmallAlphabet('a') == 1) {
		camera.x += CAMERA_SP * cos(camera_angle - PI / 2) * cos(camera_angleY);
		camera.z += CAMERA_SP * sin(camera_angle - PI / 2) * cos(camera_angleY);
	}
	if (getStateKeyOfSmallAlphabet('d') == 1) {
		camera.x += CAMERA_SP * cos(camera_angle + PI / 2) * cos(camera_angleY);
		camera.z += CAMERA_SP * sin(camera_angle + PI / 2) * cos(camera_angleY);
	}

	//q入力時_カメラの初期化
	if (getStateKeyOfSmallAlphabet('q') == 1)
		initCamerCoordinates();
}

//gluLookAtを設定する
void setGluLookAt() {
	gluLookAt(camera.x, camera.y, camera.z, camera.gx, camera.gy, camera.gz,
			camera.ux, camera.uy, camera.uz);
}
