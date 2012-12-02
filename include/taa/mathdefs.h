/**
 * @brief     math type definitions header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_MATHDEFS_H_
#define taa_MATHDEFS_H_

#include <taa/system.h>
#include <math.h>

#define taa_PI (3.14159265f)

/**
 * @brief a 3x3 matrix in column major format.
 * @details This structure is NOT aligned on 16 byte boundaries.
 * <p>elements are layed out in memory in the following order:</p>
 * <pre>
 * |  0  3  6  |
 * |  1  4  7  |
 * |  2  5  8  |
 * </pre>
 */
typedef struct taa_mat33_s taa_mat33;

/**
 * @brief 4x4 matrix in column major format.
 * @details This structure MUST BE aligned on 16 byte boundaries.
 * <p>Elements are layed out in memory in the following order:</p>
 * <pre>
 * |  0  4  8 12 |
 * |  1  5  9 13 |
 * |  2  6 10 14 |
 * |  3  7 11 15 |
 * </pre>
 */
typedef struct taa_mat44_s taa_mat44;

/**
 * @brief a 4 dimensional quaternion
 * @details This structure MUST BE aligned on 16 byte boundaries.
 */
typedef struct taa_vec4_s taa_quat;

/**
 * @brief a 2 dimensional vector
 * @details This structure is NOT aligned on 16 byte boundaries.
 */
typedef struct taa_vec2_s taa_vec2;

/**
 * @brief a 3 dimensional vector
 * @details This structure is NOT aligned on 16 byte boundaries.
 */
typedef struct taa_vec3_s taa_vec3;

/**
 * @brief a 4 dimensional vector
 * @details This structure MUST BE aligned on 16 byte boundaries.
 */
typedef struct taa_vec4_s taa_vec4;

struct taa_vec2_s
{
    float x, y;
};

struct taa_vec3_s
{
    float x, y, z;
};

struct taa_DECLSPEC_ALIGN(16) taa_vec4_s
{
    float x, y, z, w;
} taa_ATTRIB_ALIGN(16);

struct taa_mat33_s
{
    taa_vec3 x;
    taa_vec3 y;
    taa_vec3 z;
};

struct taa_DECLSPEC_ALIGN(16) taa_mat44_s
{
    taa_vec4 x;
    taa_vec4 y;
    taa_vec4 z;
    taa_vec4 w;
} taa_ATTRIB_ALIGN(16);

#endif // taa_MATHDEFS_H_
