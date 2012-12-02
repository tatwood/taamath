/**
 * @brief     inlined scalar functions header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SCALAR_H_
#define taa_SCALAR_H_

#include "mathdefs.h"

//****************************************************************************
// forward declarations

taa_INLINE static float taa_clamp(
    float x,
    float min,
    float max);

taa_INLINE static int taa_clampi(
    int x,
    int min,
    int max);

taa_INLINE static float taa_degrees(
    float radians);

taa_INLINE static float taa_max(
    float a,
    float b);

taa_INLINE static int taa_maxi(
    int a,
    int b);

taa_INLINE static float taa_min(
    float a,
    float b);

taa_INLINE static int taa_mini(
    int a,
    int b);

taa_INLINE static float taa_mix(
    float x,
    float y,
    float a);

taa_INLINE static float taa_radians(
    float degrees);

taa_INLINE static float taa_clamp(
    float x,
    float min,
    float max)
{
    return (x > min) ? ((x < max) ? x : max) : min;
}

taa_INLINE static int taa_clampi(
    int x,
    int min,
    int max)
{
    return (x > min) ? ((x < max) ? x : max) : min;
}

taa_INLINE static float taa_degrees(
    float radians)
{
    return radians * (180.0f/taa_PI);
}

taa_INLINE static float taa_max(
    float a,
    float b)
{
    return (a > b) ? a : b;
}

taa_INLINE static int taa_maxi(
    int a,
    int b)
{
    return (a > b) ? a : b;
}


taa_INLINE static float taa_min(
    float a,
    float b)
{
    return (a < b) ? a : b;
}

taa_INLINE static int taa_mini(
    int a,
    int b)
{
    return (a < b) ? a : b;
}

taa_INLINE static float taa_mix(
    float x,
    float y,
    float a)
{
    return x*(1.0f - a) + y*a;
}

taa_INLINE static float taa_radians(
    float degrees)
{
    return degrees * (taa_PI/180.0f);
}

#endif // taa_SCALAR_H_
