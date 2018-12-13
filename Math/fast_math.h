#ifndef __FAST_MATH_H__
#define __FAST_MATH_H__

#include <stdint.h>

float fast_sqrt(float x);
float fast_sq(float x);
float fast_fabs(float x);
uint16_t fast_abs(int16_t x);
uint32_t fast_32abs(int32_t x);
float fast_sin(float x);
float fast_cos(float x);
float fast_atan2(float y, float x);
float fast_fcontain(const float data,const float max,const float min);
float fast_i16contain(const int16_t data,const int16_t max,const int16_t min);

#endif
