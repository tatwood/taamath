#if defined(_DEBUG) && defined(_MSC_FULL_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "testutil.h"
#include <taa/scalar.h>
#include <taa/gl.h>
#include <taa/glcontext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#error asserts are not enabled
#endif

enum
{
    NUM_TEST_LOOPS = 16384
};

static void test_mat33_multiply()
{
    int i;
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        taa_mat33 A;
        taa_mat33 B;
        taa_mat33 M;
        taa_mat33 N;
        taa_mat44 A4;
        taa_mat44 B4;
        taa_mat44 N4;
        rand_mat33(&A);
        rand_mat33(&B);
        taa_vec3_set(0.5f, 0.5f, 0.5f, &M.x);
        taa_vec3_set(0.5f, 0.5f, 0.5f, &M.y);
        taa_vec3_set(0.5f, 0.5f, 0.5f, &M.z);
        taa_mat33_subtract(&A, &M, &A);
        taa_mat33_subtract(&B, &M, &B);
        taa_mat33_scale(&A, 2.0f, &A);
        taa_mat33_scale(&B, 2.0f, &B);
        taa_mat33_multiply(&A, &B, &M);
        taa_mat44_from_mat33(&A, &A4);
        taa_mat44_from_mat33(&B, &B4);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glLoadMatrixf(&A4.x.x);
        glMultMatrixf(&B4.x.x);
        glGetFloatv(GL_MODELVIEW_MATRIX, &N4.x.x);
        taa_mat33_from_mat44(&N4, &N);
        assert(cmp_mat33(&M, &N, TEST_EPSILON) == 0);
    }
}

static void test_mat44_multiply()
{
    int i;
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        taa_mat44 A;
        taa_mat44 B;
        taa_mat44 M;
        taa_mat44 N;
        rand_mat44(&A);        
        rand_mat44(&B);        
        taa_vec4_set(0.5f, 0.5f, 0.5f, 0.5f, &M.x);
        taa_vec4_set(0.5f, 0.5f, 0.5f, 0.5f, &M.y);
        taa_vec4_set(0.5f, 0.5f, 0.5f, 0.5f, &M.z);
        taa_vec4_set(0.5f, 0.5f, 0.5f, 0.5f, &M.w);
        taa_mat44_subtract(&A, &M, &A);
        taa_mat44_subtract(&B, &M, &B);
        taa_mat44_scale(&A, 2.0f, &A);
        taa_mat44_scale(&B, 2.0f, &B);
        taa_mat44_multiply(&A, &B, &M);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glLoadMatrixf(&A.x.x);
        glMultMatrixf(&B.x.x);
        glGetFloatv(GL_MODELVIEW_MATRIX, &N.x.x);
        assert(cmp_mat44(&M, &N, TEST_EPSILON) == 0);
    }
}

static void test_mat44_lookat()
{
    int i;
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        taa_vec4 sub = { 0.5f, 0.5f, 0.5f, 0.0f };
        taa_vec4 eye;
        taa_vec4 tgt;
        taa_vec4 up;
        taa_mat44 M;
        taa_mat44 N;
        rand_vec4(&eye);
        rand_vec4(&tgt);
        rand_vec4(&up);
        taa_vec4_subtract(&eye, &sub, &eye);
        taa_vec4_subtract(&tgt, &sub, &tgt);
        taa_vec4_add(&eye, &tgt, &tgt);
        taa_vec4_subtract(&up, &sub, &up);
        taa_vec4_scale(&eye, 5.0f, &eye);
        taa_vec4_scale(&tgt, 5.0f, &tgt);
        up.y += (up.y >= 0.0f) ? 0.1f : -0.1f;
        up.w = 0.0f;
        taa_vec4_normalize(&up, &up);
        taa_mat44_lookat(&eye, &tgt, &up, &M);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye.x, eye.y, eye.z, tgt.x, tgt.y, tgt.z, up.x, up.y, up.z);
        glGetFloatv(GL_MODELVIEW_MATRIX, &N.x.x);
        assert(cmp_mat44(&M, &N, TEST_EPSILON*100.0f) == 0);
    }
}

static void test_mat44_perspective()
{
    int i;
    for(i = 0; i < NUM_TEST_LOOPS; ++i)
    {
        float fov = (randf()*0.125f + (1/3.0f)) * taa_PI;
        float aspect = randf() * 0.5f + 0.5f;
        float znear = randf() + 0.1f;
        float zfar = randf() * 100.0f + 50.0f;
        taa_mat44 M;
        taa_mat44 N;
        taa_mat44_perspective(fov, aspect, znear, zfar, &M);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(taa_degrees(fov), aspect, znear, zfar);
        glGetFloatv(GL_PROJECTION_MATRIX, &N.x.x);
        assert(cmp_mat44(&M, &N, TEST_EPSILON*100.0f) == 0);
    }
}

