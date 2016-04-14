#include "../head/uGL.h"

//色(4fv)
float uColor4fv_brack[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //黒
float uColor4fv_white[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //白
float uColor4fv_red[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //赤
float uColor4fv_green[] = { 0.0f, 1.0f, 0.0f, 1.0f }; //緑
float uColor4fv_blue[] = { 0.0f, 0.0f, 1.0f, 1.0f }; //青

//材質(4fv)
float uMaterial4fv_red[] = { 0.8, 0.2, 0.2, 1.0 }; //赤
float uMaterial4fv_white[] = { 0.9, 0.9, 0.9, 1.0 }; //白
float uMaterial4fv_black[] = { 0.1, 0.1, 0.1, 1.0 }; //黒
float uMaterial4fv_blue[] = { 0.1, 0.1, 0.9, 1.0 }; //青
float uMaterial4fv_green[] = { 0.1, 0.9, 0.1, 1.0 }; //緑

//エラー出力
void uErrorOut(const char file[], const char func[], int line,
		const char message[]) {
	fprintf(stderr, "<file:%s func:%s line:%d>\n", file, func, line);
	fprintf(stderr, "Error:%s\n\n", message);
}

//2D上にの点を描画する(size=直径)
void uPoint2D(int x, int y, float size) {
	glPointSize(size);
	glBegin (GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

//2D上に線を描画する
void uLine2D(int x1, int y1, int x2, int y2, float width) {
	glLineWidth(width);
	glBegin (GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

//2D上に四角形を描画する
void uSquare2D(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,
		float width) {
	glLineWidth(width);
	glBegin (GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glVertex2i(x4, y4);
	glEnd();
}

void uSquare2D(int x1, int y1, int x2, int y2, float width) {
	glLineWidth(width);
	glBegin (GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

//2D上に四角形を描画する(塗りつぶし)
void uSquareFill2D(int x1, int y1, int x2, int y2, int x3, int y3, int x4,
		int y4) {
	glBegin (GL_QUADS);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glVertex2i(x4, y4);
	glEnd();
}

void uSquareFill2D(int x1, int y1, int x2, int y2) {
	glBegin (GL_QUADS);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

//2D上に円を描画
void uCircle2D(float radius, int x, int y) {
	for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 1.0) {
		float th2 = th1 + 10.0;
		float th1_rad = th1 / 180.0 * uPI;
		float th2_rad = th2 / 180.0 * uPI;

		float x1 = radius * cos(th1_rad);
		float y1 = radius * sin(th1_rad);
		float x2 = radius * cos(th2_rad);
		float y2 = radius * sin(th2_rad);

		glBegin (GL_LINES);
		glVertex2f(x1 + x, y1 + y);
		glVertex2f(x2 + x, y2 + y);
		glEnd();
	}
}

//2D上に円を描画(塗りつぶし)
void uCircle2DFill(float radius, int x, int y) {
	for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 1.0) {
		float th2 = th1 + 10.0;
		float th1_rad = th1 / 180.0 * uPI;
		float th2_rad = th2 / 180.0 * uPI;

		float x1 = radius * cos(th1_rad);
		float y1 = radius * sin(th1_rad);
		float x2 = radius * cos(th2_rad);
		float y2 = radius * sin(th2_rad);

		glBegin (GL_TRIANGLES);
		glVertex2f(x, y);
		glVertex2f(x1 + x, y1 + y);
		glVertex2f(x2 + x, y2 + y);
		glEnd();
	}
}

//2D上に楕円を描画
void uOval2D(float radius, int x, int y, float ovalx, float ovaly) {
	for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 1.0) {
		float th2 = th1 + 10.0;
		float th1_rad = th1 / 180.0 * uPI;
		float th2_rad = th2 / 180.0 * uPI;

		float x1 = radius * cos(th1_rad) * (ovalx / 100.0f);
		float y1 = radius * sin(th1_rad) * (ovaly / 100.0f);
		float x2 = radius * cos(th2_rad) * (ovalx / 100.0f);
		float y2 = radius * sin(th2_rad) * (ovaly / 100.0f);

		glBegin (GL_LINES);
		glVertex2f(x1 + x, y1 + y);
		glVertex2f(x2 + x, y2 + y);
		glEnd();
	}
}

//2D上に楕円を描画(塗りつぶし)
void uOval2DFill(float radius, int x, int y, float ovalx, float ovaly) {
	for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 1.0) {
		float th2 = th1 + 10.0;
		float th1_rad = th1 / 180.0 * uPI;
		float th2_rad = th2 / 180.0 * uPI;

		float x1 = radius * cos(th1_rad) * (ovalx / 100.0f);
		float y1 = radius * sin(th1_rad) * (ovaly / 100.0f);
		float x2 = radius * cos(th2_rad) * (ovalx / 100.0f);
		float y2 = radius * sin(th2_rad) * (ovaly / 100.0f);

		glBegin (GL_TRIANGLES);
		glVertex2f(x, y);
		glVertex2f(x1 + x, y1 + y);
		glVertex2f(x2 + x, y2 + y);
		glEnd();
	}
}

//三角形を描画
void uDrawTriangle(Vector3 v1, float color1[], Vector3 v2, float color2[],
		Vector3 v3, float color3[]) {
	glBegin (GL_TRIANGLES);
	glColor4fv(color1);
	glVertex3f(v1.x, v1.y, v1.z);
	glColor4fv(color2);
	glVertex3f(v2.x, v2.y, v2.z);
	glColor4fv(color3);
	glVertex3f(v3.x, v3.y, v3.z);
	glEnd();
}

//四角形を描画
void uDrawQuadrangle(Vector3 v1, float color1[], Vector3 v2, float color2[],
		Vector3 v3, float color3[], Vector3 v4, float color4[]) {
	glBegin (GL_QUADS);
	glColor4fv(color1);
	glVertex3f(v1.x, v1.y, v1.z);
	glColor4fv(color2);
	glVertex3f(v2.x, v2.y, v2.z);
	glColor4fv(color3);
	glVertex3f(v3.x, v3.y, v3.z);
	glColor4fv(color4);
	glVertex3f(v4.x, v4.y, v4.z);
	glEnd();
}

//黒白の地面を描画
void uDrawGround(int size) {
	if (size < 0 || 1000 < size) {
		uErrorOut(__FILE__, __func__, __LINE__, "サイズ指定値が不正です");
		return;
	}

	glBegin (GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	for (int j = -size / 2; j < size / 2; j++) {
		for (int i = -size / 2; i < size; i++) {
			//RGB設定
			if (((i + j) % 2) == 0)
				glColor4fv(uColor4fv_white);
			else
				glColor4fv(uColor4fv_brack);
			//材質設定
			if (((i + j) % 2) == 0)
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, uMaterial4fv_white);
			else
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, uMaterial4fv_black);

			glVertex3d((GLdouble) i, 0.0, (GLdouble) j);
			glVertex3d((GLdouble) i, 0.0, (GLdouble)(j + 1));
			glVertex3d((GLdouble)(i + 1), 0.0, (GLdouble)(j + 1));
			glVertex3d((GLdouble)(i + 1), 0.0, (GLdouble) j);
		}
	}
	glEnd();
}

//文字列描画
void uDrawString(const char str[], int x0, int y0, const float color[]) {
	glDisable (GL_LIGHTING);

	// 平行投影にする
	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_INIT_WINDOW_WIDTH),
			glutGet(GLUT_INIT_WINDOW_HEIGHT), 0);
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// 画面上にテキスト描画
	glColor4fv(color);
	glRasterPos2f(x0, y0);
	for (; *str; str++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);
}