/////////////////////////////////////////////////////////////////////////////
//
// 3D Math Primer for Games and Graphics Development
//
// MathUtil.h - 雑多な数学ユーティリティ用の宣言
//
// Visit gamemath.com for the latest version of this file.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MATHUTIL_H_INCLUDED__
#define __MATHUTIL_H_INCLUDED__

#include <math.h>

// πといくつかの倍数用のグローバル定数の宣言

const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;
const float kPiOver180 = kPi / 180.0f;
const float k180OverPi = 180.0f / kPi;

// 適切に2πの倍数を加えることで角度を-π...πの範囲にラップする

extern float wrapPi(float theta);

// 安全な逆三角関数

extern float safeAcos(float x);

// Convert between degrees and radians

inline float	degToRad(float deg) { return deg * kPiOver180; }
inline float	radToDeg(float rad) { return rad * k180OverPi; }

// ある角度のsinとcosを計算する
// プラットフォームによっては両方の値が必要なことが分っている場合、
// 2つの値を別に計算するよりも早く計算できる

inline void sinCos(float *returnSin, float *returnCos, float theta) {

	// 簡単化のために、単に通常の三角関数を用いる
	// 注意すべきことは、プラットフォームによってはより良い方法が
	// 存在する場合があるという事である

	*returnSin = sin(theta);
	*returnCos = cos(theta);
}

// Convert between "field of view" and "zoom"  See section 15.2.4.
// The FOV angle is specified in radians.

inline float	fovToZoom(float fov) { return 1.0f / tan(fov * .5f); }
inline float	zoomToFov(float zoom) { return 2.0f * atan(1.0f / zoom); }

/////////////////////////////////////////////////////////////////////////////
#endif // #ifndef __MATHUTIL_H_INCLUDED__
