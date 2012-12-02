/**
 * @brief     inlined quaternion functions header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_QUAT_H_
#define taa_QUAT_H_

#include "vec3.h"
#include "vec4.h"
#include <assert.h>

//****************************************************************************
// forward declarations

taa_INLINE static void taa_quat_add(
    const taa_quat* a,
    const taa_quat* b,
    taa_quat* q_out);

taa_INLINE static void taa_quat_conjugate(
    const taa_quat* a,
    taa_quat* q_out);

taa_INLINE static void taa_quat_axisangle(
    float rad,
    const taa_vec4* axis,
    taa_quat* q_out);

taa_INLINE static void taa_quat_from_mat33(
    const taa_mat33* m,
    taa_quat* q_out);

taa_INLINE static void taa_quat_from_mat44(
    const taa_mat44* m,
    taa_quat* q_out);

taa_INLINE static void taa_quat_identity(
    taa_quat* q_out);

taa_INLINE static void taa_quat_multiply(
    const taa_quat* a,
    const taa_quat* b,
    taa_quat* q_out);

taa_INLINE static void taa_quat_multiply_vec3(
    const taa_quat* a,
    const taa_vec3* b,
    taa_quat* q_out);

taa_INLINE static void taa_quat_normalize(
    const taa_quat* a,
    taa_quat* q_out);

taa_INLINE static void taa_quat_to_axis_angle(
    const taa_quat* a,
    taa_vec4* aa_out);

taa_INLINE static void taa_quat_transform_vec3(
    const taa_quat* a,
    const taa_vec3* b,
    taa_vec3* v_out);

taa_INLINE static void taa_quat_transform_vec4(
    const taa_quat* a,
    const taa_vec4* b,
    taa_vec4* v_out);

taa_INLINE static void taa_quat_scale(
    const taa_quat* a,
    float x,
    taa_quat* q_out);

//****************************************************************************
taa_INLINE static void taa_quat_add(
    const taa_quat* a,
    const taa_quat* b,
    taa_quat* q_out)
{
    q_out->x = a->x + b->x;
    q_out->y = a->y + b->y;
    q_out->z = a->z + b->z;
    q_out->w = a->w + b->w;
}

//****************************************************************************
taa_INLINE static void taa_quat_conjugate(
    const taa_quat* a,
    taa_quat* q_out)
{
    q_out->x = -a->x;
    q_out->y = -a->y;
    q_out->z = -a->z;
    q_out->w =  a->w;
}

//****************************************************************************
taa_INLINE static void taa_quat_axisangle(
    float rad,
    const taa_vec4* axis,
    taa_quat* q_out)
{
    float a = rad * 0.5f;
    float s = sinf(a);
    q_out->x = axis->x * s;
    q_out->y = axis->y * s;
    q_out->z = axis->z * s;
    q_out->w = cosf(a);
}

//****************************************************************************
taa_INLINE static void taa_quat_from_mat33(
    const taa_mat33* m,
    taa_quat* q_out)
{
    float trace = m->x.x + m->y.y + m->z.z;
    if (trace >= 0.0f)
    {
        float s = sqrtf(trace + 1.0f) * 0.5f;
        float t = 0.25f/s;
        q_out->x = (m->y.z - m->z.y) * t;
        q_out->y = (m->z.x - m->x.z) * t;
        q_out->z = (m->x.y - m->y.x) * t;
        q_out->w = s;
    }
    else if((m->x.x > m->y.y) && (m->x.x > m->z.z))
    {
        // s=4*x
        float s = sqrtf(1.0f+m->x.x-m->y.y-m->z.z) * 0.5f;
        float t = 0.25f/s;
        q_out->x = s;
        q_out->y = (m->y.x + m->x.y) * t;
        q_out->z = (m->x.z + m->z.x) * t;
        q_out->w = (m->y.z - m->z.y) * t;
    }
    else if(m->y.y > m->z.z)
    {
        // s=4*y
        float s = sqrtf(1.0f+m->y.y-m->x.x-m->z.z) * 0.5f;
        float t = 0.25f/s;
        q_out->x = (m->y.x + m->x.y) * t;
        q_out->y = s;
        q_out->z = (m->z.y + m->y.z) * t;
        q_out->w = (m->z.x - m->x.z) * t;
    }
    else
    {
        // s=4*z
        float s = sqrtf(1.0f+m->z.z-m->x.x-m->y.y) * 0.5f;
        float t = 0.25f/s;
        q_out->x = (m->z.x + m->x.z) * t;
        q_out->y = (m->z.y + m->y.z) * t;
        q_out->z = s;
        q_out->w = (m->x.y - m->y.x) * t;
    }
}

//****************************************************************************
taa_INLINE static void taa_quat_from_mat44(
    const taa_mat44* m,
    taa_quat* q_out)
{
    float trace = m->x.x + m->y.y + m->z.z;
    if (trace >= 0.0f)
    {
        float s = sqrtf(trace + 1.0f) * 0.5f;
        float t = 0.25f/s;
        q_out->x = (m->y.z - m->z.y) * t;
        q_out->y = (m->z.x - m->x.z) * t;
        q_out->z = (m->x.y - m->y.x) * t;
        q_out->w = s;
    }
    else if((m->x.x > m->y.y) && (m->x.x > m->z.z))
    {
        // s=4*x
        float s = sqrtf(1.0f+m->x.x-m->y.y-m->z.z) * 0.5f;
        float t = 0.25f/s;
        q_out->x = s;
        q_out->y = (m->y.x + m->x.y) * t;
        q_out->z = (m->x.z + m->z.x) * t;
        q_out->w = (m->y.z - m->z.y) * t;
    }
    else if(m->y.y > m->z.z)
    {
        // s=4*y
        float s = sqrtf(1.0f+m->y.y-m->x.x-m->z.z) * 0.5f;
        float t = 0.25f/s;
        q_out->x = (m->y.x + m->x.y) * t;
        q_out->y = s;
        q_out->z = (m->z.y + m->y.z) * t;
        q_out->w = (m->z.x - m->x.z) * t;
    }
    else
    {
        // s=4*z
        float s = sqrtf(1.0f+m->z.z-m->x.x-m->y.y) * 0.5f;
        float t = 0.25f/s;
        q_out->x = (m->z.x + m->x.z) * t;
        q_out->y = (m->z.y + m->y.z) * t;
        q_out->z = s;
        q_out->w = (m->x.y - m->y.x) * t;
    }
}

//****************************************************************************
taa_INLINE static void taa_quat_identity(
    taa_quat* q_out)
{
    q_out->x = 0.0f;
    q_out->y = 0.0f;
    q_out->z = 0.0f;
    q_out->w = 1.0f;
}

//****************************************************************************
taa_INLINE static void taa_quat_multiply(
    const taa_quat* a,
    const taa_quat* b,
    taa_quat* q_out)
{
    assert(a != q_out);
    assert(b != q_out);
    q_out->x = a->y*b->z - a->z*b->y + a->w*b->x + a->x*b->w;
    q_out->y = a->z*b->x - a->x*b->z + a->w*b->y + a->y*b->w;
    q_out->z = a->x*b->y - a->y*b->x + a->w*b->z + a->z*b->w;
    q_out->w = a->w*b->w - a->x*b->x - a->y*b->y - a->z*b->z;
}

//****************************************************************************
taa_INLINE static void taa_quat_multiply_vec3(
    const taa_quat* a,
    const taa_vec3* b,
    taa_quat* q_out)
{
    assert(a != q_out);
    q_out->x = a->w * b->x + a->y * b->z - a->z * b->y;
    q_out->y = a->w * b->y + a->z * b->x - a->x * b->z;
    q_out->z = a->w * b->z + a->x * b->y - a->y * b->x;
    q_out->w =-a->x * b->x - a->y * b->y - a->z * b->z;
}

//****************************************************************************
taa_INLINE static void taa_quat_normalize(
    const taa_quat* a,
    taa_quat* q_out)
{
    float len = sqrtf(a->x*a->x+a->y*a->y+a->z*a->z+a->w*a->w);
    taa_quat_scale(a, 1.0f/len, q_out);
}

//****************************************************************************
taa_INLINE static void taa_quat_to_axis_angle(
    const taa_quat* a,
    taa_vec4* aa_out)
{
    float qw = a->w;
    float div = 1.0f - (qw*qw);
    if(div > 0.0f)
    {
        div = 1.0f/((float)sqrt(div));
        aa_out->x = a->x * div;
        aa_out->y = a->y * div;
        aa_out->z = a->z * div;
        aa_out->w = 2.0f * ((float)acos(qw));
    }
    else
    {
        taa_vec4_set(0.0f,1.0f,0.0f,0.0f,aa_out);
    }
}

//****************************************************************************
taa_INLINE static void taa_quat_transform_vec3(
    const taa_quat* a,
    const taa_vec3* b,
    taa_vec3* v_out)
{
    // v' = 2 * cross(q.xyz, (cross(q.xyz, v) + v*q.w)) + v
    const taa_vec3* q = (const taa_vec3*) a;
    taa_vec3 qxv;
    assert(b != v_out);
    taa_vec3_cross(q, b, &qxv);
    taa_vec3_scale(b, a->w, v_out);
    taa_vec3_add(&qxv, v_out, v_out);
    taa_vec3_cross(q, v_out, &qxv);
    taa_vec3_scale(&qxv, 2.0f, v_out);
    taa_vec3_add(v_out, b, v_out);
}

//****************************************************************************
taa_INLINE static void taa_quat_transform_vec4(
    const taa_quat* a,
    const taa_vec4* b,
    taa_vec4* v_out)
{
    // v' = 2 * cross(q.xyz, (cross(q.xyz, v) + v*q.w)) + v
    const taa_vec4* q = (const taa_vec4*) a;
    taa_vec4 qxv;
    assert(b != v_out);
    taa_vec4_cross3(q, b, &qxv);
    taa_vec4_scale(b, a->w, v_out);
    taa_vec4_add(&qxv, v_out, v_out);
    taa_vec4_cross3(q, v_out, &qxv);
    taa_vec4_scale(&qxv, 2.0f, v_out);
    taa_vec4_add(v_out, b, v_out);
}

//****************************************************************************
taa_INLINE static void taa_quat_scale(
    const taa_quat* a,
    float x,
    taa_quat* q_out)
{
    q_out->x = a->x * x;
    q_out->y = a->y * x;
    q_out->z = a->z * x;
    q_out->w = a->w * x;
}

#endif // taa_QUAT_H_

