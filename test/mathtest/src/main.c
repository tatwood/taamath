#if defined(_DEBUG) && defined(_MSC_FULL_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "testutil.h"
#include <taa/scalar.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#error asserts are not enabled
#endif

enum
{
    NUM_TEST_LOOPS = 16384
};

static void test_vec3_normalize()
{
    int i;
    taa_vec3 u;
    taa_vec3 v;
    // run a couple of tests to ensure that the div by 0 trick does not affect
    // accuracy
    taa_vec3_set(1.0f,0.0f,0.0f, &u);    
    taa_vec3_set(1.0f,0.0f,0.0f, &v);
    taa_vec3_normalize(&u, &u);
    assert(cmp_vec3(&u, &v, 0.0f) == 0);
    taa_vec3_set(0.0f,0.0f,0.0f, &u);
    taa_vec3_set(0.0f,0.0f,0.0f, &v);
    taa_vec3_normalize(&u, &u);
    assert(cmp_vec3(&u, &v, 0.0f) == 0); 
    // run the test loop
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        rand_vec3(&u);
        taa_vec3_set(0.5f,0.5f,0.5f, &v);
        taa_vec3_subtract(&u, &v, &u);
        taa_vec3_scale(&u, 4.0f, &u);
        taa_vec3_normalize(&u, &u);
        assert(cmp_scalar(taa_vec3_length(&u), 1.0f, TEST_EPSILON) == 0);
    }    
}

static void test_vec4_normalize()
{
    int i;
    taa_vec4 u;
    taa_vec4 v;
    // run a couple of tests to ensure that the div by 0 trick does not affect
    // accuracy
    taa_vec4_set(1.0f,0.0f,0.0f,0.0f, &u);    
    taa_vec4_set(1.0f,0.0f,0.0f,0.0f, &v);
    taa_vec4_normalize(&u, &u);
    assert(cmp_vec4(&u, &v, 5e-4f) == 0);
    taa_vec4_set(0.0f,0.0f,0.0f,0.0f, &u);
    taa_vec4_set(0.0f,0.0f,0.0f,0.0f, &v);
    taa_vec4_normalize(&u, &u);
    assert(cmp_vec4(&u, &v, 0.0f) == 0); 
    // run the test loop
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        rand_vec4(&u);
        taa_vec4_set(0.5f,0.5f,0.5f,0.5f, &v);
        taa_vec4_subtract(&u, &v, &u);
        taa_vec4_scale(&u, 4.0f, &u);
        taa_vec4_normalize(&u, &u);
        assert(cmp_scalar(taa_vec4_length(&u),1.0f, TEST_EPSILON) == 0);
    }    
}

static void test_mat33_inverse()
{
    int i;
    uint32_t numtests = 0;
    taa_mat33 I;
    taa_mat33_identity(&I);
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        taa_mat33 M;
        taa_mat33 N;
        rand_mat33(&M);
        taa_vec3_set(0.5f, 0.5f, 0.5f, &N.x);
        taa_vec3_set(0.5f, 0.5f, 0.5f, &N.y);
        taa_vec3_set(0.5f, 0.5f, 0.5f, &N.z);
        taa_mat33_subtract(&M, &N, &M);
        taa_vec3_normalize(&M.x, &M.x);
        taa_vec3_normalize(&M.y, &M.y);
        taa_vec3_normalize(&M.z, &M.z);
        taa_mat33_scale(&M, 2.0f, &M);
        if(fabs(taa_mat33_determinant(&M)) > 1e-3f)
        {
            taa_mat33 Minv;
            taa_mat33_inverse(&M, &Minv);
            taa_mat33_multiply(&M, &Minv, &N);
            assert(cmp_mat33(&N, &I, 5e-4f) == 0);
            ++numtests;
        }
    }
    assert(numtests > 0);
}

static void test_mat44_inverse()
{
    int i;
    uint32_t numtests = 0;
    taa_mat44 I;
    taa_mat44_identity(&I);
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        taa_mat44 M;
        taa_mat44 N;
        rand_mat44(&M);
        taa_vec4_set(0.5f, 0.5f, 0.5f, 0.5f, &N.x);
        taa_vec4_set(0.5f, 0.5f, 0.5f, 0.5f, &N.y);
        taa_vec4_set(0.5f, 0.5f, 0.5f, 0.5f, &N.z);
        taa_vec4_set(0.5f, 0.5f, 0.5f, 0.5f, &N.w);
        taa_mat44_subtract(&M, &N, &M);
        taa_vec4_normalize(&M.x, &M.x);
        taa_vec4_normalize(&M.y, &M.y);
        taa_vec4_normalize(&M.z, &M.z);
        taa_vec4_normalize(&M.w, &M.w);        
        taa_mat44_scale(&M, 2.0f, &M);
        if(fabs(taa_mat44_determinant(&M)) > 1e-3f)
        {
            taa_mat44 Minv;
            taa_mat44_inverse(&M, &Minv);
            taa_mat44_multiply(&M, &Minv, &N);
            assert(cmp_mat44(&N, &I, 5e-4f) == 0);
            ++numtests;
        }
    }
    assert(numtests > 0);
}

static void test_mat44_from_quat()
{
    int i;
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        float rad = randf() * taa_PI * 0.5f;
        taa_quat q;
        taa_mat44 M;
        taa_vec4 axis;
        taa_vec4 t;
        taa_vec4 u;
        taa_vec4 v;
        rand_vec4(&t);
        rand_vec4(&axis);
        axis.w = 0.0f;
        taa_vec4_normalize(&axis, &axis);
        taa_quat_axisangle(rad, &axis, &q);
        taa_mat44_from_quat(&q, &M);
        taa_quat_transform_vec4(&q, &t, &u);
        taa_mat44_transform_vec4(&M, &t, &v);
        assert(cmp_vec4(&u, &v, TEST_EPSILON) == 0);
    }
}

static void test_quat_from_mat44()
{
    int i;
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        float rad = randf() * taa_PI * 0.5f;
        taa_quat q;
        taa_mat44 M;
        taa_vec4 axis;
        taa_vec4 t;
        taa_vec4 u;
        taa_vec4 v;
        rand_vec4(&t);
        rand_vec4(&axis);
        axis.w = 0.0f;
        taa_vec4_normalize(&axis, &axis);
        taa_mat44_axisangle(rad, &axis, &M);
        taa_quat_from_mat44(&M, &q);
        taa_mat44_transform_vec4(&M, &t, &u);
        taa_quat_transform_vec4(&q, &t, &v);
        assert(cmp_vec4(&u, &v, TEST_EPSILON) == 0);
    }
}

int main(int argc, char* argv[])
{
    printf("testing taa_vec3_normalize...");
    fflush(stdout); 
    test_vec3_normalize();
    printf("pass\n");
    printf("testing taa_vec4_normalize...");
    fflush(stdout); 
    test_vec4_normalize();
    printf("pass\n");    
    printf("testing taa_mat33_inverse...");
    fflush(stdout);     
    test_mat33_inverse();
    printf("pass\n");
    printf("testing taa_mat44_inverse...");
    fflush(stdout);     
    test_mat44_inverse();
    printf("pass\n");
    printf("testing taa_mat44_from_quat...");
    fflush(stdout);     
    test_mat44_from_quat();
    printf("pass\n");
    printf("testing taa_quat_from_mat44...");
    fflush(stdout);     
    test_quat_from_mat44();
    printf("pass\n"); 
          
#if defined(_DEBUG) && defined(_MSC_FULL_VER)
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtCheckMemory();
    _CrtDumpMemoryLeaks();
#endif
    return EXIT_SUCCESS;
}
