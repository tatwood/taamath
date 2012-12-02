/**
 * @brief     header for inlined 4x4 matrix functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_MAT44_H_
#define taa_MAT44_H_

#include "vec4.h"
#include "vpu.h"

//****************************************************************************
// forward declarations

taa_INLINE static void taa_mat44_add(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* v_out);

taa_INLINE static float taa_mat44_determinant(
    const taa_mat44* a);

taa_INLINE static void taa_mat44_axisangle(
    float rad,
    const taa_vec4* axis,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_from_mat33(
    const taa_mat33* a,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_from_quat(
    const taa_quat* q,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_from_scale(
    const taa_vec4 *scale,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_from_translate(
    const taa_vec4* v,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_identity(
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_inverse(
    const taa_mat44* a,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_lookat(
    const taa_vec4* eye,
    const taa_vec4* target,
    const taa_vec4* up,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_multiply(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_orthonormalize(
    const taa_mat44* a,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_perspective(
    float fovy,
    float aspect,
    float znear,
    float zfar,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_pitch(
    float pitch,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_roll(
    float roll,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_scale(
    const taa_mat44* a,
    float x,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_subtract(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* m_out);

/**
 * @brief multiplies a matrix by a column vector
 * @details discards w component
 */
taa_INLINE static void taa_mat44_transform_vec3(
    const taa_mat44* a,
    const taa_vec3* b,
    taa_vec3* v_out);

/** 
 * @brief multiplies a matrix by a column vector
 */
taa_INLINE static void taa_mat44_transform_vec4(
    const taa_mat44* a,
    const taa_vec4* b,
    taa_vec4* v_out);

taa_INLINE static void taa_mat44_transpose(
    const taa_mat44* a,
    taa_mat44* m_out);

taa_INLINE static void taa_mat44_yaw(
    float yaw,
    taa_mat44* m_out);

//****************************************************************************
taa_INLINE static void taa_mat44_add(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* m_out)
{
    assert((((size_t) a) & 15) == 0);
    assert((((size_t) b) & 15) == 0);
    assert((((size_t) m_out) & 15) == 0);
    taa_vpu_add(
        *((taa_vpu_vec4*) &a->x),
        *((taa_vpu_vec4*) &b->x),
        *((taa_vpu_vec4*) &m_out->x));
    taa_vpu_add(
        *((taa_vpu_vec4*) &a->y),
        *((taa_vpu_vec4*) &b->y),
        *((taa_vpu_vec4*) &m_out->y));
    taa_vpu_add(
        *((taa_vpu_vec4*) &a->z),
        *((taa_vpu_vec4*) &b->z),
        *((taa_vpu_vec4*) &m_out->z));
    taa_vpu_add(
        *((taa_vpu_vec4*) &a->w),
        *((taa_vpu_vec4*) &b->w),
        *((taa_vpu_vec4*) &m_out->w));
}

//****************************************************************************
taa_INLINE static float taa_mat44_determinant(
    const taa_mat44* a)
{
    return
        + a->w.x * a->z.y * a->y.z * a->x.w
        - a->z.x * a->w.y * a->y.z * a->x.w
        - a->w.x * a->y.y * a->z.z * a->x.w
        + a->y.x * a->w.y * a->z.z * a->x.w
        + a->z.x * a->y.y * a->w.z * a->x.w
        - a->y.x * a->z.y * a->w.z * a->x.w
        - a->w.x * a->z.y * a->x.z * a->y.w
        + a->z.x * a->w.y * a->x.z * a->y.w
        + a->w.x * a->x.y * a->z.z * a->y.w
        - a->x.x * a->w.y * a->z.z * a->y.w
        - a->z.x * a->x.y * a->w.z * a->y.w
        + a->x.x * a->z.y * a->w.z * a->y.w
        + a->w.x * a->y.y * a->x.z * a->z.w
        - a->y.x * a->w.y * a->x.z * a->z.w
        - a->w.x * a->x.y * a->y.z * a->z.w
        + a->x.x * a->w.y * a->y.z * a->z.w
        + a->y.x * a->x.y * a->w.z * a->z.w
        - a->x.x * a->y.y * a->w.z * a->z.w
        - a->z.x * a->y.y * a->x.z * a->w.w
        + a->y.x * a->z.y * a->x.z * a->w.w
        + a->z.x * a->x.y * a->y.z * a->w.w
        - a->x.x * a->z.y * a->y.z * a->w.w
        - a->y.x * a->x.y * a->z.z * a->w.w
        + a->x.x * a->y.y * a->z.z * a->w.w;
}

