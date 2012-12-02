/**
 * @brief     unit test for cubic solver implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/solve.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    int seed = (int) time(NULL);
    int i;
    unsigned int solmask;

    printf("seed: %x\n", seed);
    solmask = 0;
    for(i = 0; i < 128*128; ++i)
    {
        // randomly generate parameters
        float a = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float b = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float c = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float d = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float px[3];
        float maxx;
        unsigned int typemask;
        int fail;
        int j;
        int n;
        const char* type = "";
        // solve the equation
        n = taa_solve_cubic(a, b, c, d, px);
        typemask = 0;
        if(fabs(a) > FLT_EPSILON && fabs(d) > FLT_EPSILON)
        {
            type = "cubic";
            typemask |= 1 << 3;
        }
        else if(fabs(b) > FLT_EPSILON)
        {
            type = "quadratic";  
            typemask |= 1 << 1;  
        }
        else
        {
            type = "linear";
            typemask |= 1 << 0;
        }
        printf("i=%i a=%f b=%f c=%f d=%f n=%i (%s)\n",i,a,b,c,d,n,type);
        fail = 0;
        maxx = 0.0f;
        for(j = 0; j < n; ++j)
        {
            // check the results
            float x = px[j];
            float zero = a*x*x*x + b*x*x + c*x + d;
            if(maxx < fabs(x))
            {
                maxx = (float) fabs(x);
            }
            if(zero <= 1e-4f)
            {
                printf("\tx%i=%f zero=%f\n",j,x,zero);
            }
            else
            {
                printf("\tx%i=%f zero=%f (fail)\n",j,x,zero);
                fail = 1;
            }
        }
        if(maxx < 10.0f)
        {
            // due the the high amount of floating point imprecision that
            // can occur on solutions with large values, only equations with
            // solutions within the threshold are validated
            for(j = 0; j < n; ++j)
            {
                solmask |= typemask;
                typemask <<= 1;
            }
            assert(!fail);
        }
    }
    // make sure that all solution types were validated
    assert(solmask == 63);
    printf("pass\n");
    return EXIT_SUCCESS;
}
