class Fps {
public:
	//デフォルトコンストラクタ
	Fps() {
		start_cnt = 0;
		cnt = 0;
		calculated_fps = 0;
		update_cnt = FRAME_PER_SECONDS;
		set_fps = FRAME_PER_SECONDS;
		frame_cnt = 0;
		WaitTime = 0;
	}

	//FPS処理時間など更新
	void fps_Update() {
		frame_cnt++;
		if (cnt == update_cnt) { //60フレーム目なら平均を計算する
			calculated_fps = 1000 / ((update_cnt) / (double) update_cnt);
			cnt = 0;
		}
	}

	//FPSの描画
	void fps_DrawFPS(int X, int Y) {
		char str[48];
		sprintf(str, "%f", calculated_fps);
		uDrawString(str, X, Y, uColor4fv_red);
	}

private:
	unsigned int start_cnt;		//測定開始時刻
	unsigned int cnt;			//カウンタ
	double calculated_fps;		//fpsの計算結果
	unsigned int update_cnt;	//平均を取るサンプル数
	int set_fps;				//設定したFPS
	int WaitTime;				//待機時間のサンプリングフレーム間での合計
	unsigned int frame_cnt;		//経過フレームのカウント
};

