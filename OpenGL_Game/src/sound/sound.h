//sound.h
class Sound{
private:
	ALuint buffer, source;	//バッファとソース
	float angle;	//音源の位置
public:
	Sound(const char *BGMFileName);	//コンストラクタ
	void stream();	//毎フレーム呼ぶと音源が移動する
	~Sound();	//デストラクタ
};
