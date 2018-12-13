#ifndef __MYNAME_H__
#define __MYNAME_H__

#include <stdint.h>

#define bool char
    
typedef struct
{
    float a;
    float b;
    float c;
}Vector_t;

typedef struct 
{
    Vector_t a,b,c;
}Matrix_t;

void Vector_zero(Vector_t* v);
Vector_t Vector_add(Vector_t a,Vector_t b);
Vector_t Vector_sub(Vector_t a,Vector_t b);
float Vector_mult(Vector_t a,Vector_t b);
Vector_t Vector_multk(Vector_t a,float k);
Vector_t Vector_cross(Vector_t a,Vector_t b);
float Vector_length(Vector_t a);
Vector_t Vector_norm(Vector_t a);
Matrix_t Matrix_multk(Matrix_t a,float k);
Vector_t Matrix_multVector(Matrix_t m,Vector_t b,bool transp);
Vector_t Matrix_multXYVextor(Matrix_t m,Vector_t b,bool transp);
Vector_t Matrix_multZVextor(Matrix_t m,Vector_t b,bool transp);
Matrix_t Matrix_quat2dcm(float quat[4]);
Matrix_t Matrix_update(Matrix_t m,Vector_t v);

#endif
