#ifndef __RGB2JCH_DATA_H__
#define __RGB2JCH_DATA_H__

#include "HelloWorld.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
using namespace cocos2d;

class RGB2JCH
{
public:
    struct CIECAM02color {
  double x, y, z;
  double J, C, h, H;
  double Q, M, s;
  double ac, bc;
  double as, bs;
  double am, bm;
};

struct CIECAM02vc {
  double xw, yw, zw, aw;
  double la, yb;
  int surround;
  double n, z, f, c, nbb, nc, ncb, fl, d;
};

float getCIECAM02h (int r, int g, int b);

private:
    static double compute_n(struct CIECAM02vc theVC);
    static double compute_z(struct CIECAM02vc theVC);
    static double compute_nbb(struct CIECAM02vc theVC);
    static double compute_fl(struct CIECAM02vc theVC);
    static double calculate_fl_from_la_ciecam02(double la);
    static void xyz_to_cat02( double *r, double *g, double *b, double x, double y, double z );
    static void cat02_to_xyz( double *x, double *y, double *z, double r, double g, double b );
    static void hpe_to_xyz( double *x, double *y, double *z, double r, double g, double b );
    static void cat02_to_hpe( double *rh, double *gh, double *bh, double r, double g, double b );
    static double compute_d(struct CIECAM02vc theVC);
    static double nonlinear_adaptation( double c, double fl );
    static double inverse_nonlinear_adaptation( double c, double fl );
    static double achromatic_response_to_white( struct CIECAM02vc theVC );
    struct CIECAM02color forwardCIECAM02(struct CIECAM02color theColor, struct CIECAM02vc theVC, int theVerbose, FILE *theFile);
                          
};

#endif // __RGB2JCH_DATA_H__
