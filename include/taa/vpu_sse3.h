/**
 * @brief     SSE3 intrinsics macros header
 * @details   This header provides the implementation of the target agnostic
 *            VPU macros to support SSE3 instructions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_VPU_SSE3_H_
#define taa_VPU_SSE3_H_

#if defined(__GNUC__)

#include <x86intrin.h>

#elif defined(_MSC_FULL_VER)

#include <intrin.h>
#include <emmintrin.h>
#include <xmmintrin.h>

#endif

#include <float.h>

#define taa_vpu_target __m128

static const taa_DECLSPEC_ALIGN(16) union
{
    uint32_t u32[4];
    float    f32[4];        
} taa_ATTRIB_ALIGN(16) s_taa_sse_absmask =
{
    { 0x80000000, 0x80000000, 0x80000000, 0x80000000 }
};

static const taa_DECLSPEC_ALIGN(16) float taa_ATTRIB_ALIGN(16) s_taa_sse_tiny[4] =
{
    FLT_MIN, FLT_MIN, FLT_MIN, FLT_MIN
};

//****************************************************************************
#define taa_vpu_mat33_transpose_target(c0_,c1_,c2_, c0_out_,c1_out_,c2_out_) \
    do { \
        taa_vpu_vec4 x0y0x1y1_ = _mm_shuffle_ps(c0_, c1_, 0x44/*01000100*/);\
        taa_vpu_vec4 z0w0z1w1_ = _mm_shuffle_ps(c0_, c1_, 0xee/*11101110*/);\
        c0_out_ = _mm_shuffle_ps(x0y0x1y1_, c2_, 0xc8/*11001000*/);\
        c1_out_ = _mm_shuffle_ps(x0y0x1y1_, c2_, 0xdd/*11011101*/);\
        c2_out_ = _mm_shuffle_ps(z0w0z1w1_, c2_, 0xe8/*11101000*/);\
    } while(0)

//****************************************************************************
#define taa_vpu_mat34_mul_vec4_target(c0_, c1_, c2_, v_, out_) \
    do { \
        taa_vpu_vec4 xxxx_ = _mm_shuffle_ps(v_, v_, 0x00/*00000000*/);\
        taa_vpu_vec4 yyyy_ = _mm_shuffle_ps(v_, v_, 0x55/*01010101*/);\
        taa_vpu_vec4 zzzz_ = _mm_shuffle_ps(v_, v_, 0xaa/*10101010*/);\
        taa_vpu_vec4 cx_   = _mm_mul_ps(c0_, xxxx_); \
        taa_vpu_vec4 cy_   = _mm_mul_ps(c1_, yyyy_); \
        taa_vpu_vec4 cz_   = _mm_mul_ps(c2_, zzzz_); \
        cx_                = _mm_add_ps(cx_, cy_); \
        out_               = _mm_add_ps(cx_, cz_); \
    } while(0)

//****************************************************************************
#define taa_vpu_mat44_abs_target( \
        c0_, c1_, c2_, c3_,  \
        c0_out_, c1_out_, c2_out_, c3_out_) \
    do { \
        __m128 mask_= _mm_load_ps(s_taa_sse_absmask.f32); \
        (c0_out_) = _mm_andnot_ps(mask_, c0_); \
        (c1_out_) = _mm_andnot_ps(mask_, c1_); \
        (c2_out_) = _mm_andnot_ps(mask_, c2_); \
        (c3_out_) = _mm_andnot_ps(mask_, c3_); \
    } while(0)

//****************************************************************************
#define taa_vpu_mat44_mul_vec4_target(c0_, c1_, c2_, c3_, v_, out_) \
    do { \
        taa_vpu_vec4 xxxx_ = _mm_shuffle_ps(v_, v_, 0x00/*00000000*/);\
        taa_vpu_vec4 yyyy_ = _mm_shuffle_ps(v_, v_, 0x55/*01010101*/);\
        taa_vpu_vec4 zzzz_ = _mm_shuffle_ps(v_, v_, 0xaa/*10101010*/);\
        taa_vpu_vec4 wwww_ = _mm_shuffle_ps(v_, v_, 0xff/*11111111*/);\
        taa_vpu_vec4 cx_   = _mm_mul_ps(c0_, xxxx_); \
        taa_vpu_vec4 cy_   = _mm_mul_ps(c1_, yyyy_); \
        taa_vpu_vec4 cz_   = _mm_mul_ps(c2_, zzzz_); \
        taa_vpu_vec4 cw_   = _mm_mul_ps(c3_, wwww_); \
        cx_                = _mm_add_ps(cx_, cy_); \
        cz_                = _mm_add_ps(cz_, cw_); \
        out_               = _mm_add_ps(cx_, cz_); \
    } while(0)

