//標準ライブラリ
#include <GL/freeglut.h>
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
#include "enum.h"
#include "struct.h"

//継承元or便利ヘッダ
#include "../util/solid.h"
#include "../util/ball.h"
#include "../util/square.h"
#include "../util/fps.hpp"
#include "../util/vector3.h"

//プロジェクトヘッダ
#include "../bullet/control_bullet.h"
#include "../bullet/bullet.hpp"
#include "../display/output_display.hpp"
#include "../input/input.hpp"
#include "../main/first_init.hpp"
#include "../main/main.hpp"
#include "../meteo/control_meteo.hpp"
#include "../meteo/meteo.hpp"
#include "../player/camera.hpp"
#include "../player/player.h"
#include "../target/target.h"
