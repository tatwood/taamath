/**
 * @brief     inlined 3x3 matrix functions header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_MAT33_H_
#define taa_MAT33_H_

#include "vec3.h"

//****************************************************************************
// forward declarations

taa_INLINE static void taa_mat33_add(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* m_out);

taa_INLINE static float taa_mat33_determinant(
    const taa_mat33* m);

taa_INLINE static void taa_mat33_axisangle(
    float rad, 
    const taa_vec3* axis,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_from_mat44(
    const taa_mat44* a,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_pitch(
    float pitch,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_from_quat(
    const taa_quat* q,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_roll(
    float roll,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_from_scale(
    const taa_vec3* scale,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_yaw(
    float yaw,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_identity(
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_inverse(
    const taa_mat33* a,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_multiply(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_orthonormalize(
    const taa_mat33* a,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_scale(
    const taa_mat33* a,
    float x,
    taa_mat33* m_out);

taa_INLINE static void taa_mat33_subtract(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* m_out);

/** Multiplies a matrix by a column vector
 */
taa_INLINE static void taa_mat33_transform_vec3(
    const taa_mat33* a,
    const taa_vec3* b,
    taa_vec3* v_out);

taa_INLINE static void taa_mat33_transpose(
    const taa_mat33* a,
    taa_mat33* m_out);

//****************************************************************************
taa_INLINE static void taa_mat33_add(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* m_out)
{
    taa_vec3_add(&a->x, &b->x, &m_out->x);
    taa_vec3_add(&a->y, &b->y, &m_out->y);
    taa_vec3_add(&a->z, &b->z, &m_out->z);
}

//****************************************************************************
taa_INLINE static float taa_mat33_determinant(
    const taa_mat33* m)
{
    return
        + m->x.x * m->y.y * m->z.z
        + m->y.x * m->z.y * m->x.z
        + m->z.x * m->x.y * m->y.z
        - m->x.x * m->z.y * m->y.z
        - m->y.x * m->x.y * m->z.z
        - m->z.x * m->y.y * m->x.z;
}

//****************************************************************************
taa_INLINE static void taa_mat33_axisangle(
    float rad, 
    const taa_vec3* axis,
    taa_mat33* m_out)
{
    float c = cosf(rad);
    float s = sinf(rad);
    m_out->x.x = axis->x*axis->x*(1.0f-c) + c;
    m_out->x.y = axis->y*axis->x*(1.0f-c) + axis->z*s;
    m_out->x.z = axis->x*axis->z*(1.0f-c) - axis->y*s;

    m_out->y.x = axis->x*axis->y*(1.0f-c) - axis->z*s;
    m_out->y.y = axis->y*axis->y*(1.0f-c) + c;
    m_out->y.z = axis->y*axis->z*(1.0f-c) + axis->x*s;

    m_out->z.x = axis->x*axis->z*(1.0f-c) + axis->y*s;
    m_out->z.y = axis->y*axis->z*(1.0f-c) - axis->x*s;
    m_out->z.z = axis->z*axis->z*(1.0f-c) + c;
}

