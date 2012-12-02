/**
 * @brief     target agnostic vpu macro api definition.
 * @author    Thomas Atwood (tatwood.net)
 * @date      2012
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_VPU_H_
#define taa_VPU_H_

#if defined(taa_MATH_FPU)
#include "vpu_fpu.h"

#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#include "vpu_sse3.h"

#elif defined(__GNUC__) && defined(__arm__)
#include "vpu_neon.h"

#elif defined(_MSC_FULL_VER) && (defined(_M_IX86) || defined(_M_X64))
#include "vpu_sse3.h"

#else
#pragma message("No VPU intrinsics for this target. Using scalar fpu macros")
#include "vpu_fpu.h"

#endif

#define taa_vpu_vec4 taa_vpu_target

//****************************************************************************

#define taa_vpu_mat33_transpose(c0_,c1_,c2_, c0_out_,c1_out_,c2_out_) \
    taa_vpu_mat33_transpose_target(c0_,c1_,c2_, c0_out_,c1_out_,c2_out_)

/**
 * @brief multiply matrix with 4 rows and 3 columns by vec4
 */
#define taa_vpu_mat34_mul_vec4(c0_, c1_, c2_, v_, out_) \
    taa_vpu_mat34_mul_vec4_target(c0_, c1_, c2_, v_, out_)

#define taa_vpu_mat44_abs( \
        c0_, c1_, c2_, c3_,  \
        c0_out_, c1_out_, c2_out_, c3_out_) \
    taa_vpu_mat44_abs_target( \
        c0_,c1_,c2_,c3_, \
        c0_out_,c1_out_,c2_out_,c3_out_)

#define taa_vpu_mat44_mul_vec4(c0_, c1_, c2_, c3_, v_, out_) \
    taa_vpu_mat44_mul_vec4_target(c0_, c1_, c2_, c3_, v_, out_)

#define taa_vpu_mat44_transpose( \
        c0_,c1_,c2_,c3_, \
        c0_out_,c1_out_,c2_out_,c3_out_) \
    taa_vpu_mat44_transpose_target( \
        c0_,c1_,c2_,c3_, \
        c0_out_,c1_out_,c2_out_,c3_out_)

//****************************************************************************

/**
 * @brief compute absolute value
 * @details
 *          out.x = fabs(a.x);
 *          out.y = fabs(a.y);
 *          out.z = fabs(a.z);
 *          out.w = fabs(a.w);
 * @params a taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_abs(a_, out_) \
    taa_vpu_abs_target(a_, out_)

#define taa_vpu_add(a_, b_, out_) \
    taa_vpu_add_target(a_, b_, out_)

/**
 * @brief bitwise and
 * @details
 *          out.x = a.x & b.x;
 *          out.y = a.y & b.y;
 *          out.z = a.z & b.z;
 *          out.w = a.w & b.w;
 * @params a taa_vpu_vec4 in
 * @params b taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_and(a_, b_, out_) \
    taa_vpu_and_target(a_, b_, out_)

/**
 * @brief compare absolute greater than
 * @details
 *          out.x = (fabs(a.x) > fabs(b.x)) ? 0xffffffff : 0;
 *          out.y = (fabs(a.y) > fabs(b.y)) ? 0xffffffff : 0;
 *          out.z = (fabs(a.z) > fabs(b.z)) ? 0xffffffff : 0;
 *          out.w = (fabs(a.w) > fabs(b.w)) ? 0xffffffff : 0;
 * @params a taa_vpu_vec4 in
 * @params b taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_cmpagt(a_, b_, out_) \
    taa_vpu_cmpagt_target(a_, b_, out_)

/**
 * @brief compare greater than
 * @details
 *          out.x = (a.x > b.x) ? 0xffffffff : 0;
 *          out.y = (a.y > b.y) ? 0xffffffff : 0;
 *          out.z = (a.z > b.z) ? 0xffffffff : 0;
 *          out.w = (a.w > b.w) ? 0xffffffff : 0;
 * @params a taa_vpu_vec4 in
 * @params b taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_cmpgt(a_, b_, out_) \
    taa_vpu_cmpgt_target(a_, b_, out_)

#define taa_vpu_cross3(a_, b_, out_) \
    taa_vpu_cross3_target(a_, b_, out_)

#define taa_vpu_div(a_, b_, out_) \
    taa_vpu_div_target(a_, b_, out_)

/**
 * @brief computes vector dot product
 * @details
 *         out.x = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w
 *         out.y = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w
 *         out.z = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w
 *         out.w = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w
 * @params a taa_vpu_vec4 in
 * @params b taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_dot(a_, b_, out_) \
    taa_vpu_dot_target(a_, b_, out_)

#define taa_vpu_dot4(a_, b_, out_) \
    taa_vpu_dot_target(a_, b_, out_)

/**
 * @brief loads memory address into vpu register
 * @details
 *          out.x = pa[0];
 *          out.y = pa[1];
 *          out.z = pa[2];
 *          out.w = pa[3];
 * @params pa const float* in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_load(pa_, out_) \
    taa_vpu_load_target(pa_, out_)

#define taa_vpu_max(a_, b_, out_) \
    taa_vpu_max_target(a_, b_, out_)

#define taa_vpu_min(a_, b_, out_) \
    taa_vpu_min_target(a_, b_, out_)

#define taa_vpu_mov(a_, out_) \
    taa_vpu_mov_target(a_, out_)

#define taa_vpu_mul(a_, b_, out_) \
    taa_vpu_mul_target(a_, b_, out_)

/**
 * @brief compute negative value
 * @details
 *          out.x = -a.x;
 *          out.y = -a.y;
 *          out.z = -a.z;
 *          out.w = -a.w;
 * @params a taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_neg(a_, out_) \
    taa_vpu_neg_target(a_, out_) \

/**
 * @details This macros is implemented using v/(sqrt(len(v)) + FLT_MIN). Zero
 *          length vectors will continue to be zero length after the normalize
 *          operation. The rsqrt instruction is not used because it is an
 *          inaccurate estimation, and further inaccuracy would introduced to
 *          compensate for zero length vectors, because FLT_MIN would need to
 *          be added before the rsqrt. If speed is desired over accuracy,
 *          combine a vpu_vec4_dot4 with vpu_vec4_rsqrt and multiply the
 *          result against the original vector.
 */
