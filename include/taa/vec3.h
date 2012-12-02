/**
 * @brief     inlined 3 dimensional vector functions header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_VEC3_H_
#define taa_VEC3_H_

#include "mathdefs.h"
#include <assert.h>
#include <float.h>

//****************************************************************************
// forward declarations

taa_INLINE static void taa_vec3_add(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out);

taa_INLINE static void taa_vec3_cross(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out);

taa_INLINE static void taa_vec3_divide(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out);

taa_INLINE static float taa_vec3_dot(
    const taa_vec3* a,
    const taa_vec3* b);

taa_INLINE static void taa_vec3_from_mat33_scale(
    const taa_mat33* a,
    taa_vec3* v_out);

taa_INLINE static float taa_vec3_length(
    const taa_vec3* a);

taa_INLINE static void taa_vec3_mix(
    const taa_vec3* a,
    const taa_vec3* b,
    float x,
    taa_vec3* v_out);

taa_INLINE static void taa_vec3_multiply(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out);

taa_INLINE static void taa_vec3_negate(
    const taa_vec3* a,
    taa_vec3* v_out);

taa_INLINE static void taa_vec3_normalize(
    const taa_vec3* a,
    taa_vec3* v_out);

taa_INLINE static void taa_vec3_scale(
    const taa_vec3* a,
    float x,
    taa_vec3* v_out);

taa_INLINE static void taa_vec3_set(
    float x, 
    float y, 
    float z, 
    taa_vec3* v_out);

taa_INLINE static void taa_vec3_subtract(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out);

//****************************************************************************
taa_INLINE static void taa_vec3_add(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out)
{
    v_out->x = a->x + b->x;
    v_out->y = a->y + b->y;
    v_out->z = a->z + b->z;
}

//****************************************************************************
taa_INLINE static void taa_vec3_cross(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out)
{
    assert(a != v_out);
    assert(b != v_out);
    v_out->x = a->y*b->z-a->z*b->y;
    v_out->y = a->z*b->x-a->x*b->z;
    v_out->z = a->x*b->y-a->y*b->x;
}

//****************************************************************************
taa_INLINE static void taa_vec3_divide(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out)
{
    v_out->x = a->x / b->x;
    v_out->y = a->y / b->y;
    v_out->z = a->z / b->z;
}

//****************************************************************************
taa_INLINE static float taa_vec3_dot(
    const taa_vec3* a,
    const taa_vec3* b)
{
    return a->x*b->x + a->y*b->y + a->z*b->z;
}

//****************************************************************************
taa_INLINE static void taa_vec3_from_mat33_scale(
    const taa_mat33* a,
    taa_vec3* v_out)
{
    v_out->x = taa_vec3_length(&a->x);
    v_out->y = taa_vec3_length(&a->y);
    v_out->z = taa_vec3_length(&a->z);
}

//****************************************************************************
taa_INLINE static float taa_vec3_length(
    const taa_vec3* a)
{
    return sqrtf(a->x*a->x + a->y*a->y + a->z*a->z);
}

//****************************************************************************
taa_INLINE static void taa_vec3_mix(
    const taa_vec3* a,
    const taa_vec3* b,
    float x,
    taa_vec3* v_out)
{
    v_out->x = a->x*(1.0f-x) + b->x*x;
    v_out->y = a->y*(1.0f-x) + b->y*x;
    v_out->z = a->z*(1.0f-x) + b->z*x;
}

//****************************************************************************
taa_INLINE static void taa_vec3_multiply(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out)
{
    v_out->x = a->x * b->x;
    v_out->y = a->y * b->y;
    v_out->z = a->z * b->z;
}

//****************************************************************************
taa_INLINE static void taa_vec3_negate(
    const taa_vec3* a,
    taa_vec3* v_out)
{
    v_out->x = -a->x;
    v_out->y = -a->y;
    v_out->z = -a->z;
}

//****************************************************************************
taa_INLINE static void taa_vec3_normalize(
    const taa_vec3* a,
    taa_vec3* v_out)
{
    taa_vec3_scale(a, 1.0f/(taa_vec3_length(a) + FLT_MIN), v_out);
}

//****************************************************************************
taa_INLINE static void taa_vec3_scale(
    const taa_vec3* a,
    float x,
    taa_vec3* v_out)
{
    v_out->x = a->x * x;
    v_out->y = a->y * x;
    v_out->z = a->z * x;
}

//****************************************************************************
taa_INLINE static void taa_vec3_set(
    float x, 
    float y, 
    float z, 
    taa_vec3* v_out)
{
    v_out->x = x;
    v_out->y = y;
    v_out->z = z;
}

//****************************************************************************
taa_INLINE static void taa_vec3_subtract(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* v_out)
{
    v_out->x = a->x - b->x;
    v_out->y = a->y - b->y;
    v_out->z = a->z - b->z;
}

#endif // taa_VEC3_H_
