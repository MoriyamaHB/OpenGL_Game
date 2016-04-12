#include"../head/GV.h"

//カメラ座標
static Camera camera;

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
	camera.angle_h = PI / 2;
	camera.angle_w = 0;
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
	camera.angle_h += ((double) mouse_dx / CAMERA_ROTATE_PX) * 2 * PI;
	camera.angle_w += ((double) mouse_dy / CAMERA_ROTATE_PX) * 2 * PI;

	//カメラ角度を視点位置に反映
	camera.gx = cos(camera.angle_h) * cos(camera.angle_w) + camera.x;
	camera.gz = sin(camera.angle_h) * cos(camera.angle_w) + camera.z;
	camera.gy = sin(camera.angle_w) + camera.y;

}

//カメラ座標をキー入力から計算する(3人称視点)
void transfarCameraByKey() {
	//カメラの移動
	if (getStateKeyOfSmallAlphabet('w') == 1) {
		camera.x -= CAMERA_SP * cos(camera.angle_h) * cos(camera.angle_w);
		camera.z -= CAMERA_SP * sin(camera.angle_h) * cos(camera.angle_w);
		camera.y -= CAMERA_SP * sin(camera.angle_w);
	}
	if (getStateKeyOfSmallAlphabet('s') == 1) {
		camera.x += CAMERA_SP * cos(camera.angle_h) * cos(camera.angle_w);
		camera.z += CAMERA_SP * sin(camera.angle_h) * cos(camera.angle_w);
		camera.y += CAMERA_SP * sin(camera.angle_w);
	}
	if (getStateKeyOfSmallAlphabet('a') == 1) {
		camera.x += CAMERA_SP * cos(camera.angle_h - PI / 2)
				* cos(camera.angle_w);
		camera.z += CAMERA_SP * sin(camera.angle_h - PI / 2)
				* cos(camera.angle_w);
	}
	if (getStateKeyOfSmallAlphabet('d') == 1) {
		camera.x -= CAMERA_SP * cos(camera.angle_h + PI / 2)
				* cos(camera.angle_w);
		camera.z -= CAMERA_SP * sin(camera.angle_h + PI / 2)
				* cos(camera.angle_w);
	}

	//q入力時_カメラの初期化
	if (getStateKeyOfSmallAlphabet('q') == 1)
		initCamerCoordinates();
}

//gluLookAtを設定する
void setGluLookAt() {
	gluLookAt(camera.gx, camera.gy, camera.gz, camera.x, camera.y, camera.z,
			camera.ux, camera.uy, camera.uz);
}