#define taa_vpu_normalize(a_, out_) \
    taa_vpu_normalize_target(a_, out_)

/**
 * @brief bitwise or
 * @details
 *          out.x = a.x | b.x;
 *          out.y = a.y | b.y;
 *          out.z = a.z | b.z;
 *          out.w = a.w | b.w;
 * @params a taa_vpu_vec4 in
 * @params b taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_or(a_, b_, out_) \
    taa_vpu_or_target(a_, b_, out_)

/**
 * @details reciprocal square root
 */
#define taa_vpu_rsqrt(a_, out_) \
    taa_vpu_rsqrt_target(a_, out_)

#define taa_vpu_set(x_, y_, z_, w_, out_) \
    taa_vpu_set_target(x_, y_, z_, w_, out_)

/**
 * @brief set all 4 values of vec4 to single value
 * @details
 *          out.x = x;
 *          out.y = x;
 *          out.z = x;
 *          out.w = x;
 * @params x float in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_set1(x_, out_) \
    taa_vpu_set1_target(x_, out_)

/**
 * @brief combines four vectors, selecting one component from each
 * @details
 *         out.x = a.w
 *         out.y = b.x
 *         out.z = c.w
 *         out.w = d.x
 * @params a taa_vpu_vec4 in
 * @params b taa_vpu_vec4 in
 * @params c taa_vpu_vec4 in
 * @params d taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_shuf_aw_bx_cw_dx(a_, b_, c_, d_, out_) \
    taa_vpu_shuf_aw_bx_cw_dx_target(a_, b_, c_, d_, out_)

/**
 * @brief combines two vectors
 * @details
 *         out.x = a.x
 *         out.y = a.y
 *         out.z = a.z
 *         out.w = b.x
 * @params a taa_vpu_vec4 in
 * @params b taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_shuf_ax_ay_az_bx(a_, b_, out_) \
    taa_vpu_shuf_ax_ay_az_bx_target(a_, b_, out_)

/**
 * @brief stores vpu register into memory address
 * @details
 *          out[0] = a.x;
 *          out[1] = a.y;
 *          out[2] = a.z;
 *          out[3] = a.w;
 * @params a taa_vpu_vec4 in
 * @params out float* out
 */
#define taa_vpu_store(a_, out_) \
    taa_vpu_store_target(a_, out_)

/**
 * @brief stores x component of the vpu register into memory address
 * @details
 *          out = a.x;
 * @params a taa_vpu_vec4 in
 * @params out float* out
 */
#define taa_vpu_store1(a_, out_) \
    taa_vpu_store1_target(a_, out_)

#define taa_vpu_sub(a_, b_, out_) \
    taa_vpu_sub_target(a_, b_, out_)

/**
 * @brief bitwise xor
 * @details
 *          out.x = a.x ^ b.x;
 *          out.y = a.y ^ b.y;
 *          out.z = a.z ^ b.z;
 *          out.w = a.w ^ b.w;
 * @params a taa_vpu_vec4 in
 * @params b taa_vpu_vec4 in
 * @params out taa_vpu_vec4 out
 */
#define taa_vpu_xor(a_, b_, out_) \
    taa_vpu_xor_target(a_, b_, out_)

#endif // taa_VPU_H_
