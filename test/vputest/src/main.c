#if defined(_DEBUG) && defined(_MSC_FULL_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <taa/fpu.h>
#include "testutil.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#error asserts are not enabled
#endif

//****************************************************************************
void test_mat33_transpose()
{
    taa_mat44 ma;
    taa_mat44 mb;
    taa_mat44 mc;
    taa_mat44* pa = &ma;
    taa_mat44* pb = &mb;
    taa_mat44* pc = &mc;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vc = (taa_vpu_vec4*) pc;
    rand_mat44(pa);
    pb->w = pa->w;
    pc->w = pa->w;
    // fpu macros
    taa_fpu_mat33_transpose(fa[0], fa[1], fa[2], fb[0], fb[1], fb[2]);
    // vpu macros
    taa_vpu_mat33_transpose(va[0], va[1], va[2], vc[0], vc[1], vc[2]);
    assert(!cmp_mat44(pb, pc, TEST_EPSILON));
}

//****************************************************************************
void test_mat44_add()
{
    taa_mat44 ma;
    taa_mat44 mb;
    taa_mat44 mc;
    taa_mat44 md;
    taa_mat44* pa = &ma;
    taa_mat44* pb = &mb;
    taa_mat44* pc = &mc;
    taa_mat44* pd = &md;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_fpu_vec4* fc = (taa_fpu_vec4*) pc;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vb = (taa_vpu_vec4*) pb;
    taa_vpu_vec4* vd = (taa_vpu_vec4*) pd;
    rand_mat44(pa);
    rand_mat44(pb);
    // fpu macros
    taa_fpu_add(fa[0], fb[0], fc[0]);
    taa_fpu_add(fa[1], fb[1], fc[1]);
    taa_fpu_add(fa[2], fb[2], fc[2]);
    taa_fpu_add(fa[3], fb[3], fc[3]);
    // vpu macros
    taa_vpu_add(va[0], vb[0], vd[0]);
    taa_vpu_add(va[1], vb[1], vd[1]);
    taa_vpu_add(va[2], vb[2], vd[2]);
    taa_vpu_add(va[3], vb[3], vd[3]);
    assert(!cmp_mat44(pc, pd, TEST_EPSILON));
    // function api
    taa_mat44_add(pa, pb, pd);
    assert(!cmp_mat44(pc, pd, TEST_EPSILON));
}

//****************************************************************************
void test_mat44_multiply()
{
    taa_mat44 ma;
    taa_mat44 mb;
    taa_mat44 mc;
    taa_mat44 md;
    taa_mat44* pa = &ma;
    taa_mat44* pb = &mb;
    taa_mat44* pc = &mc;
    taa_mat44* pd = &md;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_fpu_vec4* fc = (taa_fpu_vec4*) pc;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vb = (taa_vpu_vec4*) pb;
    taa_vpu_vec4* vd = (taa_vpu_vec4*) pd;
    rand_mat44(pa);
    rand_mat44(pb);
    // fpu macros
    taa_fpu_mat44_mul_vec4(fa[0],fa[1],fa[2],fa[3], fb[0], fc[0]);
    taa_fpu_mat44_mul_vec4(fa[0],fa[1],fa[2],fa[3], fb[1], fc[1]);
    taa_fpu_mat44_mul_vec4(fa[0],fa[1],fa[2],fa[3], fb[2], fc[2]);
    taa_fpu_mat44_mul_vec4(fa[0],fa[1],fa[2],fa[3], fb[3], fc[3]);
    // vpu macros
    taa_vpu_mat44_mul_vec4(va[0],va[1],va[2],va[3], vb[0], vd[0]);
    taa_vpu_mat44_mul_vec4(va[0],va[1],va[2],va[3], vb[1], vd[1]);
    taa_vpu_mat44_mul_vec4(va[0],va[1],va[2],va[3], vb[2], vd[2]);
    taa_vpu_mat44_mul_vec4(va[0],va[1],va[2],va[3], vb[3], vd[3]);
    assert(!cmp_mat44(pc, pd, TEST_EPSILON));
    // function api
    taa_mat44_multiply(pa, pb, pc);
    assert(!cmp_mat44(pc, pd, TEST_EPSILON));
}

