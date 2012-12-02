#ifndef TESTUTIL_H_
#define TESTUTIL_H_

#include <taa/log.h>
#include <taa/mat33.h>
#include <taa/mat44.h>
#include <taa/quat.h>
#include <float.h>
#include <stdlib.h>

#define TEST_EPSILON ((FLT_EPSILON)*100.0f)

//****************************************************************************
static float randf()
{
    return rand() / ((float) RAND_MAX);
}

//****************************************************************************
static void rand_vec3(
    taa_vec3* v_out)
{
    v_out->x = randf();
    v_out->y = randf();
    v_out->z = randf();
}

//****************************************************************************
static void rand_vec4(
    taa_vec4* v_out)
{
    v_out->x = randf();
    v_out->y = randf();
    v_out->z = randf();
    v_out->w = randf();
}

//****************************************************************************
static void rand_mat33(
    taa_mat33* m_out)
{
    rand_vec3(&m_out->x);
    rand_vec3(&m_out->y);
    rand_vec3(&m_out->z);
}

//****************************************************************************
static void rand_mat44(
    taa_mat44* m_out)
{
    rand_vec4(&m_out->x);
    rand_vec4(&m_out->y);
    rand_vec4(&m_out->z);
    rand_vec4(&m_out->w);
}

//****************************************************************************
static int cmp_float(
    const float a,
    const float b,
    float epsilon)
{
    int result = 0;
    float fd = a - b;
    if(fabs(fd) > epsilon)
    {
        taa_LOG_DEBUG("float value %f differs from %f by %f", a, b, fd);       
        result = 1;
    }
    return result;
}

//****************************************************************************
static int cmp_vec3(
    const taa_vec3* a,
    const taa_vec3* b,
    float epsilon)
{
    int result = 0;
    int i;
    for(i = 0; i < 3; ++i)
    {   
        float fa = (&a->x)[i];
        float fb = (&b->x)[i];
        float fd = fa - fb;
        if(fabs(fd) > epsilon)
        {
            const char el[3] = { 'x', 'y', 'z' };
            taa_LOG_DEBUG(
                "vec4 value a.%c (%f) differs from b.%c (%f) by %f", 
                el[i],
                fa,
                el[i],
                fb,
                fd);       
            result = 1;
        }
    }
    return result;
}

//****************************************************************************
static int cmp_vec4(
    const taa_vec4* a,
    const taa_vec4* b,
    float epsilon)
{
    int result = 0;
    int i;
    for(i = 0; i < 4; ++i)
    {   
        float fa = (&a->x)[i];
        float fb = (&b->x)[i];
        float fd = fa - fb;
        if(fabs(fd) > epsilon)
        {
            const char el[4] = { 'x', 'y', 'z', 'w' };
            taa_LOG_DEBUG(
                "vec4 value a.%c (%f) differs from b.%c (%f) by %f", 
                el[i],
                fa,
                el[i],
                fb,
                fd);       
            result = 1;
        }
    }
    return result;
}

//****************************************************************************
static int cmp_mat33(
    const taa_mat33* a,
    const taa_mat33* b,
    float epsilon)
{
    int result = 0;
    int i;
    for(i = 0; i < 3; ++i)
    {
        if(cmp_vec3((&a->x) + i, (&b->x) + i, epsilon))
        {
            const char el[3] = { 'x', 'y', 'z' };
            taa_LOG_DEBUG(
                "mat33 column a.%c differs from b.%c",
                el[i],
                el[i]);
            result = 1;
        }
    }
    return result;
}

//****************************************************************************
static int cmp_mat44(
    const taa_mat44* a,
    const taa_mat44* b,
    float epsilon)
{
    int result = 0;
    int i;
    for(i = 0; i < 4; ++i)
    {
        if(cmp_vec4((&a->x) + i, (&b->x) + i, epsilon))
        {
            const char el[4] = { 'x', 'y', 'z', 'w' };
            taa_LOG_DEBUG(
                "mat44 column a.%c differs from b.%c",
                el[i],
                el[i]);
            result = 1;
        }
    }
    return result;
}

#endif // TESTUTIL_H_

