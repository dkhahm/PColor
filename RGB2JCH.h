#ifndef __RGB2JCH_DATA_H__
#define __RGB2JCH_DATA_H__


#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
using namespace cocos2d;

class RGB2JCH
{
public:

    RGB2JCH();
    
    static void getCIECAM02h (int* r, int* g, int* b, float *T, float *h);

private:
    
    static int XYZtoCorColorTemp(struct CIECAM02color *theColor);
    static double compute_n(struct CIECAM02vc theVC);
    static double compute_z(struct CIECAM02vc theVC);
    static double compute_nbb(struct CIECAM02vc theVC);
    static double compute_fl(struct CIECAM02vc theVC);
    static double calculate_fl_from_la_ciecam02(double la);
    static void xyz_to_cat02( double *r, double *g, double *b, double x, double y, double z );
    static void cat02_to_hpe( double *rh, double *gh, double *bh, double r, double g, double b );
    static double compute_d(struct CIECAM02vc theVC);
    static double nonlinear_adaptation( double c, double fl );
    
    static double achromatic_response_to_white( struct CIECAM02vc theVC );
    static struct CIECAM02color forwardCIECAM02(struct CIECAM02color theColor, struct CIECAM02vc theVC);
                          
};

#endif // __RGB2JCH_DATA_H__
