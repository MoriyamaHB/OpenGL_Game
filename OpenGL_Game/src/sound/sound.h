//sound.h
class Sound {
private:
	//バッファとソース
	ALuint buffer_, source_;

public:
	Sound(const char *BGMFileName); //コンストラクタ
	void SetListener(Vector3 listener_position, Vector3 listener_direction,
			Vector3 listener_up_vec);//リスナー位置設定
	void SetSource(Vector3 source_position);//音源位置設定
	void Stream();	//毎フレーム呼ぶと音源がループする
	void Play();	//呼び出すと再度最初から再生する
	~Sound();	//デストラクタ
};
