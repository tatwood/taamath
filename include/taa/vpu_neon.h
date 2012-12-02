/**
 * @brief     GCC ARM neon macros header
 * @details   This header provides the implementation of the target agnostic
 *            VPU macros to support ARM Neon intrinsics with the GCC compiler.
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_NEON_GCC_H_
#define taa_NEON_GCC_H_

#include <arm_neon.h>

#define taa_vpu_target float32x4_t

//****************************************************************************
#define taa_vpu_mat44_mul_vec4_target(c0_, c1_, c2_, c3_, v_, out_) \
    ((out_) = vmulq_n_f32(      c0_, vgetq_lane_f32(v_, 0)); \
    ((out_) = vmlaq_n_f32(out_, c1_, vgetq_lane_f32(v_, 1)); \
    ((out_) = vmlaq_n_f32(out_, c2_, vgetq_lane_f32(v_, 2)); \
    ((out_) = vmlaq_n_f32(out_, c3_, vgetq_lane_f32(v_, 3))

//****************************************************************************
#define taa_vpu_abs_target(a_, out_) \
    ((out_) = vabsq_f32(a_))

//****************************************************************************
#define taa_vpu_add_target(a_, b_, out_) \
    ((out_) = vaddq_f32(a_, b_))

//****************************************************************************
#define taa_vpu_and_target(a_, b_, out_) \
    ((out_) = (float32x4_t) vandq_u32 ((uint32x4_t) (a_), (uint32x4_t) (b_)))

//****************************************************************************
#define taa_vpu_cmpagt_target(a_, b_, out_) \
    ((out_) = (float32x4_t) vcagtq_f32 (a_, b_)

//****************************************************************************
#define taa_vpu_cmpgt_target(a_, b_, out_) \
    ((out_) = (float32x4_t) vcgtq_f32(a_, b_))

//****************************************************************************
#define taa_vpu_div_target(a_, b_, out_) \
    ((out_) = vdivq_f32(a_, b_))

//****************************************************************************
#define taa_vpu_load_target(pa_, out_) \
    ((out_) = vld1q_f32(pa_))

//****************************************************************************
#define taa_vpu_max_target(a_, b_, out_) \
    ((out_) = vmaxq_u32 (a_, b_))

//****************************************************************************
#define taa_vpu_min_target(a_, b_, out_) \
    ((out_) = vminq_u32 (a_, b_))

//****************************************************************************
#define taa_vpu_mul_target(a_, b_, out_) \
    ((out_) = vmulq_f32(a_, b_))

//****************************************************************************
#define taa_vpu_or_target(a_, b_, out_) \
    ((out_) = (float32x4_t) vorq_u32 ((uint32x4_t) (a_), (uint32x4_t) (b_)))

//****************************************************************************
#define taa_vpu_neg_target(a_, out_) \
    ((out_) = vnegq_f32(a_))

//****************************************************************************
#define taa_vpu_neg_target(a_, out_) \
    ((out_) = vrsqrteq_f32(a_))

//****************************************************************************
#define taa_vpu_set_target(x_, y_, z_, w_, out_) \
    ((out_) = __extension__ (taa_vpu_vec4){ x_, y_, z_, w_ })

//****************************************************************************
#define taa_vpu_shuf_aw_bx_cw_dx_target(a_, b_, c_, d_, out_) \
    do { \
        /* tmp = a.y,a.z,a.w,b.x */ \
        /* |bw|bz|by|bx|aw|az|ay|ax| => |bx|aw|az|ay| */ \
        taa_vpu_vec4 tmp_ = vextq_f32(  a_,   b_, 1); \
        /* out = c.w,d.x,d.y,d.z */ \
        /* |dw|dz|dy|dx|cw|cz|cy|cx| => |dz|dy|dx|cw| */ \
        out_              = vextq_f32(  c_,   d_, 3);\
        /* out = a.w,b.x,c.w,d.x */ \
        /* |dz|dy|dx|cw|bx|aw|az|ay| => |dx|cw|bx|aw| */ \
        out_              = vextq_f32(tmp_, out_, 2);\
    } while(0)

//****************************************************************************
#define taa_vpu_shuf_ax_ay_az_bx_target(a_, b_, out_) \
    do { \
        /* out = a.w,a.x,a.y,a.z */ \
        /* |aw|az|ay|ax|aw|az|ay|ax| => |az|ay|ax|aw| */ \
        out_ = vextq_f32(  a_,   a_, 3); \
        /* out = a.x,a.y,a.z,b.x */ \
        /* |bw|bz|by|bx|az|ay|ax|aw| => |bx|az|ay|ax| */ \
        out_ = vextq_f32(out_,   b_, 1);\
    } while(0)

//****************************************************************************
#define taa_vpu_sub_target(a_, b_, out_) \
    ((out_) = vsubq_f32(a_, b_))

//****************************************************************************
#define taa_vpu_xor_target(a_, b_, out_) \
    ((out_) = (float32x4_t) vxorq_u32 ((uint32x4_t) (a_), (uint32x4_t) (b_)))

#endif // taa_NEON_GCC_H_