//****************************************************************************
void test_mat44_transform_vec4()
{
    taa_mat44 m;
    taa_vec4 a;
    taa_vec4 b;
    taa_vec4 c;
    taa_mat44* pm = &m;
    taa_vec4* pa = &a;
    taa_vec4* pb = &b;
    taa_vec4* pc = &c;
    taa_fpu_vec4* fm = (taa_fpu_vec4*) pm;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_vpu_vec4* vm = (taa_vpu_vec4*) pm;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vc = (taa_vpu_vec4*) pc;
    rand_mat44(pm);
    rand_vec4(pa);
    // fpu macros
    taa_fpu_mat44_mul_vec4(fm[0],fm[1],fm[2],fm[3], *fa, *fb);
    // vpu macros
    taa_vpu_mat44_mul_vec4(vm[0],vm[1],vm[2],vm[3], *va, *vc);
    assert(!cmp_vec4(pb, pc, TEST_EPSILON));
    // function api
    taa_mat44_transform_vec4(pm, pa, pc);
    assert(!cmp_vec4(pb, pc, TEST_EPSILON));
}

//****************************************************************************
void test_mat44_transpose()
{
    taa_mat44 ma;
    taa_mat44 mb;
    taa_mat44 mc;
    taa_mat44* pa = &ma;
    taa_mat44* pb = &mb;
    taa_mat44* pc = &mc;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vc = (taa_vpu_vec4*) pc;
    rand_mat44(pa);
    // fpu macros
    taa_fpu_mat44_transpose(fa[0],fa[1],fa[2],fa[3], fb[0],fb[1],fb[2],fb[3]);
    // vpu macros
    taa_vpu_mat44_transpose(va[0],va[1],va[2],va[3], vc[0],vc[1],vc[2],vc[3]);
    assert(!cmp_mat44(pb, pc, TEST_EPSILON));
    // function api
    taa_mat44_transpose(pa, pc);
    assert(!cmp_mat44(pb, pc, TEST_EPSILON));
}

//****************************************************************************
void test_vec4_abs()
{
    taa_vec4 a;
    taa_vec4 b;
    taa_vec4 c;
    taa_vec4* pa = &a;
    taa_vec4* pb = &b;
    taa_vec4* pc = &c;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vc = (taa_vpu_vec4*) pc;
    rand_vec4(pa);
    taa_vec4_negate(pa, pa);
    // fpu macros
    taa_fpu_abs(*fa, *fb);
    // vpu macros
    taa_vpu_abs(*va, *vc);
    assert(!cmp_vec4(pb, pc, TEST_EPSILON));
}

//****************************************************************************
void test_vec4_cross3()
{
    taa_vec4 a;
    taa_vec4 b;
    taa_vec4 c;
    taa_vec4 d;
    taa_vec4* pa = &a;
    taa_vec4* pb = &b;
    taa_vec4* pc = &c;
    taa_vec4* pd = &d;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_fpu_vec4* fc = (taa_fpu_vec4*) pc;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vb = (taa_vpu_vec4*) pb;
    taa_vpu_vec4* vd = (taa_vpu_vec4*) pd;
    rand_vec4(pa);
    rand_vec4(pb);
    // fpu macros
    taa_fpu_cross3(*fa, *fb, *fc);
    // vpu macros
    taa_vpu_cross3(*va, *vb, *vd);
    assert(!cmp_vec4(pc, pd, TEST_EPSILON));
    // function api
    taa_vec4_cross3(pa, pb, pd);
    assert(!cmp_vec4(pc, pd, TEST_EPSILON));
}