typedef struct main_win_s main_win;

struct main_win_s
{
    taa_window_display windisplay;
    taa_window win;
    taa_glcontext_display rcdisplay;
    taa_glcontext_surface rcsurface;
    taa_glcontext rc;
};

//****************************************************************************
static int main_init_window(
    main_win* mwin)
{
    int err = 0;
    int rcattribs[] =
    {
        taa_GLCONTEXT_BLUE_SIZE   ,  8,
        taa_GLCONTEXT_GREEN_SIZE  ,  8,
        taa_GLCONTEXT_RED_SIZE    ,  8,
        taa_GLCONTEXT_DEPTH_SIZE  , 24,
        taa_GLCONTEXT_STENCIL_SIZE,  8,
        taa_GLCONTEXT_NONE
    };
    taa_glcontext_config rcconfig;
    memset(mwin, 0, sizeof(*mwin));
    mwin->windisplay = taa_window_open_display();
    err = (mwin->windisplay != NULL) ? 0 : -1;
    if(err == 0)
    {
        err = taa_window_create(
            mwin->windisplay,
            "gl math test",
            720,
            405,
            taa_WINDOW_FULLSCREEN,
            &mwin->win);
    }
    if(err == 0)
    {
        mwin->rcdisplay = taa_glcontext_get_display(mwin->windisplay);
        err = (mwin->rcdisplay != NULL) ? 0 : -1;
    }
    if(err == 0)
    {
        err = (taa_glcontext_initialize(mwin->rcdisplay)) ? 0 : -1;
    };
    if(err == 0)
    {
        int numconfig = 0;
        taa_glcontext_choose_config(
            mwin->rcdisplay,
            rcattribs,
            &rcconfig,
            1,
            &numconfig);
        err = (numconfig >= 1) ? 0 : -1;
    }
    if(err == 0)
    {
        mwin->rcsurface = taa_glcontext_create_surface(
            mwin->rcdisplay,
            rcconfig,
            mwin->win);
        err = (mwin->rcsurface != 0) ? 0 : -1;
    }
    if(err == 0)
    {
        mwin->rc = taa_glcontext_create(
            mwin->rcdisplay,
            mwin->rcsurface,
            rcconfig,
            NULL,
            NULL);
        err = (mwin->rc != NULL) ? 0 : -1;
    }
    if(err == 0)
    {
        int success = taa_glcontext_make_current(
            mwin->rcdisplay,
            mwin->rcsurface,
            mwin->rc);
        err = (success) ? 0 : -1;
    }
    return err;
}

//****************************************************************************
static void main_close_window(
    main_win* mwin)
{
    taa_window_show(mwin->windisplay, mwin->win, 0);
    if(mwin->rc != NULL)
    {
        taa_glcontext_make_current(mwin->rcdisplay,mwin->rcsurface,NULL);
        taa_glcontext_destroy(mwin->rcdisplay, mwin->rc);
        taa_glcontext_destroy_surface(
            mwin->rcdisplay,
            mwin->win,
            mwin->rcsurface);
    }
    if(mwin->rcdisplay != NULL)
    {
        taa_glcontext_terminate(mwin->rcdisplay);
    }
    taa_window_destroy(mwin->windisplay, mwin->win);
    if(mwin->windisplay != NULL)
    {
        taa_window_close_display(mwin->windisplay);
    }
}

//****************************************************************************
void main_exec(
    main_win* mwin)
{
    printf("testing taa_mat33_multiply...");
    fflush(stdout); 
    test_mat33_multiply();
    printf("pass\n");
    printf("testing taa_mat44_multiply...");
    fflush(stdout);     
    test_mat44_multiply();
    printf("pass\n");
    printf("testing taa_mat44_lookat...");
    fflush(stdout);     
    test_mat44_lookat();
    printf("pass\n");
    printf("testing taa_mat44_perspective...");
    fflush(stdout);     
    test_mat44_perspective();
    printf("pass\n");
}

//****************************************************************************
int main(int argc, char* argv[])
{
    main_win mwin;
    int err;

    err = main_init_window(&mwin);
    if(err == 0)
    {
        main_exec(&mwin);
    }
    main_close_window(&mwin);

#if defined(_DEBUG) && defined(_MSC_FULL_VER)
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtCheckMemory();
    _CrtDumpMemoryLeaks();
#endif
    return err;
}
