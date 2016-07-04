//標準ライブラリ
#include <GL/freeglut.h>
#include <FTGL/ftgl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <math.h>

//自作ライブラリ
#include "../util/cc_util.h"
#include "../util/uGL.h"

//データヘッダ
#include "define.h"
#include "struct.h"

//継承元or便利ヘッダ
#include "../util/solid.h"
#include "../util/ball.h"
#include "../util/square.h"
#include "../util/fps.h"
#include "../util/vector3.h"

//プロジェクトヘッダ
#include "../bullet/control_bullet.h"
#include "../bullet/bullet.h"
#include "../display/output_display.h"
#include "../input/input.h"
#include "../main/first_init.h"
#include "../main/main.h"
#include "../meteo/control_meteo.h"
#include "../meteo/meteo.h"
#include "../player/camera.h"
#include "../player/player.h"
#include "../score/score.h"
#include "../start/start.h"
#include "../target/target.h"
#include "../time/time.h"