//****************************************************************************
taa_INLINE static void taa_mat44_axisangle(
    float rad,
    const taa_vec4* axis,
    taa_mat44* m_out)
{
    float c = cosf(rad);
    float s = sinf(rad);
    m_out->x.x = axis->x*axis->x*(1.0f-c) + c;
    m_out->x.y = axis->y*axis->x*(1.0f-c) + axis->z*s;
    m_out->x.z = axis->x*axis->z*(1.0f-c) - axis->y*s;
    m_out->x.w = 0.0f;
    m_out->y.x = axis->x*axis->y*(1.0f-c) - axis->z*s;
    m_out->y.y = axis->y*axis->y*(1.0f-c) + c;
    m_out->y.z = axis->y*axis->z*(1.0f-c) + axis->x*s;
    m_out->y.w = 0.0f;
    m_out->z.x = axis->x*axis->z*(1.0f-c) + axis->y*s;
    m_out->z.y = axis->y*axis->z*(1.0f-c) - axis->x*s;
    m_out->z.z = axis->z*axis->z*(1.0f-c) + c;
    m_out->z.w = 0.0f;
    m_out->w.x = 0.0f;
    m_out->w.y = 0.0f;
    m_out->w.z = 0.0f;
    m_out->w.w = 1.0f;
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_mat33(
    const taa_mat33* a,
    taa_mat44* m_out)
{
    taa_vec4_set(a->x.x, a->x.y, a->x.z, 0.0f, &m_out->x);
    taa_vec4_set(a->y.x, a->y.y, a->y.z, 0.0f, &m_out->y);
    taa_vec4_set(a->z.x, a->z.y, a->z.z, 0.0f, &m_out->z);
    taa_vec4_set(  0.0f,   0.0f,   0.0f, 1.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_quat(
    const taa_quat* q,
    taa_mat44* m_out)
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
    taa_vec4_set(1.0f-(yy+zz),        xy+wz,        xz-wy, 0.0f, &m_out->x);
    taa_vec4_set(       xy-wz, 1.0f-(xx+zz),        yz+wx, 0.0f, &m_out->y);
    taa_vec4_set(       xz+wy,        yz-wx, 1.0f-(xx+yy), 0.0f, &m_out->z);
    taa_vec4_set(        0.0f,         0.0f,         0.0f, 1.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_scale(
    const taa_vec4 *scale,
    taa_mat44* m_out)
{
    // columns
    taa_vec4_set(scale->x,    0.0f,     0.0f, 0.0f, &m_out->x);
    taa_vec4_set(   0.0f, scale->y,     0.0f, 0.0f, &m_out->y);
    taa_vec4_set(   0.0f,     0.0f, scale->z, 0.0f, &m_out->z);
    taa_vec4_set(   0.0f,     0.0f,     0.0f, 1.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_translate(
    const taa_vec4* v,
    taa_mat44* m_out)
{
    // columns
    taa_vec4_set( 1.0f, 0.0f, 0.0f, 0.0f, &m_out->x);
    taa_vec4_set( 0.0f, 1.0f, 0.0f, 0.0f, &m_out->y);
    taa_vec4_set( 0.0f, 0.0f, 1.0f, 0.0f, &m_out->z);
    taa_vec4_set( v->x, v->y, v->z, 1.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_identity(
    taa_mat44* m_out)
{
    // columns
    taa_vec4_set(1.0f, 0.0f, 0.0f, 0.0f, &m_out->x);
    taa_vec4_set(0.0f, 1.0f, 0.0f, 0.0f, &m_out->y);
    taa_vec4_set(0.0f, 0.0f, 1.0f, 0.0f, &m_out->z);
    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_inverse(
    const taa_mat44* a,
    taa_mat44* m_out)
{
    float d = 1.0f/taa_mat44_determinant(a);
    assert(a != m_out);
    m_out->x.x = d *
        (a->z.y*a->w.z*a->y.w - a->w.y*a->z.z*a->y.w +
         a->w.y*a->y.z*a->z.w - a->y.y*a->w.z*a->z.w -
         a->z.y*a->y.z*a->w.w + a->y.y*a->z.z*a->w.w);
    m_out->x.y = d *
        (a->w.y*a->z.z*a->x.w - a->z.y*a->w.z*a->x.w -
         a->w.y*a->x.z*a->z.w + a->x.y*a->w.z*a->z.w +
         a->z.y*a->x.z*a->w.w - a->x.y*a->z.z*a->w.w);
    m_out->x.z = d *
        (a->y.y*a->w.z*a->x.w - a->w.y*a->y.z*a->x.w +
         a->w.y*a->x.z*a->y.w - a->x.y*a->w.z*a->y.w -
         a->y.y*a->x.z*a->w.w + a->x.y*a->y.z*a->w.w);
    m_out->x.w = d *
        (a->z.y*a->y.z*a->x.w - a->y.y*a->z.z*a->x.w -
         a->z.y*a->x.z*a->y.w + a->x.y*a->z.z*a->y.w +
         a->y.y*a->x.z*a->z.w - a->x.y*a->y.z*a->z.w);

    m_out->y.x = d *
        (a->w.x*a->z.z*a->y.w - a->z.x*a->w.z*a->y.w -
         a->w.x*a->y.z*a->z.w + a->y.x*a->w.z*a->z.w +
         a->z.x*a->y.z*a->w.w - a->y.x*a->z.z*a->w.w);
    m_out->y.y = d *
        (a->z.x*a->w.z*a->x.w - a->w.x*a->z.z*a->x.w +
         a->w.x*a->x.z*a->z.w - a->x.x*a->w.z*a->z.w -
         a->z.x*a->x.z*a->w.w + a->x.x*a->z.z*a->w.w);
    m_out->y.z =  d *
        (a->w.x*a->y.z*a->x.w - a->y.x*a->w.z*a->x.w -
         a->w.x*a->x.z*a->y.w + a->x.x*a->w.z*a->y.w +
         a->y.x*a->x.z*a->w.w - a->x.x*a->y.z*a->w.w);
    m_out->y.w = d *
        (a->y.x*a->z.z*a->x.w - a->z.x*a->y.z*a->x.w +
         a->z.x*a->x.z*a->y.w - a->x.x*a->z.z*a->y.w -
         a->y.x*a->x.z*a->z.w + a->x.x*a->y.z*a->z.w);

    m_out->z.x = d *
        (a->z.x*a->w.y*a->y.w - a->w.x*a->z.y*a->y.w +
         a->w.x*a->y.y*a->z.w - a->y.x*a->w.y*a->z.w -
         a->z.x*a->y.y*a->w.w + a->y.x*a->z.y*a->w.w);
    m_out->z.y = d *
        (a->w.x*a->z.y*a->x.w - a->z.x*a->w.y*a->x.w -
         a->w.x*a->x.y*a->z.w + a->x.x*a->w.y*a->z.w +
         a->z.x*a->x.y*a->w.w - a->x.x*a->z.y*a->w.w);
    m_out->z.z = d *
        (a->y.x*a->w.y*a->x.w - a->w.x*a->y.y*a->x.w +
         a->w.x*a->x.y*a->y.w - a->x.x*a->w.y*a->y.w -
         a->y.x*a->x.y*a->w.w + a->x.x*a->y.y*a->w.w);
    m_out->z.w = d *
        (a->z.x*a->y.y*a->x.w - a->y.x*a->z.y*a->x.w -
         a->z.x*a->x.y*a->y.w + a->x.x*a->z.y*a->y.w +
         a->y.x*a->x.y*a->z.w - a->x.x*a->y.y*a->z.w);

    m_out->w.x = d *
        (a->w.x*a->z.y*a->y.z - a->z.x*a->w.y*a->y.z -
         a->w.x*a->y.y*a->z.z + a->y.x*a->w.y*a->z.z +
         a->z.x*a->y.y*a->w.z - a->y.x*a->z.y*a->w.z);
    m_out->w.y = d *
        (a->z.x*a->w.y*a->x.z - a->w.x*a->z.y*a->x.z +
         a->w.x*a->x.y*a->z.z - a->x.x*a->w.y*a->z.z -
         a->z.x*a->x.y*a->w.z + a->x.x*a->z.y*a->w.z);
    m_out->w.z = d *
        (a->w.x*a->y.y*a->x.z - a->y.x*a->w.y*a->x.z -
         a->w.x*a->x.y*a->y.z + a->x.x*a->w.y*a->y.z +
         a->y.x*a->x.y*a->w.z - a->x.x*a->y.y*a->w.z);
    m_out->w.w = d *
        (a->y.x*a->z.y*a->x.z - a->z.x*a->y.y*a->x.z +
         a->z.x*a->x.y*a->y.z - a->x.x*a->z.y*a->y.z -
         a->y.x*a->x.y*a->z.z + a->x.x*a->y.y*a->z.z);
}

//****************************************************************************
taa_INLINE static void taa_mat44_lookat(
    const taa_vec4* eye,
    const taa_vec4* target,
    const taa_vec4* up,
    taa_mat44* m_out)
{
    taa_vec4 f;
    taa_vec4 s;
    taa_vec4 u;
    // calculate rotation
    taa_vec4_subtract(target, eye, &f);
    f.w = 0.0f;
    taa_vec4_normalize(&f, &f);
    taa_vec4_cross3(&f, up, &s);
    taa_vec4_normalize(&s, &s);
    taa_vec4_cross3(&s, &f, &u);
    taa_vec4_normalize(&u, &u);
    // columns
    taa_vec4_set(s.x,   u.x, -f.x, 0.0f, &m_out->x);
    taa_vec4_set(s.y,   u.y, -f.y, 0.0f, &m_out->y);
    taa_vec4_set(s.z,   u.z, -f.z, 0.0f, &m_out->z);
    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &m_out->w);
    // calculate translation
    taa_vec4_set(-eye->x, -eye->y, -eye->z, 1.0f, &f);
    taa_mat44_transform_vec4(m_out, &f, &s);
    m_out->w = s;
} 

//****************************************************************************
taa_INLINE static void taa_mat44_multiply(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* m_out)
{
    assert(a != m_out);
    assert(b != m_out);
    assert((((size_t) a) & 15) == 0);
    assert((((size_t) b) & 15) == 0);
    assert((((size_t) m_out) & 15) == 0);
    taa_vpu_mat44_mul_vec4(
        *((taa_vpu_vec4*) &a->x),
        *((taa_vpu_vec4*) &a->y),
        *((taa_vpu_vec4*) &a->z),
        *((taa_vpu_vec4*) &a->w),
        *((taa_vpu_vec4*) &b->x),
        *((taa_vpu_vec4*) &m_out->x));
    taa_vpu_mat44_mul_vec4(
        *((taa_vpu_vec4*) &a->x),
        *((taa_vpu_vec4*) &a->y),
        *((taa_vpu_vec4*) &a->z),
        *((taa_vpu_vec4*) &a->w),
        *((taa_vpu_vec4*) &b->y),
        *((taa_vpu_vec4*) &m_out->y));
    taa_vpu_mat44_mul_vec4(
        *((taa_vpu_vec4*) &a->x),
        *((taa_vpu_vec4*) &a->y),
        *((taa_vpu_vec4*) &a->z),
        *((taa_vpu_vec4*) &a->w),
        *((taa_vpu_vec4*) &b->z),
        *((taa_vpu_vec4*) &m_out->z));
    taa_vpu_mat44_mul_vec4(
        *((taa_vpu_vec4*) &a->x),
        *((taa_vpu_vec4*) &a->y),
        *((taa_vpu_vec4*) &a->z),
        *((taa_vpu_vec4*) &a->w),
        *((taa_vpu_vec4*) &b->w),
        *((taa_vpu_vec4*) &m_out->w));
}

//****************************************************************************
taa_INLINE static void taa_mat44_orthonormalize(
    const taa_mat44* a,
    taa_mat44* m_out)
{
    // col0' = |col0|
    // col1' = |col1 - dot(col0', col1) col0'|
    // col2' = |col2 - dot(col0', col2) col0' - dot(col1', col2) col1'|
    taa_vec4 t;
    taa_vec4 u;
    taa_vec4 v;

    t = a->x;
    t.w = 0.0f;
    taa_vec4_normalize(&t, &m_out->x);

    t = a->y;
    t.w = 0.0f;
    taa_vec4_scale(&m_out->x, taa_vec4_dot(&m_out->x, &t), &v);
    taa_vec4_subtract(&t, &v, &m_out->y);
    taa_vec4_normalize(&m_out->y, &m_out->y);

    t = a->z;
    t.w = 0.0f;
    taa_vec4_scale(&m_out->x, taa_vec4_dot(&m_out->x, &t), &u);
    taa_vec4_scale(&m_out->y, taa_vec4_dot(&m_out->y, &t), &v);
    taa_vec4_subtract(&t, &u, &m_out->z);
    taa_vec4_subtract(&m_out->z, &v, &m_out->z);
    taa_vec4_normalize(&m_out->z, &m_out->z);

    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_perspective(
    float fovy,
    float aspect,
    float znear,
    float zfar,
    taa_mat44* m_out)
{
    float rad = fovy * 0.5f;
    float cotan = cosf(rad) / sinf(rad);
    float dz = 1.0f/(znear - zfar);
    // columns
    taa_vec4_set(cotan/aspect,  0.0f,               0.0f,  0.0f, &m_out->x);
    taa_vec4_set(        0.0f, cotan,               0.0f,  0.0f, &m_out->y);
    taa_vec4_set(        0.0f,  0.0f,    (zfar+znear)*dz, -1.0f, &m_out->z);
    taa_vec4_set(        0.0f,  0.0f, 2.0f*znear*zfar*dz,  0.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_pitch(
    float pitch,
    taa_mat44* m_out)
{
    /*  1  0  0  0
     *  0  c -s  0
     *  0  s  c  0
     *  0  0  0  1
     */
    float c = cosf(pitch);
    float s = sinf(pitch);
    // columns
    taa_vec4_set(1.0f, 0.0f, 0.0f, 0.0f, &m_out->x);
    taa_vec4_set(0.0f,    c,    s, 0.0f, &m_out->y);
    taa_vec4_set(0.0f,   -s,    c, 0.0f, &m_out->z);
    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_roll(
    float roll,
    taa_mat44* m_out)
{
    /*  c -s  0  0
     *  s  c  0  0
     *  0  0  1  0
     *  0  0  0  1
     */
    float c = cosf(roll);
    float s = sinf(roll);
    // columns
    taa_vec4_set(   c,    s, 0.0f, 0.0f, &m_out->x);
    taa_vec4_set(  -s,    c, 0.0f, 0.0f, &m_out->y);
    taa_vec4_set(0.0f, 0.0f, 1.0f, 0.0f, &m_out->z);
    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_scale(
    const taa_mat44* a,
    float x,
    taa_mat44* m_out)
{
    taa_vec4_scale(&a->x, x, &m_out->x);
    taa_vec4_scale(&a->y, x, &m_out->y);
    taa_vec4_scale(&a->z, x, &m_out->z);
    taa_vec4_scale(&a->w, x, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_subtract(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* m_out)
{
    taa_vec4_subtract(&a->x, &b->x, &m_out->x);
    taa_vec4_subtract(&a->y, &b->y, &m_out->y);
    taa_vec4_subtract(&a->z, &b->z, &m_out->z);
    taa_vec4_subtract(&a->w, &b->w, &m_out->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_transform_vec3(
    const taa_mat44* a,
    const taa_vec3* b,
    taa_vec3* v_out)
{
    assert(((taa_vec3*) &a->x) > v_out || ((taa_vec3*) &a->w) < v_out);
    assert(b != v_out);
    v_out->x = a->x.x*b->x + a->y.x*b->y + a->z.x*b->z + a->w.x;
    v_out->y = a->x.y*b->x + a->y.y*b->y + a->z.y*b->z + a->w.y;
    v_out->z = a->x.z*b->x + a->y.z*b->y + a->z.z*b->z + a->w.z;
}

//****************************************************************************
taa_INLINE static void taa_mat44_transform_vec4(
    const taa_mat44* a,
    const taa_vec4* b,
    taa_vec4* v_out)
{
    assert(&a->x > v_out || &a->w < v_out);
    assert(b != v_out);
    assert((((size_t) a) & 15) == 0);
    assert((((size_t) b) & 15) == 0);
    assert((((size_t) v_out) & 15) == 0);
    taa_vpu_mat44_mul_vec4(
        *((taa_vpu_vec4*) &a->x),
        *((taa_vpu_vec4*) &a->y),
        *((taa_vpu_vec4*) &a->z),
        *((taa_vpu_vec4*) &a->w),
        *((taa_vpu_vec4*) b),
        *((taa_vpu_vec4*) v_out));
}

//****************************************************************************
taa_INLINE static void taa_mat44_transpose(
    const taa_mat44* a,
    taa_mat44* m_out)
{
    assert(a != m_out);
    assert((((size_t) a) & 15) == 0);
    assert((((size_t) m_out) & 15) == 0);
    taa_vpu_mat44_transpose(
        *((taa_vpu_vec4*) &a->x),
        *((taa_vpu_vec4*) &a->y),
        *((taa_vpu_vec4*) &a->z),
        *((taa_vpu_vec4*) &a->w),
        *((taa_vpu_vec4*) &m_out->x),
        *((taa_vpu_vec4*) &m_out->y),
        *((taa_vpu_vec4*) &m_out->z),
        *((taa_vpu_vec4*) &m_out->w));
}

//****************************************************************************
taa_INLINE static void taa_mat44_yaw(
    float yaw,
    taa_mat44* m_out)
{
    /*  c  0  s  0
     *  0  1  0  0
     * -s  0  c  0
     *  0  0  0  1
     */
    float c = cosf(yaw);
    float s = sinf(yaw);
    // columns
    taa_vec4_set(    c, 0.0f,   -s, 0.0f, &m_out->x);
    taa_vec4_set( 0.0f, 1.0f, 0.0f, 0.0f, &m_out->y);
    taa_vec4_set(    s, 0.0f,    c, 0.0f, &m_out->z);
    taa_vec4_set( 0.0f, 0.0f, 0.0f, 1.0f, &m_out->w);
}

#endif // taa_MATH_MAT44_H_
