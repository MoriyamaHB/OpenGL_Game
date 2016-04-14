#include"define.h"
#include"enum.h"
#include"struct.h"
//#include <freeglut.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"../head_2/vector3.h"
#include<iostream>
#include"../head_2/uGL.h"
#include<unistd.h>
#include<time.h>
#include<string.h>

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern
#endif

#include "function.h"

//クラス設計
#include"../class_head/camera.hpp"
#include"../class_head/fps.hpp"
#include"../class_head/OutputDisplay.hpp"

//クラス定義
GLOBAL Camera3D3P camera;
GLOBAL OutputDisplay out_disp;
GLOBAL Fps fps;
