class OutputDisplay {
public:
	void Regist(const char str[], const float color[], int life = 1);
	void Draw();

private:
	const static int kMaxItem = 24; 	//最大登録数
	const static int kLineHeight = 30; 	//一行分の高さ
	const static int kStartWidth = 10; 	//描画開始座標x
	const static int kStartHeight = 23; //描画開始座標y
	OutputItem item_[kMaxItem];

	//空の項目を探す
	int SerchEmptyItem();
};
