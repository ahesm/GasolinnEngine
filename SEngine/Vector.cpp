#include "Vector.h"

gfunc::Ver2::Ver2(Vec2 vec) { this->x = vec.x; this->y, vec.y; };
gfunc::Vec2::Vec2(Ver2 ver) { this->x, ver.x; this->y = ver.y; };