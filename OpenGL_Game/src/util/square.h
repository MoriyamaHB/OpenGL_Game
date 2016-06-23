#ifndef OPENGLGAME_UTIL_SQUARE_H_
#define OPENGLGAME_UTIL_SQUARE_H_

class Square: public Solid {
public:
	//コンストラクタ,初期化
	Square();
	Square(float x, float y, float z);
	Square(Vector3 point);

	//描画
	void Draw() const;
};

#endif