//****************************************************************************
taa_INLINE static void taa_mat33_from_mat44(
    const taa_mat44* a,
    taa_mat33* m_out)
{
    taa_vec3_set(a->x.x, a->x.y, a->x.z, &m_out->x);
    taa_vec3_set(a->y.x, a->y.y, a->y.z, &m_out->y);
    taa_vec3_set(a->z.x, a->z.y, a->z.z, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_pitch(
    float pitch,
    taa_mat33* m_out)
{
    /*  1  0  0
     *  0  c -s
     *  0  s  c
     */
    float c = cosf(pitch);
    float s = sinf(pitch);
    // columns
    taa_vec3_set(1.0f, 0.0f, 0.0f, &m_out->x);
    taa_vec3_set(0.0f,    c,    s, &m_out->y);
    taa_vec3_set(0.0f,   -s,    c, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_from_quat(
    const taa_quat* q,
    taa_mat33* m_out)
{
    float xx = 2.0f * q->x * q->x;
    float xy = 2.0f * q->y * q->x;
    float xz = 2.0f * q->z * q->x;
    float yy = 2.0f * q->y * q->y;
    float yz = 2.0f * q->z * q->y;
    float zz = 2.0f * q->z * q->z;
    float wx = 2.0f * q->x * q->w;
    float wy = 2.0f * q->y * q->w;
    float wz = 2.0f * q->z * q->w;
    // columns
    taa_vec3_set(1.0f - (yy+zz),          xy+wz,          xz-wy, &m_out->x);
    taa_vec3_set(         xy-wz, 1.0f - (xx+zz),          yz+wx, &m_out->y);
    taa_vec3_set(         xz+wy,          yz-wx, 1.0f - (xx+yy), &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_roll(
    float roll,
    taa_mat33* m_out)
{
    /*  c -s  0
     *  s  c  0
     *  0  0  1
     */
    float c = cosf(roll);
    float s = sinf(roll);
    // columns    
    taa_vec3_set(    c,    s, 0.0f, &m_out->x);
    taa_vec3_set(   -s,    c, 0.0f, &m_out->y);
    taa_vec3_set( 0.0f, 0.0f, 1.0f, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_from_scale(
    const taa_vec3* scale,
    taa_mat33* m_out)
{
    // columns
    taa_vec3_set(scale->x,     0.0f,     0.0f, &m_out->x);
    taa_vec3_set(    0.0f, scale->y,     0.0f, &m_out->y);
    taa_vec3_set(    0.0f,     0.0f, scale->z, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_yaw(
    float yaw,
    taa_mat33* m_out)
{
    /*  c  0  s
     *  0  1  0
     * -s  0  c
     */
    float c = cosf(yaw);
    float s = sinf(yaw);
    // columns    
    taa_vec3_set(   c, 0.0f,   -s, &m_out->x);
    taa_vec3_set(0.0f, 1.0f, 0.0f, &m_out->y);
    taa_vec3_set(   s, 0.0f,    c, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_identity(
    taa_mat33* m_out)
{
    // columns
    taa_vec3_set(1.0f, 0.0f, 0.0f, &m_out->x);
    taa_vec3_set(0.0f, 1.0f, 0.0f, &m_out->y);
    taa_vec3_set(0.0f, 0.0f, 1.0f, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_inverse(
    const taa_mat33* a,
    taa_mat33* m_out)
{
    float d = 1.0f/taa_mat33_determinant(a);
    assert(a != m_out);
    m_out->x.x = (a->y.y*a->z.z - a->y.z*a->z.y)*d;
    m_out->x.y = (a->x.z*a->z.y - a->x.y*a->z.z)*d;
    m_out->x.z = (a->x.y*a->y.z - a->x.z*a->y.y)*d;
    m_out->y.x = (a->y.z*a->z.x - a->y.x*a->z.z)*d;
    m_out->y.y = (a->x.x*a->z.z - a->x.z*a->z.x)*d;
    m_out->y.z = (a->x.z*a->y.x - a->x.x*a->y.z)*d;
    m_out->z.x = (a->y.x*a->z.y - a->y.y*a->z.x)*d;
    m_out->z.y = (a->x.y*a->z.x - a->x.x*a->z.y)*d;
    m_out->z.z = (a->x.x*a->y.y - a->x.y*a->y.x)*d;
}

//****************************************************************************
taa_INLINE static void taa_mat33_multiply(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* m_out)
{
    assert(a != m_out);
    assert(b != m_out);
    m_out->x.x = a->x.x*b->x.x + a->y.x*b->x.y + a->z.x*b->x.z;
    m_out->x.y = a->x.y*b->x.x + a->y.y*b->x.y + a->z.y*b->x.z;
    m_out->x.z = a->x.z*b->x.x + a->y.z*b->x.y + a->z.z*b->x.z;
    m_out->y.x = a->x.x*b->y.x + a->y.x*b->y.y + a->z.x*b->y.z;
    m_out->y.y = a->x.y*b->y.x + a->y.y*b->y.y + a->z.y*b->y.z;
    m_out->y.z = a->x.z*b->y.x + a->y.z*b->y.y + a->z.z*b->y.z;
    m_out->z.x = a->x.x*b->z.x + a->y.x*b->z.y + a->z.x*b->z.z;
    m_out->z.y = a->x.y*b->z.x + a->y.y*b->z.y + a->z.y*b->z.z;
    m_out->z.z = a->x.z*b->z.x + a->y.z*b->z.y + a->z.z*b->z.z;
}

//****************************************************************************
taa_INLINE static void taa_mat33_orthonormalize(
    const taa_mat33* a,
    taa_mat33* m_out)
{
    // col0' = |col0|
    // col1' = |col1 - dot(col0', col1) col0'|
    // col2' = |col2 - dot(col0', col2) col0' - dot(col1', col2) col1'|
    taa_vec3 u;
    taa_vec3 v;

    taa_vec3_normalize(&a->x, &m_out->x);

    taa_vec3_scale(&m_out->x, taa_vec3_dot(&m_out->x, &a->y), &v);
    taa_vec3_subtract(&a->y, &v, &m_out->y);
    taa_vec3_normalize(&m_out->y, &m_out->y);

    taa_vec3_scale(&m_out->x, taa_vec3_dot(&m_out->x, &a->z), &u);
    taa_vec3_scale(&m_out->y, taa_vec3_dot(&m_out->y, &a->z), &v);
    taa_vec3_subtract(&a->z, &u, &m_out->z);
    taa_vec3_subtract(&m_out->z, &v, &m_out->z);
    taa_vec3_normalize(&m_out->z, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_scale(
    const taa_mat33* a,
    float x,
    taa_mat33* m_out)
{
    taa_vec3_scale(&a->x, x, &m_out->x);
    taa_vec3_scale(&a->y, x, &m_out->y);
    taa_vec3_scale(&a->z, x, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_subtract(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* m_out)
{
    taa_vec3_subtract(&a->x, &b->x, &m_out->x);
    taa_vec3_subtract(&a->y, &b->y, &m_out->y);
    taa_vec3_subtract(&a->z, &b->z, &m_out->z);
}

//****************************************************************************
taa_INLINE static void taa_mat33_transform_vec3(
    const taa_mat33* a,
    const taa_vec3* b,
    taa_vec3* v_out)
{
    assert(&a->x > v_out || &a->z < v_out);
    assert(b != v_out);
    v_out->x = a->x.x*b->x + a->y.x*b->y + a->z.x*b->z;
    v_out->y = a->x.y*b->x + a->y.y*b->y + a->z.y*b->z;
    v_out->z = a->x.z*b->x + a->y.z*b->y + a->z.z*b->z;
}

//****************************************************************************
taa_INLINE static void taa_mat33_transpose(
    const taa_mat33* a,
    taa_mat33* m_out)
{
    assert(a != m_out);
    taa_vec3_set(a->x.x, a->y.x, a->z.x, &m_out->x);
    taa_vec3_set(a->x.y, a->y.y, a->z.y, &m_out->y);
    taa_vec3_set(a->x.z, a->y.z, a->z.z, &m_out->z);
}

#endif // taa_MAT33_H_