//****************************************************************************
void test_vec4_dot()
{
    taa_vec4 a;
    taa_vec4 b;
    taa_vec4 c;
    taa_vec4 d;
    float f;
    taa_vec4* pa = &a;
    taa_vec4* pb = &b;
    taa_vec4* pc = &c;
    taa_vec4* pd = &d;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_fpu_vec4* fc = (taa_fpu_vec4*) pc;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vb = (taa_vpu_vec4*) pb;
    taa_vpu_vec4* vd = (taa_vpu_vec4*) pd;
    rand_vec4(pa);
    rand_vec4(pb);
    // fpu macros
    taa_fpu_dot(*fa, *fb, *fc);
    // vpu macros
    taa_vpu_dot(*va, *vb, *vd);
    assert(!cmp_vec4(pc, pd, TEST_EPSILON));
    // function api
    f = taa_vec4_dot(pa, pb);
    assert(!cmp_float(pd->x, f, TEST_EPSILON));
    assert(!cmp_float(pd->y, f, TEST_EPSILON));
    assert(!cmp_float(pd->z, f, TEST_EPSILON));
    assert(!cmp_float(pd->w, f, TEST_EPSILON));
}

//****************************************************************************
void test_vec4_multiply()
{
    taa_vec4 a;
    taa_vec4 b;
    taa_vec4 c;
    taa_vec4 d;
    taa_vec4* pa = &a;
    taa_vec4* pb = &b;
    taa_vec4* pc = &c;
    taa_vec4* pd = &d;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_fpu_vec4* fc = (taa_fpu_vec4*) pc;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vb = (taa_vpu_vec4*) pb;
    taa_vpu_vec4* vd = (taa_vpu_vec4*) pd;
    rand_vec4(pa);
    rand_vec4(pb);
    // fpu macros
    taa_fpu_mul(*fa, *fb, *fc);
    // vpu macros
    taa_vpu_mul(*va, *vb, *vd);
    assert(!cmp_vec4(pc, pd, TEST_EPSILON));
    // function api
    taa_vec4_multiply(pa, pb, pd);
    assert(!cmp_vec4(pc, pd, TEST_EPSILON));
}

//****************************************************************************
void test_vec4_normalize()
{
    taa_vec4 a;
    taa_vec4 b;
    taa_vec4 c;
    taa_vec4* pa = &a;
    taa_vec4* pb = &b;
    taa_vec4* pc = &c;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vc = (taa_vpu_vec4*) pc;
    rand_vec4(pa);
    // fpu macros
    taa_fpu_normalize(*fa, *fb);
    // vpu macros
    taa_vpu_normalize(*va, *vc);
    assert(!cmp_vec4(pb, pc, TEST_EPSILON));
    // function api
    taa_vec4_normalize(pa, pc);
    assert(!cmp_vec4(pb, pc, TEST_EPSILON));
}

//****************************************************************************
void test_shuf_ax_ay_az_bx()
{
    taa_vec4 a;
    taa_vec4 b;
    taa_vec4 c;
    taa_vec4 d;
    taa_vec4* pa = &a;
    taa_vec4* pb = &b;
    taa_vec4* pc = &c;
    taa_vec4* pd = &d;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_fpu_vec4* fc = (taa_fpu_vec4*) pc;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vb = (taa_vpu_vec4*) pb;
    taa_vpu_vec4* vd = (taa_vpu_vec4*) pd;
    rand_vec4(pa);
    rand_vec4(pb);
    // fpu macros
    taa_fpu_shuf_ax_ay_az_bx(*fa, *fb, *fc);
    // vpu macros
    taa_vpu_shuf_ax_ay_az_bx(*va, *vb, *vd);
    assert(!cmp_vec4(pc, pd, TEST_EPSILON));
    assert(!cmp_float(pd->x, pa->x, TEST_EPSILON));
    assert(!cmp_float(pd->y, pa->y, TEST_EPSILON));
    assert(!cmp_float(pd->z, pa->z, TEST_EPSILON));
    assert(!cmp_float(pd->w, pb->x, TEST_EPSILON));
}

