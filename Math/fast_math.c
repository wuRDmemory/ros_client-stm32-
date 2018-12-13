#include "fast_math.h"

static const float P = 0.225f;
static const float B = 1.2732f;
static const float C = -0.4053f;
static const float PI = 3.1415926f;

float fast_sqrt(float x) 
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return 1.0f/y;
}

float fast_sq(float x)
{
    return x*x;
}

float fast_fabs(float x)
{
	return x >= 0 ? x : -x;
}

uint16_t fast_abs(int16_t x)
{
	return x >= 0 ? x : -x;
}

uint32_t fast_32abs(int32_t x)
{
	return x >= 0 ? x : -x;
}

float fast_sin(float x)
{
	float  y = B*x + C*x*fast_fabs(x);
	return (P*(y*fast_fabs(y) - y)+y);
}

float fast_cos(float x)
{
	x += PI/2.0f;
	
	if(x > PI)
		x -= 2.0f*PI;
	return fast_sin(x);
}

float fast_atan2(float y, float x)
{
	float angle, r;
	const float c3 = 0.1821;
	const float c1 = 0.9675;
	float abs_y = fast_fabs(y) + (float) (1e-10);

	if (x >= 0)
	{
		r = (x - abs_y) / (x + abs_y);
		angle = (float) (PI / 4.0);
	}
	else
	{
		r = (x + abs_y) / (abs_y - x);
		angle = (float) (3 * PI / 4.0);
	}
	angle += (c3 * r * r - c1) * r;
	return (y < 0) ? -angle : angle;
}

float fast_fcontain(const float data,const float max,const float min)
{
    return (data >= max) ? max : ((data < min) ? min : data);
}

float fast_i16contain(const int16_t data,const int16_t max,const int16_t min)
{
    return (data >= max) ? max : ((data < min) ? min : data);
}
