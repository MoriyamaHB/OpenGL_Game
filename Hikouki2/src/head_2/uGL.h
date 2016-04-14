#ifndef UGL_H_
#define UGL_H_

#include "vector3.h"

//色(4fv)
extern float uColor4fv_brack[];
extern float uColor4fv_white[];
extern float uColor4fv_red[];
extern float uColor4fv_green[];
extern float uColor4fv_blue[];

//材質(4fv)
extern float uMaterial4fv_red[];
extern float uMaterial4fv_white[];
extern float uMaterial4fv_black[];
extern float uMaterial4fv_blue[];
extern float uMaterial4fv_green[];

//2D上にの点を描画する(size=直径)
extern void uPoint2D(int x, int y, float size);

//2D上に線を描画する
extern void uLine2D(int x1, int y1, int x2, int y2, float width);

//2D上に四角形を描画する
extern void uSquare2D(int x1, int y1, int x2, int y2, int x3, int y3, int x4,
		int y4, float width);
extern void uSquare2D(int x1, int y1, int x2, int y2, float width);

//2D上に四角形を描画する(塗りつぶし)
extern void uSquareFill2D(int x1, int y1, int x2, int y2, int x3, int y3,
		int x4, int y4);
extern void uSquareFill2D(int x1, int y1, int x2, int y2);

//2D上に円を描画
extern void uCircle2D(float radius, int x, int y);

//2D上に円を描画(塗りつぶし)
extern void uCircle2DFill(float radius, int x, int y);

//2D上に楕円を描画
extern void uOval2D(float radius, int x, int y, float ovalx, float ovaly);

//2D上に楕円を描画(塗りつぶし)
extern void uOval2DFill(float radius, int x, int y, float ovalx, float ovaly);

//三角形を描画
extern void uDrawTriangle(Vector3 v1, float color1[], Vector3 v2,
		float color2[], Vector3 v3, float color3[]);

//四角形を描画
extern void uDrawQuadrangle(Vector3 v1, float color1[], Vector3 v2,
		float color2[], Vector3 v3, float color3[], Vector3 v4, float color4[]);

//黒白の地面を描画
extern void uDrawGround(int size);

//文字列描画
void uDrawString(char str[], int x0, int y0, float color[]);

#endif /* UGL_H_ */