//****************************************************************************
#define taa_vpu_mat44_transpose_target( \
        c0_,c1_,c2_,c3_, \
        c0_out_,c1_out_,c2_out_,c3_out_) \
    do { \
        taa_vpu_vec4 x0y0x1y1_ = _mm_shuffle_ps(c0_,c1_,0x44/*01000100*/); \
        taa_vpu_vec4 x2y2x3y3_ = _mm_shuffle_ps(c2_,c3_,0x44/*01000100*/); \
        taa_vpu_vec4 z0w0z1w1_ = _mm_shuffle_ps(c0_,c1_,0xee/*11101110*/); \
        taa_vpu_vec4 z2w2z3w3_ = _mm_shuffle_ps(c2_,c3_,0xee/*11101110*/); \
        c0_out_ = _mm_shuffle_ps(x0y0x1y1_,x2y2x3y3_,0x88/*10001000*/);\
        c1_out_ = _mm_shuffle_ps(x0y0x1y1_,x2y2x3y3_,0xdd/*11011101*/);\
        c2_out_ = _mm_shuffle_ps(z0w0z1w1_,z2w2z3w3_,0x88/*10001000*/);\
        c3_out_ = _mm_shuffle_ps(z0w0z1w1_,z2w2z3w3_,0xdd/*11011101*/);\
    } while(0)

//****************************************************************************
#define taa_vpu_abs_target(a_, out_) \
    do { \
        __m128 vmask_= _mm_load_ps(s_taa_sse_absmask.f32); \
        (out_) = _mm_andnot_ps(vmask_, a_); \
    } while(0)

//****************************************************************************
#define taa_vpu_add_target(a_, b_, out_) \
    ((out_) = _mm_add_ps(a_, b_))

//****************************************************************************
#define taa_vpu_and_target(a_, b_, out_) \
    ((out_) = _mm_and_ps(a_, b_))

//****************************************************************************
#define taa_vpu_cmpagt_target(a_, b_, out_) \
    do { \
        __m128 mask_= _mm_load_ps(s_taa_sse_absmask.f32); \
        (out_) = _mm_cmpgt_ps(_mm_andnot_ps(mask_, a_), \
                              _mm_andnot_ps(mask_, a_)); \
    } while(0)

//****************************************************************************
#define taa_vpu_cmpgt_target(a_, b_, out_) \
    ((out_) = _mm_cmpgt_ps(a_, b_))

//****************************************************************************
#define taa_vpu_cross3_target(a_, b_, out_) \
    do { \
        taa_vpu_vec4 y0z0x0_ = _mm_shuffle_ps(a_,a_,0xc9/*11001001*/);\
        taa_vpu_vec4 z1x1y1_ = _mm_shuffle_ps(b_,b_,0xd2/*11010010*/);\
        taa_vpu_vec4 z0x0y0_ = _mm_shuffle_ps(a_,a_,0xd2/*11010010*/);\
        taa_vpu_vec4 y1z1x1_ = _mm_shuffle_ps(b_,b_,0xc9/*11001001*/);\
        y0z0x0_ = _mm_mul_ps(y0z0x0_, z1x1y1_); \
        z0x0y0_ = _mm_mul_ps(z0x0y0_, y1z1x1_); \
        out_    = _mm_sub_ps(y0z0x0_, z0x0y0_); \
    } while(0)

//****************************************************************************
#define taa_vpu_div_target(a_, b_, out_) \
    ((out_) = _mm_div_ps(a_, b_))

