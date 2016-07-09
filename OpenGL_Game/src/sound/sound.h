//sound.h
class Sound {
private:
	//バッファとソース
	ALuint buffer_, source_;

public:
	Sound(const char *BGMFileName); //コンストラクタ
	void SetListener(Vector3 listener_position, Vector3 listener_direction,
			Vector3 listener_up_vec) const; //リスナー位置設定
	void SetListener(const Camera3D3P *camera) const; //リスナー位置設定(カメラクラスを用いる)
	void SetSource(Vector3 source_position) const; //音源位置設定
	void Stream() const;	//毎フレーム呼ぶと音源がループする
	void Play() const;	//呼び出すと再度最初から再生する
	~Sound();	//デストラクタ
};
