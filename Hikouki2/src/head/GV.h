#include"define.h"
#include"enum.h"
#include"struct.h"
#include<GL/freeglut.h>
#include<stdio.h>
#include<math.h>
#include"../head_2/vector3.h"
#include<iostream>
#include"../head_2/uGL.h"

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern
#endif

#include "function.h"

//クラス設計
#include"../source/camera.hpp"

//クラス定義
GLOBAL Camera camera;
