/**
 * @brief     glue macros for mapping scalar fpu macros to the vpu api
 * @details   these macros will likely perform slower than a direct scalar
 *            implementation as they emulate vector operations that always
 *            operate on four floats.
 * @author    Thomas Atwood (tatwood.net)
 * @date      2012
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_VPU_FPU_H_
#define taa_VPU_FPU_H_

#include "fpu.h"

#define taa_vpu_target taa_fpu_vec4

#define taa_vpu_mat33_transpose_target(c0_,c1_,c2_, c0_out_,c1_out_,c2_out_) \
    taa_fpu_mat33_transpose(c0_,c1_,c2_, c0_out_,c1_out_,c2_out_) \

#define taa_vpu_mat34_mul_vec4_target(c0_, c1_, c2_, v_, out_) \
    taa_fpu_mat34_mul_vec4(c0_, c1_, c2_, v_, out_)

#define taa_vpu_mat44_abs_target( \
        c0_, c1_, c2_, c3_,  \
        c0_out_, c1_out_, c2_out_, c3_out_) \
    taa_fpu_mat44_abs( \
        c0_, c1_, c2_, c3_,  \
        c0_out_, c1_out_, c2_out_, c3_out_)

#define taa_vpu_mat44_mul_vec4_target(c0_, c1_, c2_, c3_, v_, out_) \
    taa_fpu_mat44_mul_vec4(c0_, c1_, c2_, c3_, v_, out_)

#define taa_vpu_mat44_transpose_target( \
        c0_,c1_,c2_,c3_, \
        c0_out_,c1_out_,c2_out_,c3_out_) \
    taa_fpu_mat44_transpose( \
        c0_,c1_,c2_,c3_, \
        c0_out_,c1_out_,c2_out_,c3_out_)

#define taa_vpu_abs_target(a_, out_) \
    taa_fpu_abs(a_, out_)

#define taa_vpu_add_target(a_, b_, out_) \
    taa_fpu_add(a_, b_, out_)

#define taa_vpu_and_target(a_, b_, out_) \
    taa_fpu_and(a_, b_, out_)

#define taa_vpu_cmpagt_target(a_, b_, out_) \
    taa_fpu_cmpagt(a_, b_, out_)

#define taa_vpu_cmpgt_target(a_, b_, out_) \
    taa_fpu_cmpgt(a_, b_, out_)

#define taa_vpu_cross3_target(a_, b_, out_) \
    taa_fpu_cross3(a_, b_, out_) \

#define taa_vpu_div_target(a_, b_, out_) \
    taa_fpu_div(a_, b_, out_)

#define taa_vpu_dot_target(a_, b_, out_) \
    taa_fpu_dot(a_, b_, out_)

#define taa_vpu_load_target(pa_, out_) \
    taa_fpu_load(pa_, out_)

#define taa_vpu_max_target(a_, b_, out_) \
    taa_fpu_max(a_, b_, out_)

#define taa_vpu_min_target(a_, b_, out_) \
    taa_fpu_min(a_, b_, out_)

#define taa_vpu_mov_target(a_, out_) \
    taa_fpu_mov(a_, out_)

#define taa_vpu_mul_target(a_, b_, out_) \
    taa_fpu_mul(a_, b_, out_)

#define taa_vpu_neg_target(a_, out_) \
    taa_fpu_neg(a_, out_) \

#define taa_vpu_normalize_target(a_, out_) \
    taa_fpu_normalize(a_, out_)

#define taa_vpu_or_target(a_, b_, out_) \
    taa_fpu_or(a_, b_, out_)

#define taa_vpu_rsqrt_target(a_, out_) \
    taa_fpu_rsqrt(a_, out_)

#define taa_vpu_set_target(x_, y_, z_, w_, out_) \
    taa_fpu_set(x_, y_, z_, w_, out_)

#define taa_vpu_set1_target(x_, out_) \
    taa_fpu_set1(x_, out_)

#define taa_vpu_shuf_ax_ay_az_bx_target(a_, b_, out_) \
    taa_fpu_shuf_ax_ay_az_bx(a_, b_, out_)

#define taa_vpu_shuf_aw_bx_cw_dx_target(a_, b_, c_, d_, out_) \
    taa_fpu_shuf_aw_bx_cw_dx(a_, b_, c_, d_, out_)

#define taa_vpu_store_target(a_, out_) \
    taa_fpu_store(a_, out_)

#define taa_vpu_store1_target(a_, out_) \
    taa_fpu_store1(a_, out_)

#define taa_vpu_sub_target(a_, b_, out_) \
    taa_fpu_sub(a_, b_, out_)

#define taa_vpu_xor_target(a_, b_, out_) \
    taa_fpu_xor(a_, b_, out_)

#endif // taa_VPU_FPU_H_
