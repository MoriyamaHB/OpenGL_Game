//標準、ライブラリ
//#include <freeglut.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<string.h>
#include"../head/uGL.h"

//自作ヘッダ
#include"define.h"
#include"enum.h"
#include"struct.h"

//クラス
#include"../class_head/vector3.h"
#include"../class_head/camera.hpp"
#include"../class_head/fps.hpp"
#include"../class_head/OutputDisplay.hpp"
#include"../class_head/ball.hpp"
#include"../class_head/meteo.hpp"

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern
#endif

#include "function.h"

//クラス定義
GLOBAL Camera3D3P camera;
GLOBAL OutputDisplay out_disp;
GLOBAL Fps fps;
