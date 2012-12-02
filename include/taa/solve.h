/**
 * @brief     cubic root solver implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SOLVE_H_
#define taa_SOLVE_H_

#include "mathdefs.h"
#include <float.h>

taa_INLINE static int32_t taa_solve_cubic(
    float a, 
    float b,
    float c,
    float d,
    float* x_out)
{
    static const float cos120 = -0.5f;
    static const float sin120 = 0.866025404f;
    int32_t n = 0;
    if(fabs(d) < FLT_EPSILON)
    {
        // first solution is x = 0
        *x_out = 0.0f;
        ++n;
        ++x_out;
        // divide all terms by x, converting to quadratic equation
        d = c;
        c = b;
        b = a;
        a = 0.0f;
    }
    if(fabs(a) < FLT_EPSILON)
    {
        if(fabs(b) < FLT_EPSILON)
        {
            // linear equation
            if(fabs(c) > FLT_EPSILON)
            {
                *x_out = -d/c;
                n += 1;
            }
        }
        else
        {
            // quadratic equation
            float yy = c*c - 4*b*d;
            if(yy >= 0)
            {
                float inv2b = 1/(2*b); 
                float y = (float) sqrt(yy);
                x_out[0] = (-c + y) * inv2b;
                x_out[1] = (-c - y) * inv2b;
                n += 2;
            }
        }
    }
    else
    {
        // cubic equation
        float inva = 1/a;
        float invaa = inva*inva;
        float bb = b*b;
        float bover3a = b*(1/3.0f)*inva;
        float p = (3*a*c - bb)*(1/3.0f)*invaa;
        float halfq = (2*bb*b - 9*a*b*c + 27*a*a*d)*(0.5f/27)*invaa*inva;
        float yy = p*p*p/27 + halfq*halfq;
        if(yy > FLT_EPSILON)
        {
            // sqrt is positive: one real solution
            float y = (float) sqrt(yy);
            float uuu = -halfq + y;
            float vvv = -halfq - y;
            float www = fabs(uuu) > fabs(vvv) ? uuu : vvv;
            float w =(float) ((www<0) ? -pow(fabs(www),1/3.0):pow(www,1/3.0));
            *x_out = w - p/(3*w) - bover3a;
            n = 1;
        }
        else if(yy < -FLT_EPSILON)
        {
            // sqrt is negative: three real solutions
            float x = -halfq;
            float y = (float) sqrt(-yy);
            float theta;
            float r;
            float ux;
            float uyi;
            // convert to polar form
            if(fabs(x) > FLT_EPSILON)
            {
                theta = (float) ((x>0) ? atan(y/x) : (atan(y/x)+taa_PI));
                r = (float) sqrt(x*x - yy);
            }
            else
            {
                // vertical line
                theta = taa_PI/2;
                r = y;
            }
            // calc cube root
            theta /= 3.0f;
            r = (float) pow(r, 1/3.0);
            // convert to complex coordinate
            ux = (float) cos(theta)*r;
            uyi = (float) sin(theta)*r;
            // first solution
            x_out[0] = ux+ux - bover3a;
            // second solution, rotate +120 degrees
            x_out[1] = 2*(ux*cos120 - uyi*sin120) - bover3a;
            // third solution, rotate -120 degrees
            x_out[2] = 2*(ux*cos120 + uyi*sin120) - bover3a;
            n = 3;
        }
        else
        {
            // sqrt is zero: two real solutions
            float www = -halfq;
            float w =(float) ((www<0) ? -pow(fabs(www),1/3.0):pow(www,1/3.0));
            // first solution           
            x_out[0] = w+w - bover3a;
            // second solution, rotate +120 degrees
            x_out[1] = 2*w*cos120 - bover3a;
            n = 2;
        }
    }
    return n;
}

#endif // taa_SOLVE_H_

