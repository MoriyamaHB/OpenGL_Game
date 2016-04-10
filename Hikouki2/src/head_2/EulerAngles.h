/////////////////////////////////////////////////////////////////////////////
//
// 3D Math Primer for Games and Graphics Development
//
// EulerAngles.h - EulerAnglesクラス用の宣言
//
// Visit gamemath.com for the latest version of this file.
//
// For more details, see EulerAngles.cpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __EULERANGLES_H_INCLUDED__
#define __EULERANGLES_H_INCLUDED__

// 前方宣言

class Quaternion;
class Matrix4x3;
class RotationMatrix;

//---------------------------------------------------------------------------
// class EulerAngles
//
// このクラスはヘディング・ピッチ・バンクのオイラー角3つ組で表す

class EulerAngles {
public:

// Public data

	// 素直な表現:3つの角度をラジアンで保存する

	float	heading;
	float	pitch;
	float	bank;

// Public operations

	// デフォルトのコンストラクタは何もしない

	EulerAngles() {}

	// 3つの値のコンストラクタ

	EulerAngles(float h, float p, float b) :
		heading(h), pitch(p), bank(b) {}

	// 恒等化する(すべて0を設定する

	void	identity() { pitch = bank = heading = 0.0f; }

	// 正準オイラー角の3つ組を決定する

	void	canonize();

	// 四元数をオイラー角形式に変換する
	// 入力される四元数は、その名前が示すようにオブジェクト空間から完成空間、
	// または、完成空間からオブジェクト空間への回転を実行するものとする

	void	fromObjectToInertialQuaternion(const Quaternion &q);
	void	fromInertialToObjectQuaternion(const Quaternion &q);

	// 座標変換行列をオイラー角に変換する
	// 入力される行列はは、その名前が示すようにオブジェクト空間から完成空間、
	// または、完成空間からオブジェクト空間への回転を実行するものとする
	// この行列は直行しているものとする

	void	fromObjectToWorldMatrix(const Matrix4x3 &m);
	void	fromWorldToObjectMatrix(const Matrix4x3 &m);

	// 回転行列をオイラー角形式に変換する

	void	fromRotationMatrix(const RotationMatrix &m);
};

// 恒等オイラー角用のグローバルな定数

extern const EulerAngles kEulerAnglesIdentity;

/////////////////////////////////////////////////////////////////////////////
#endif // #ifndef __EULERANGLES_H_INCLUDED__