//****************************************************************************
#define taa_vpu_dot_target(a_, b_, out_) \
    do { \
        out_ = _mm_mul_ps (a_, b_); \
        out_ = _mm_hadd_ps(out_, out_); /* x+y,z+w,x+y,z+w */ \
        out_ = _mm_hadd_ps(out_, out_); \
    } while(0)

//****************************************************************************
#define taa_vpu_load_target(pa_, out_) \
    ((out_) = _mm_load_ps(pa_))

//****************************************************************************
#define taa_vpu_max_target(a_, b_, out_) \
    ((out_) = _mm_max_ps(a_, b_))

//****************************************************************************
#define taa_vpu_min_target(a_, b_, out_) \
    ((out_) = _mm_min_ps(a_, b_))

//****************************************************************************
#define taa_vpu_mov_target(a_, out_) \
    ((out_) = (a_))

//****************************************************************************
#define taa_vpu_mul_target(a_, b_, out_) \
    ((out_) = _mm_mul_ps(a_, b_))

//****************************************************************************
#define taa_vpu_neg_target(a_, out_) \
    do { \
        (out_) = _mm_xor_ps(_mm_load_ps(s_taa_sse_absmask.f32), a_); \
    } while(0)

//****************************************************************************
#define taa_vpu_normalize_target(a_, out_) \
    do { \
        taa_vpu_vec4 r_; \
        r_   = _mm_mul_ps (a_, a_); \
        r_   = _mm_hadd_ps(r_, r_); /* x+y,z+w,x+y,z+w */ \
        r_   = _mm_hadd_ps(r_, r_); /* x+y+z+w,x+y+z+w,x+y+z+w,x+y+z+w */ \
        r_   = _mm_sqrt_ps(r_); \
        r_   = _mm_add_ps(r_, _mm_load_ps(s_taa_sse_tiny)); \
        out_ = _mm_div_ps(a_, r_); \
    } while(0)

//****************************************************************************
#define taa_vpu_or_target(a_, b_, out_) \
    ((out_) = _mm_or_ps(a_, b_))

//****************************************************************************
#define taa_vpu_rsqrt_target(a_, out_) \
    ((out_) = _mm_rsqrt_ps(a_))

//****************************************************************************
#define taa_vpu_set_target(x_, y_, z_, w_, out_) \
    ((out_) = _mm_set_ps(w_, z_, y_, x_))

//****************************************************************************
#define taa_vpu_set1_target(x_, out_) \
    ((out_) = _mm_set1_ps(x_))

//****************************************************************************
#define taa_vpu_shuf_ax_ay_az_bx_target(a_, b_, out_) \
    do { \
        /* out = a.z,a.z,b.x,b.x */ \
        out_ = _mm_shuffle_ps(  a_,   b_, 0x0a /*00001010*/); \
        /* out = a.x,a.y,a.z,b.x */ \
        out_ = _mm_shuffle_ps(  a_, out_, 0x84 /*10000100*/); \
    } while(0)

//****************************************************************************
#define taa_vpu_shuf_aw_bx_cw_dx_target(a_, b_, c_, d_, out_) \
    do { \
        /* tmp = a.w,a.w,b.x,b.x */ \
        taa_vpu_vec4 tmp_ = _mm_shuffle_ps(  a_,   b_, 0x0f /*00001111*/); \
        /* out = c.w,c.w,d.x,d.x */ \
        out_              = _mm_shuffle_ps(  c_,   d_, 0x0f /*00001111*/); \
        /* out = a.w,b.x,c.w,d.x */ \
        out_              = _mm_shuffle_ps(tmp_, out_, 0x88 /*10001000*/); \
    } while(0)

//****************************************************************************
#define taa_vpu_store_target(a_, out_) \
    (_mm_store_ps(out_, a_))

//****************************************************************************
#define taa_vpu_store1_target(a_, out_) \
    (_mm_store_ss(out_, a_))

//****************************************************************************
#define taa_vpu_sub_target(a_, b_, out_) \
    ((out_) = _mm_sub_ps(a_, b_))

//****************************************************************************
#define taa_vpu_xor_target(a_, b_, out_) \
    ((out_) = _mm_xor_ps(a_, b_))

#endif // taa_VPU_SSE3_H_
