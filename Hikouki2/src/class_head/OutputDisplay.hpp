class OutputDisplay {
public:

	//デフォルトコンストラクタ
	OutputDisplay();

	//画面出力文字の登録
	void regist(const char str[], const float color[]);

	//画面出力文字の描画
	void draw();

private:
	const static int MAX_ITEM = 24; //最大登録数
	const static int LINE_HEIGHT = 30; //一行分の高さ
	const static int START_WIDTH = 10; //描画開始座標x
	const static int START_HEIGHT = 23; //描画開始座標y
	int num;
	OutputItem item[MAX_ITEM];
};
