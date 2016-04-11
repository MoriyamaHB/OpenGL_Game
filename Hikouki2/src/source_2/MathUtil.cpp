/////////////////////////////////////////////////////////////////////////////
//
// 3D Math Primer for Games and Graphics Development
//
// MathUtil.cpp - 雑多な数学ユーティリティ用の宣言
//
// Visit gamemath.com for the latest version of this file.
//
/////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "../head_2/MathUtil.h"
#include "../head_2/vector3.h"

const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

//---------------------------------------------------------------------------
// 適切に2πの倍数を加えることで角度を-π...πの範囲にラップする

float wrapPi(float theta) {
	theta += kPi;
	theta -= floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

//---------------------------------------------------------------------------
// safeAcos
//
// acos(x)と同じ
// ただし、xが範囲外の場合、最も近い有効な値にクランプ処理される
// 返される値は、範囲0...πであり、これは標準のCのacos()関数と同じである

float safeAcos(float x) {

	// 制限条件をチェックする

	if (x <= -1.0f) {
		return kPi;
	}
	if (x >= 1.0f) {
		return 0.0f;
	}

	// 値が範囲内 --- 標準のC関数を用いる

	return acos(x);
}
