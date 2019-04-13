#include "ssemath.h"


void(*pfFastSinCos)(float x, float& s, float& c) = SinCos;