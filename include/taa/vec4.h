/**
 * @brief     inlined 4 dimensional vector functions header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_VEC4_H_
#define taa_VEC4_H_

#include "mathdefs.h"
#include "vpu.h"
#include <assert.h>
#include <float.h>

//****************************************************************************
// forward declarations

taa_INLINE static void taa_vec4_add(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_cross3(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_divide(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out);

taa_INLINE static float taa_vec4_dot(
    const taa_vec4* a,
    const taa_vec4* b);

taa_INLINE static void taa_vec4_from_mat44_scale(
    const taa_mat44* a,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_from_mat44_translate(
    const taa_mat44* a,
    taa_vec4* v_out);

taa_INLINE static float taa_vec4_length(
    const taa_vec4* a);

taa_INLINE static void taa_vec4_mix(
    const taa_vec4* a,
    const taa_vec4* b,
    float x,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_multiply(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_negate(
    const taa_vec4* a,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_normalize(
    const taa_vec4* a,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_scale(
    const taa_vec4* a,
    float x,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_set(
    float x,
    float y,
    float z,
    float w,
    taa_vec4* v_out);

taa_INLINE static void taa_vec4_subtract(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out);

//****************************************************************************
taa_INLINE static void taa_vec4_add(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out)
{
    taa_vpu_add(
        *((taa_vpu_vec4*) a),
        *((taa_vpu_vec4*) b),
        *((taa_vpu_vec4*) v_out));
}

//****************************************************************************
taa_INLINE static void taa_vec4_cross3(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out)
{
    assert(a != v_out);
    assert(b != v_out);
    taa_vpu_cross3(
        *((taa_vpu_vec4*) a),
        *((taa_vpu_vec4*) b),
        *((taa_vpu_vec4*) v_out));
}

//****************************************************************************
taa_INLINE static void taa_vec4_divide(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out)
{
    v_out->x = a->x / b->x;
    v_out->y = a->y / b->y;
    v_out->z = a->z / b->z;
    v_out->w = a->w / b->w;
}

//****************************************************************************
taa_INLINE static float taa_vec4_dot(
    const taa_vec4* a,
    const taa_vec4* b)
{
    float dp;
    taa_vpu_vec4 tmp0;
    taa_vpu_dot(*((taa_vpu_vec4*) a), *((taa_vpu_vec4*) b), tmp0);
    taa_vpu_store1(tmp0, &dp);
    return dp;
}

//****************************************************************************
taa_INLINE static void taa_vec4_from_mat44_scale(
    const taa_mat44* a,
    taa_vec4* v_out)
{
    v_out->x = taa_vec4_length(&a->x);
    v_out->y = taa_vec4_length(&a->y);
    v_out->z = taa_vec4_length(&a->z);
    v_out->w = 1.0f;
}

//****************************************************************************
taa_INLINE static void taa_vec4_from_mat44_translate(
    const taa_mat44* a,
    taa_vec4* v_out)
{
    *v_out = a->w;
    v_out->w = 0.0f;
}

//****************************************************************************
taa_INLINE static float taa_vec4_length(
    const taa_vec4* a)
{
    return sqrtf(a->x*a->x + a->y*a->y + a->z*a->z + a->w*a->w);
}

//****************************************************************************
taa_INLINE static void taa_vec4_mix(
    const taa_vec4* a,
    const taa_vec4* b,
    float x,
    taa_vec4* v_out)
{
    v_out->x = a->x*(1.0f-x) + b->x*x;
    v_out->y = a->y*(1.0f-x) + b->y*x;
    v_out->z = a->z*(1.0f-x) + b->z*x;
    v_out->w = a->w*(1.0f-x) + b->w*x;
}

//****************************************************************************
taa_INLINE static void taa_vec4_multiply(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out)
{
    taa_vpu_mul(
        *((taa_vpu_vec4*) a),
        *((taa_vpu_vec4*) b),
        *((taa_vpu_vec4*) v_out));
}

//****************************************************************************
taa_INLINE static void taa_vec4_negate(
    const taa_vec4* a,
    taa_vec4* v_out)
{
    v_out->x = -a->x;
    v_out->y = -a->y;
    v_out->z = -a->z;
    v_out->w = -a->w;
}

//****************************************************************************
taa_INLINE static void taa_vec4_normalize(
    const taa_vec4* a,
    taa_vec4* v_out)
{
    taa_vpu_normalize(*((taa_vpu_vec4*) a), *((taa_vpu_vec4*) v_out));
}

//****************************************************************************
taa_INLINE static void taa_vec4_scale(
    const taa_vec4* a,
    float x,
    taa_vec4* v_out)
{
    v_out->x = a->x * x;
    v_out->y = a->y * x;
    v_out->z = a->z * x;
    v_out->w = a->w * x;
}

//****************************************************************************
taa_INLINE static void taa_vec4_set(
    float x,
    float y,
    float z,
    float w,
    taa_vec4* v_out)
{
    v_out->x = x;
    v_out->y = y;
    v_out->z = z;
    v_out->w = w;
}

//****************************************************************************
taa_INLINE static void taa_vec4_subtract(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* v_out)
{
    taa_vpu_sub(
        *((taa_vpu_vec4*) a),
        *((taa_vpu_vec4*) b),
        *((taa_vpu_vec4*) v_out));
}

#endif // taa_VEC4_H_
