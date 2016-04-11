/////////////////////////////////////////////////////////////////////////////
//
// 3D Math Primer for Games and Graphics Development
//
// EulerAngles.cpp - EulerAnglesクラスの実装
//
// Visit gamemath.com for the latest version of this file.
//
/////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "../head_2/EulerAngles.h"
#include "../head_2/Quaternion.h"
#include "../head_2/MathUtil.h"
#include "../head_2/Matrix4x3.h"
#include "../head_2/RotationMatrix.h"

/////////////////////////////////////////////////////////////////////////////
//
// Notes:
//
// See Chapter 11 for more information on class design decisions.
//
// See section 10.3 for more information on the Euler angle conventions
// assumed.
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// global data
//
/////////////////////////////////////////////////////////////////////////////

// 恒等オイラー角用のグローバルな定数
// ところで、このオブジェクトが(他のオブジェクトに対して)いつ作られるのか正確には
// わからない場合がある
// このため、このオブジェクトは、初期化される前に参照可能である
// スタートアップ時に何らかの方法で0で初期化される

const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

/////////////////////////////////////////////////////////////////////////////
//
// class EulerAngles Implementation
//
/////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
// EulerAngles::canonize
//
// オイラー角の3つ組を正準化する
// これは、オイラー角の3D空間での方向の表現としての意味は変更しないが
// この角度が角速度などの他の目的用であれば、この操作は有効でなくなる

void	EulerAngles::canonize() {

	// 最初に、ピッチを範囲-π...πにラップする

	pitch = wrapPi(pitch);

	// ここで、正準範囲-π/2...π/2の外側で行列pitchの裏側をチェックする

	if (pitch < -kPiOver2) {
		pitch = -kPi - pitch;
		heading += kPi;
		bank += kPi;
	} else if (pitch > kPiOver2) {
		pitch = kPi - pitch;
		heading += kPi;
		bank += kPi;
	}

	// ここでジンバルロックのケースをチェックする(許容範囲を少し持つ)

	if (fabs(pitch) > kPiOver2 - 1e-4) {

		// ジンバルロック内にいる
		// 垂直軸に関するすべての回転をヘディングに割り当てる

		heading += bank;
		bank = 0.0f;

	} else {

		// ジンバルロック内にいない
		// バンク角を正準範囲にラップする

		bank = wrapPi(bank);
	}

	// ヘディングを正準範囲にラップする

	heading = wrapPi(heading);
}

//---------------------------------------------------------------------------
// EulerAngles::fromObjectToInertialQuaternion
//
// オイラー角をセットアップする
// オブジェクト空間->慣性空間への回転四元数が与えられる

void	EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q) {

	// sin(pitch)を取り出す

	float sp = -2.0f * (q.y*q.z - q.w*q.x);

	// ジンバルロックをチェックする
	// 数字の不正確さのために僅かな許容範囲を与える

	if (fabs(sp) > 0.9999f) {

		// 真上か真下を向いている

		pitch = kPiOver2 * sp;

		// ヘディングを計算し、バンクを0に設定する

		heading = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;

	} else {

		// 角度を計算する
		// 安全なasin関数を用いる必要はない
		// ジンバルロックチェック時に範囲をすでにチェックしているからである

		pitch	= asin(sp);
		heading	= atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank	= atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}

//---------------------------------------------------------------------------
// EulerAngles::fromInertialToObjectQuaternion
//
// オイラー角をセットアップする
// 慣性空間->オブジェクト空間への回転四元数が与えられる

void	EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q) {

	// sin(pitch)を取り出す

	float sp = -2.0f * (q.y*q.z + q.w*q.x);

	// ジンバルロックをチェックする
	// 数字の不正確さのために僅かな許容範囲を与える

	if (fabs(sp) > 0.9999f) {

		// 真上か真下を向いている

		pitch = kPiOver2 * sp;

		// ヘディングを計算し、バンクを0に設定する

		heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;

	} else {

		// 角度を計算する
		// 安全なasin関数を用いる必要はない
		// ジンバルロックチェック時に範囲をすでにチェックしているからである

		pitch	= asin(sp);
		heading	= atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank	= atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}

//---------------------------------------------------------------------------
// EulerAngles::fromObjectToWorldMatrix
//
// Setup the Euler angles, given an object->world transformation matrix.
//
// The matrix is assumed to be orthogonal.  The translation portion is
// ignored.
//
// See 10.6.2 for more information.

void	EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m) {

	// Extract sin(pitch) from m32.

	float	sp = -m.m32;

	// Check for Gimbel lock
	
	if (fabs(sp) > 9.99999f) {

		// Looking straight up or down

		pitch = kPiOver2 * sp;

		// Compute heading, slam bank to zero

		heading = atan2(-m.m23, m.m11);
		bank = 0.0f;

	} else {

		// Compute angles.  We don't have to use the "safe" asin
		// function because we already checked for range errors when
		// checking for Gimbel lock

		heading = atan2(m.m31, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12, m.m22);
	}
}

//---------------------------------------------------------------------------
// EulerAngles::fromWorldToObjectMatrix
//
// Setup the Euler angles, given a world->object transformation matrix.
//
// The matrix is assumed to be orthogonal.  The translation portion is
// ignored.
//
// See 10.6.2 for more information.

void	EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m) {

	// Extract sin(pitch) from m23.

	float	sp = -m.m23;

	// Check for Gimbel lock
	
	if (fabs(sp) > 9.99999f) {

		// Looking straight up or down

		pitch = kPiOver2 * sp;

		// Compute heading, slam bank to zero

		heading = atan2(-m.m31, m.m11);
		bank = 0.0f;

	} else {

		// Compute angles.  We don't have to use the "safe" asin
		// function because we already checked for range errors when
		// checking for Gimbel lock

		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}

//---------------------------------------------------------------------------
// EulerAngles::fromRotationMatrix
//
// Setup the Euler angles, given a rotation matrix.
//
// See 10.6.2 for more information.

void	EulerAngles::fromRotationMatrix(const RotationMatrix &m) {

	// Extract sin(pitch) from m23.

	float	sp = -m.m23;

	// Check for Gimbel lock
	
	if (fabs(sp) > 9.99999f) {

		// Looking straight up or down

		pitch = kPiOver2 * sp;

		// Compute heading, slam bank to zero

		heading = atan2(-m.m31, m.m11);
		bank = 0.0f;

	} else {

		// Compute angles.  We don't have to use the "safe" asin
		// function because we already checked for range errors when
		// checking for Gimbel lock

		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}
