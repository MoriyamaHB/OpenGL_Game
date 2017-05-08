# OpenGL_Game
---
openglで作ったゲームです

## 使用言語
C++

## 使用ライブラリ
#### 描画
* gl
* glu
* glut

#### 音
* al
* alut

#### 文字
* freeglut
* ftgl

## ビルド方法(ubuntu16.04,64bit,eclipse4.6,g++5.4.0を使用時)
1. sudo apt install freeglut3-dev libalut-dev libfreetype6-dev libftgl-dev
2. includeパスに[../64/include/]を指定(/usr/include/freetype2も必要かもしれない)
3. ライブラリに[ftgl,freetype,glut,GLU,GL,alut,openal]を指定
4. ライブラリパスに[../64/lib]を指定する
5. ビルドする