//****************************************************************************
void test_shuf_aw_bx_cw_dx()
{
    taa_vec4 a;
    taa_vec4 b;
    taa_vec4 c;
    taa_vec4 d;
    taa_vec4 e;
    taa_vec4 f;
    taa_vec4* pa = &a;
    taa_vec4* pb = &b;
    taa_vec4* pc = &c;
    taa_vec4* pd = &d;
    taa_vec4* pe = &e;
    taa_vec4* pf = &f;
    taa_fpu_vec4* fa = (taa_fpu_vec4*) pa;
    taa_fpu_vec4* fb = (taa_fpu_vec4*) pb;
    taa_fpu_vec4* fc = (taa_fpu_vec4*) pc;
    taa_fpu_vec4* fd = (taa_fpu_vec4*) pd;
    taa_fpu_vec4* fe = (taa_fpu_vec4*) pe;
    taa_vpu_vec4* va = (taa_vpu_vec4*) pa;
    taa_vpu_vec4* vb = (taa_vpu_vec4*) pb;
    taa_vpu_vec4* vc = (taa_vpu_vec4*) pc;
    taa_vpu_vec4* vd = (taa_vpu_vec4*) pd;
    taa_vpu_vec4* vf = (taa_vpu_vec4*) pf;
    rand_vec4(pa);
    rand_vec4(pb);
    rand_vec4(pc);
    rand_vec4(pd);
    // fpu macros
    taa_fpu_shuf_aw_bx_cw_dx(*fa, *fb, *fc, *fd, *fe);
    // vpu macros
    taa_vpu_shuf_aw_bx_cw_dx(*va, *vb, *vc, *vd, *vf);
    assert(!cmp_vec4(pe, pf, TEST_EPSILON));
    assert(!cmp_float(pf->x, pa->w, TEST_EPSILON));
    assert(!cmp_float(pf->y, pb->x, TEST_EPSILON));
    assert(!cmp_float(pf->z, pc->w, TEST_EPSILON));
    assert(!cmp_float(pf->w, pd->x, TEST_EPSILON));
}

//****************************************************************************
int main(int argc, char* argv[])
{
    printf("testing taa_mat33_transpose...");
    fflush(stdout);
    test_mat33_transpose();
    printf("pass\n");
    printf("testing taa_mat44_add...");
    fflush(stdout);
    test_mat44_add();
    printf("pass\n");
    printf("testing taa_mat44_multiply...");
    fflush(stdout);    
    test_mat44_multiply();
    printf("pass\n");
    printf("testing taa_mat44_transform_vec4...");
    fflush(stdout);          
    test_mat44_transform_vec4();
    printf("pass\n");
    printf("testing taa_mat44_transpose...");
    fflush(stdout);          
    test_mat44_transpose();
    printf("pass\n");
    printf("testing taa_vec4_abs...");
    fflush(stdout);  
    test_vec4_abs();
    printf("pass\n");
    printf("testing taa_vec4_cross3...");
    fflush(stdout);  
    test_vec4_cross3();
    printf("pass\n");
    printf("testing taa_vec4_dot...");
    fflush(stdout);  
    test_vec4_dot();
    printf("pass\n");
    printf("testing taa_vec4_multiply...");
    fflush(stdout);  
    test_vec4_multiply();
    printf("pass\n");
    printf("testing taa_vec4_normalize...");
    fflush(stdout);  
    test_vec4_normalize();
    printf("pass\n");
    printf("testing taa_shuf_ax_ay_az_bx...");
    fflush(stdout);  
    test_shuf_ax_ay_az_bx();
    printf("pass\n");
    printf("testing taa_shuf_aw_bx_cw_dx...");
    fflush(stdout);  
    test_shuf_aw_bx_cw_dx();
    printf("pass\n");
#if defined(_DEBUG) && defined(_MSC_FULL_VER)
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtCheckMemory();
    _CrtDumpMemoryLeaks();
#endif
    return EXIT_SUCCESS;
}
