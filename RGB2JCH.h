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
    
    void getCIECAM02h (int* r, int* g, int* b, float *T, float *h, float *Hptr, float *cieaptr, float *ciebptr, float *Jptr, float *Cptr, float *Qptr, float *acptr, float *bcptr, float *amptr, float *bmptr, float *asptr, float *bsptr);

private:
    
    int XYZtoCorColorTemp(struct CIECAM02color *theColor);
    double compute_n(struct CIECAM02vc theVC);
    double compute_z(struct CIECAM02vc theVC);
    double compute_nbb(struct CIECAM02vc theVC);
    double compute_fl(struct CIECAM02vc theVC);
    double calculate_fl_from_la_ciecam02(double la);
    void xyz_to_cat02( double *r, double *g, double *b, double x, double y, double z );
    void cat02_to_hpe( double *rh, double *gh, double *bh, double r, double g, double b );
    double compute_d(struct CIECAM02vc theVC);
    double nonlinear_adaptation( double c, double fl );
    
    double achromatic_response_to_white( struct CIECAM02vc theVC );
    struct CIECAM02color forwardCIECAM02(struct CIECAM02color theColor, struct CIECAM02vc theVC);
                          
};

#endif // __RGB2JCH_DATA_H__
