#include "mv_math.h"
#include "fast_math.h"

#define bool char

// 向量清零
void Vector_zero(Vector_t* v)
{
    v->a = 0;
    v->b = 0;
    v->c = 0;
}

// 向量相加
Vector_t Vector_add(Vector_t a,Vector_t b)
{
    Vector_t _temp;
    
    _temp.a = a.a + b.a;
    _temp.b = a.b + b.b;
    _temp.c = a.c + b.c;
    
    return _temp;
}

// 矩阵相减
Vector_t Vector_sub(Vector_t a,Vector_t b)
{
    Vector_t _temp;
    
    _temp.a = a.a - b.a;
    _temp.b = a.b - b.b;
    _temp.c = a.c - b.c;
    
    return _temp;
}

// 向量的内积
float Vector_mult(Vector_t a,Vector_t b)
{
    float _r = 0;
    
    _r += a.a * b.a;
    _r += a.b * b.b;
    _r += a.c * b.c;
    
    return _r;
}

// 向量的叉积
Vector_t Vector_cross(Vector_t a,Vector_t b)
{
    Vector_t _temp;
    
    _temp.a = a.b*b.c - a.c*b.b;
    _temp.b = -(a.a*b.c - a.c*b.a);
    _temp.c = a.a*b.b - a.b*b.a;
    
    return _temp;
}

// 向量与实数相乘
Vector_t Vector_multk(Vector_t a,float k)
{
    Vector_t _temp;
    
    _temp.a = a.a*k;
    _temp.b = a.b*k;
    _temp.c = a.c*k;
    
    return _temp;
}

// 向量的模
float Vector_length(Vector_t a)
{
    return fast_sqrt(a.a*a.a + a.b*a.b + a.c*a.c);
}

// 向量的归一化
Vector_t Vector_norm(Vector_t a)
{
    Vector_t t;
    float length = Vector_length(a);
    t.a = a.a/length;
    t.b = a.b/length;
    t.c = a.c/length;
    return t;
}

// 矩阵乘整数
Matrix_t Matrix_multk(Matrix_t a,float k)
{
    a.a.a *= k;
    a.a.b *= k;
    a.a.c *= k;
    a.b.a *= k;
    a.b.b *= k;
    a.b.c *= k;
    a.c.a *= k;
    a.c.b *= k;
    a.c.c *= k;
    return a;
}

// 矩阵乘向量
Vector_t Matrix_multVector(Matrix_t m,Vector_t b,bool transp)
{
    Vector_t t;
    if(transp)
    {
        t.a = m.a.a*b.a + m.a.b*b.b + m.a.c*b.c;
        t.b = m.b.a*b.a + m.b.b*b.b + m.b.c*b.c;
        t.c = m.c.a*b.a + m.c.b*b.b + m.c.c*b.c;    
        return t;
    }
    t.a = m.a.a*b.a + m.b.a*b.b + m.c.a*b.c;
    t.b = m.a.b*b.a + m.b.b*b.b + m.c.b*b.c;
    t.c = m.a.c*b.a + m.b.c*b.b + m.c.c*b.c;    
    return t;
}

// 矩阵的前两行与向量相乘
// 主要作用于compass的矫正上
Vector_t Matrix_multXYVextor(Matrix_t m,Vector_t b,bool transp)
{
    Vector_t t;
    // 正常时候的
    if(transp)
    {
        t.a = m.a.a*b.a + m.a.b*b.b + m.a.c*b.c;
        t.b = m.b.a*b.a + m.b.b*b.b + m.b.c*b.c;
        t.c = 0;
        return t;
    }
    t.a = m.a.a*b.a + m.b.a*b.b + m.c.a*b.c;
    t.b = m.a.b*b.a + m.b.b*b.b + m.c.b*b.c;
    t.c = 0;
    return t;
    
}

// 矩阵的最后一行与向量相乘
// 这个函数主要用于把标准重力场转移到机体坐标上 所以写的比较简单
// 但是我们先把接口接的标准一些
Vector_t Matrix_multZVextor(Matrix_t m,Vector_t b,bool transp)
{
    Vector_t t;
    if(transp)
    {
        t.a = m.a.c;
        t.b = m.b.c;
        t.c = m.c.c;
    }
    else
    {
        t.a = m.c.a * b.c;
        t.b = m.c.b * b.c;
        t.c = m.c.c * b.c;
    }
    return t;    
}

// 由四元数得到方向余弦矩阵
Matrix_t Matrix_quat2dcm(float quat[4])
{
    Matrix_t m;
    float q0q0 = fast_sq(quat[0]);
    float q1q1 = fast_sq(quat[1]);
    float q2q2 = fast_sq(quat[2]);
    float q3q3 = fast_sq(quat[3]);    
    float q0q1 = quat[0]*quat[1];
    float q0q2 = quat[0]*quat[2];
    float q0q3 = quat[0]*quat[3];
    float q1q2 = quat[1]*quat[2];
    float q1q3 = quat[1]*quat[3];    
    float q2q3 = quat[2]*quat[3];
    
    m.a.a = q0q0+q1q1-q2q2-q3q3;
    m.a.b = 2*(q1q2-q0q3);
    m.a.c = 2*(q1q3+q0q2);
    m.b.a = 2*(q1q2+q0q3);
    m.b.b = q0q0-q1q1+q2q2-q3q3;
    m.b.c = 2*(q2q3-q0q1);
    m.c.a = 2*(q1q3-q0q2);
    m.c.b = 2*(q2q3+q0q1);
    m.c.c = q0q0-q1q1-q2q2+q3q3;
    return m;
}

Matrix_t Matrix_update(Matrix_t m,Vector_t v)
{
    Matrix_t _m;
    _m.a.a = m.a.b * v.c - m.a.c * v.b;
    _m.a.b = m.a.c * v.a - m.a.a * v.c;
    _m.a.c = m.a.a * v.b - m.a.b * v.a;
    _m.b.a = m.b.b * v.c - m.b.c * v.b;
    _m.b.b = m.b.c * v.a - m.b.a * v.c;
    _m.b.c = m.b.a * v.b - m.b.b * v.a;
    _m.c.a = m.c.b * v.c - m.c.c * v.b;
    _m.c.b = m.c.c * v.a - m.c.a * v.c;
    _m.c.c = m.c.a * v.b - m.c.b * v.a;
    
    _m.a.a += m.a.a;
    _m.a.b += m.a.b;
    _m.a.c += m.a.c;
    _m.b.a += m.b.a;
    _m.b.b += m.b.b;
    _m.b.c += m.b.c;
    _m.c.a += m.c.a;
    _m.c.b += m.c.b;
    _m.c.c += m.c.c;

    return _m;
}
