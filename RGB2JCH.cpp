//
//  RGB2JCH.cpp
//  CoolWarm
//
//  Created by hahmdong gyun on 2016. 8. 11..
//
//

#include "RGB2JCH.h"

USING_NS_CC;



struct CIECAM02color {
    double x, y, z;
    double J, C, h=0, H;
    double Q, M, s;
    double ac, bc;
    double as, bs;
    double am, bm;
    double T;
};

struct CIECAM02vc {
    double xw=94.811, yw=100.0, zw=107.304, aw;
    double la=100.0, yb=20.0;
    //int surround;
    double n, z, f=1.00, c=0.69, nbb, nc=1.00, ncb, fl, d;
};


RGB2JCH::RGB2JCH(){
    
};



void RGB2JCH::getCIECAM02h (int* r, int* g, int* b, float *T, float *h){
    
    struct CIECAM02vc myVC;
    struct CIECAM02color myColor;
    
    //log("First :  %d, %d, %d", *r, *g, *b);
    
    if ((*r == 0) && (*g == 0) && (*b == 0))
    {
        *b = 1;
    }
    
    float var_R = ((float) *r / 255.0 );        //R from 0 to 255
    float var_G = ((float) *g / 255.0 );        //G from 0 to 255
    float var_B = ((float) *b / 255.0 );        //B from 0 to 255

    if (var_R > 0.04045) var_R = pow(((var_R + 0.055)/1.055), 2.4); //can it be possible? no pow(a, b)?
    else var_R = var_R / 12.92;
    if (var_G > 0.04045) var_G = pow(((var_G + 0.055)/1.055), 2.4);
    else var_G = var_G / 12.92;
    if (var_B > 0.04045) var_B = pow(((var_B + 0.055)/1.055), 2.4);
    else var_B = var_B / 12.92;
    //log("seconde :  %f, %f, %f", var_R, var_G, var_B);
    
    var_R = var_R * 100;
    var_G = var_G * 100;
    var_B = var_B * 100;

    //Observer. = 2°, Illuminant = D65
    float X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
    float Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
    float Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;
    
    //log("!!!!!!!!!!!!%f, %f, %f", X, Y, Z);
    
    myColor.x = X;
    myColor.y = Y;
    myColor.z = Z;
    
    
    //FILE *myViewingConditions, *myInput, *myOutput;
    /*
    if (argc != 7) {
        printf ("\n ciecam02 mode verbose setD in.vc in.dat out.dat\n\n");
        printf ("   mode - 0 for forward and 1 for inverse.\n");
        printf ("   verbose - 0 for off and 1 for on.\n");
        printf ("   setD - 0 for compute and 1 to force to 1.\n");
        printf ("   in.vc - Xw, Yw, Zw, La, Yb and surround.\n");
        printf ("     surrounds are 1 - average, 2 - dim, and 3 - dark.\n\n");
        exit(1);
    }
    else {
        mode    = atoi(argv[1]);
        verbose = atoi(argv[2]);
        setD    = atoi(argv[3]);
    }
    
    if ( ((myViewingConditions  = fopen(argv[4], "r") ) == NULL) ||
        ((myInput              = fopen(argv[5], "r") ) == NULL) ||
        ((myOutput             = fopen(argv[6], "w") ) == NULL) ) {
        printf ("\n\n Cant open one of the data files. Bailing...\n\n");
        exit(1);
    }
    
    
     * Read in and compute the parameters associated with the viewing conditions.
     
    
    fscanf(myViewingConditions, "%lf", &myVC.xw);
    fscanf(myViewingConditions, "%lf", &myVC.yw);
    fscanf(myViewingConditions, "%lf", &myVC.zw);
    fscanf(myViewingConditions, "%lf", &myVC.la);
    fscanf(myViewingConditions, "%lf", &myVC.yb);
    fscanf(myViewingConditions, "%d", &myVC.surround);
    */
    /*
    if (myVC.surround == 1) {
    
         
         
        myVC.f  = 1.00;
        myVC.c  = 0.69;
        myVC.nc = 1.00;
    }
    
    
    else if (myVC.surround == 2) {
     
        myVC.f  = 0.90;
        myVC.c  = 0.59;
        myVC.nc = 0.90;
    }
    else if (myVC.surround == 3) {
        
        myVC.f  = 0.800;
        myVC.c  = 0.525;
        myVC.nc = 0.800;
    }
    else {
        printf ("\n Invalid value for the surround. Exiting.\n\n");
        exit (1);
    }
    */

    myVC.n   = compute_n(myVC);
    myVC.z   = compute_z(myVC);
    myVC.fl  = compute_fl(myVC);
    myVC.nbb = compute_nbb(myVC);
    myVC.ncb = myVC.nbb;
    myVC.d   = compute_d(myVC);
    myVC.aw  = achromatic_response_to_white(myVC);
    
    /*
    if (verbose == 1) {
        fprintf (myOutput, "xw=%lf yw=%lf zw=%lf\n", myVC.xw, myVC.yw, myVC.zw);
        fprintf (myOutput, "la=%lf\n", myVC.la);
        fprintf (myOutput, "yb=%lf\n", myVC.yb);
        fprintf (myOutput, "n=%lf\n", myVC.n);
        fprintf (myOutput, "z=%lf\n", myVC.z);
        fprintf (myOutput, "fl=%lf\n", myVC.fl);
        fprintf (myOutput, "nbb=%lf\n", myVC.nbb);
        fprintf (myOutput, "ncb=%lf\n", myVC.ncb);
        fprintf (myOutput, "surround=%d  f=%lf  c=%lf  nc=%lf\n", myVC.surround, myVC.f, myVC.c, myVC.nc);
        fprintf (myOutput, "d=%lf\n", myVC.d);
        fprintf (myOutput, "aw=%lf\n", myVC.aw);
    }
    */
    myColor = forwardCIECAM02(myColor, myVC);
    

    *T = myColor.T;
    *h = myColor.h;
    
}





double RGB2JCH::compute_n(struct CIECAM02vc theVC) {
    return(theVC.yb / theVC.yw);
}

double RGB2JCH::compute_z(struct CIECAM02vc theVC) {
    return(1.48 + pow(theVC.n, 0.5));
}

double RGB2JCH::compute_nbb(struct CIECAM02vc theVC) {
    return(0.725 * pow((1.0 / theVC.n), 0.2));
}

double RGB2JCH::compute_fl(struct CIECAM02vc theVC) {
    double k, fl;
    k = 1.0 / ((5.0 * theVC.la) + 1.0);
    fl = 0.2 * pow(k, 4.0) * (5.0 * theVC.la) + 0.1 *
    (pow((1.0 - pow(k, 4.0)), 2.0)) *
    (pow((5.0 * theVC.la), (1.0 / 3.0)));
    return(fl);
}

double RGB2JCH::calculate_fl_from_la_ciecam02( double la )
{
    double la5 = la * 5.0;
    double k = 1.0 / (la5 + 1.0);
    
    /* Calculate k^4. */
    k = k * k;
    k = k * k;
    
    return (0.2 * k * la5) + (0.1 * (1.0 - k)
                              * (1.0 - k)
                              * pow(la5, 1.0 / 3.0));
}

/**
 *              [  0.7328  0.4296  -0.1624 ]
 *    M_CAT02 = [ -0.7036  1.6975   0.0061 ]
 *              [  0.0030  0.0136   0.9834 ]
 *
 *              [  1.096124 -0.278869 0.182745 ]
 * M^-1_CAT02 = [  0.454369  0.473533 0.072098 ]
 *              [ -0.009628 -0.005698 1.015326 ]
 */
void RGB2JCH::xyz_to_cat02( double *r, double *g, double *b,
                         double x, double y, double z )
{
    *r = ( 0.7328 * x) + (0.4296 * y) - (0.1624 * z);
    *g = (-0.7036 * x) + (1.6975 * y) + (0.0061 * z);
    *b = ( 0.0030 * x) + (0.0136 * y) + (0.9834 * z);
}



void RGB2JCH::cat02_to_hpe( double *rh, double *gh, double *bh,
                         double r, double g, double b )
{
    *rh = ( 0.7409792 * r) + (0.2180250 * g) + (0.0410058 * b);
    *gh = ( 0.2853532 * r) + (0.6242014 * g) + (0.0904454 * b);
    *bh = (-0.0096280 * r) - (0.0056980 * g) + (1.0153260 * b);
}

/**
 * Theoretically, D ranges from
 *     0 = no adaptation to the adopted white point,
 *  to 1 = complete adaptation to the adopted white point.
 * In practice, the minimum D value will not be less than 0.65 for a
 * dark surround and exponentially converges to 1 for average surrounds
 * with increasingly large values of L_A.
 *
 * L_A is the luminance of the adapting field in cd/m^2.
 */
double RGB2JCH::compute_d(struct CIECAM02vc theVC)
{
    return (theVC.f * (1.0 - ((1.0 / 3.6) * exp((-theVC.la - 42.0) / 92.0))));
}

double RGB2JCH::nonlinear_adaptation( double c, double fl )
{
    double p = pow( (fl * c) / 100.0, 0.42 );
    return ((400.0 * p) / (27.13 + p)) + 0.1;
}



double RGB2JCH::achromatic_response_to_white( struct CIECAM02vc theVC ) {
    double r, g, b;
    double rc, gc, bc;
    double rp, gp, bp;
    double rpa, gpa, bpa;
    
    xyz_to_cat02( &r, &g, &b, theVC.xw, theVC.yw, theVC.zw );
    
    rc = r * (((theVC.yw * theVC.d) / r) + (1.0 - theVC.d));
    gc = g * (((theVC.yw * theVC.d) / g) + (1.0 - theVC.d));
    bc = b * (((theVC.yw * theVC.d) / b) + (1.0 - theVC.d));
    
    cat02_to_hpe( &rp, &gp, &bp, rc, gc, bc );
    
    rpa = nonlinear_adaptation( rp, theVC.fl );
    gpa = nonlinear_adaptation( gp, theVC.fl );
    bpa = nonlinear_adaptation( bp, theVC.fl );
    
    return ((2.0 * rpa) + gpa + ((1.0 / 20.0) * bpa) - 0.305) * theVC.nbb;
}

struct CIECAM02color RGB2JCH::forwardCIECAM02(struct CIECAM02color theColor, struct CIECAM02vc theVC) {
    double r, g, b;
    double rw, gw, bw;
    double rc, gc, bc;
    double rp, gp, bp;
    double rpa, gpa, bpa;
    double a, ca, cb;
    double et, t, temp;
    
    xyz_to_cat02( &r , &g , &b , theColor.x, theColor.y, theColor.z );
    xyz_to_cat02( &rw, &gw, &bw, theVC.xw, theVC.yw, theVC.zw );
    //log("r:%f, g:%f, b:%f", r, g, b);
    //log("rw:%f, gw:%f, bw:%f", rw, gw, bw);
    
    
    rc = r * (((theVC.yw * theVC.d) / rw) + (1.0 - theVC.d));
    gc = g * (((theVC.yw * theVC.d) / gw) + (1.0 - theVC.d));
    bc = b * (((theVC.yw * theVC.d) / bw) + (1.0 - theVC.d));
    //log("rc:%f, gc:%f, bc:%f", rc, gc, bc);
    cat02_to_hpe( &rp, &gp, &bp, rc, gc, bc);
    
    //log("rp:%f, gp:%f, bp:%f", rp, gp, bp);
    
    rpa = nonlinear_adaptation( rp, theVC.fl );
    gpa = nonlinear_adaptation( gp, theVC.fl );
    bpa = nonlinear_adaptation( bp, theVC.fl );
    
    ca = rpa - ((12.0 * gpa) / 11.0) + (bpa / 11.0);
    cb = (1.0 / 9.0) * (rpa + gpa - (2.0 * bpa));
    //log("ca:%f, cb:%f,rpa:%f, gpa:%f, bpa:%f", ca, cb, rpa, gpa, bpa);
    
    theColor.h = (180.0 / M_PI) * atan2(cb, ca);
    if( theColor.h < 0.0 ) theColor.h += 360.0;
        
        if (theColor.h < 20.14) {
            temp = ((theColor.h + 122.47)/1.2) + ((20.14 - theColor.h)/0.8);
            theColor.H = 300 + (100*((theColor.h + 122.47)/1.2)) / temp;
        }
        else if (theColor.h < 90.0) {
            temp = ((theColor.h - 20.14)/0.8) + ((90.00 - theColor.h)/0.7);
            theColor.H = (100*((theColor.h - 20.14)/0.8)) / temp;
        }
        else if (theColor.h < 164.25) {
            temp = ((theColor.h - 90.00)/0.7) + ((164.25 - theColor.h)/1.0);
            theColor.H = 100 + ((100*((theColor.h - 90.00)/0.7)) / temp);
        }
        else if (theColor.h < 237.53) {
            temp = ((theColor.h - 164.25)/1.0) + ((237.53 - theColor.h)/1.2);
            theColor.H = 200 + ((100*((theColor.h - 164.25)/1.0)) / temp);
        }
        else {
            temp = ((theColor.h - 237.53)/1.2) + ((360 - theColor.h + 20.14)/0.8);
            theColor.H = 300 + ((100*((theColor.h - 237.53)/1.2)) / temp);
        }
    
    a = ((2.0 * rpa) + gpa + ((1.0 / 20.0) * bpa) - 0.305) * theVC.nbb;
    
    theColor.J = 100.0 * pow( a / theVC.aw, theVC.c * theVC.z );
    
    et = (1.0 / 4.0) * (cos(((theColor.h * M_PI) / 180.0) + 2.0) + 3.8);
    t = ((50000.0 / 13.0) * theVC.nc * theVC.ncb * et * sqrt((ca*ca) + (cb*cb))) /
    (rpa + gpa + (21.0/20.0)*bpa);
    
    theColor.C = pow( t, 0.9 ) * sqrt( theColor.J / 100.0 )
    * pow( 1.64 - pow( 0.29, theVC.n ), 0.73 );
    
    theColor.Q = ( 4.0 / theVC.c ) * sqrt( theColor.J / 100.0 ) *
    ( theVC.aw + 4.0 ) * pow( theVC.fl, 0.25 );
    
    theColor.M = theColor.C * pow( theVC.fl, 0.25 );
    
    theColor.s = 100.0 * sqrt( theColor.M / theColor.Q );
    
    theColor.ac = theColor.C * cos((theColor.h * M_PI) / 180.0);
    theColor.bc = theColor.C * sin((theColor.h * M_PI) / 180.0);
    
    theColor.am = theColor.M * cos((theColor.h * M_PI) / 180.0);
    theColor.bm = theColor.M * sin((theColor.h * M_PI) / 180.0);
    
    theColor.as = theColor.s * cos((theColor.h * M_PI) / 180.0);
    theColor.bs = theColor.s * sin((theColor.h * M_PI) / 180.0);
    
    /////Temp CAlaute
    struct CIECAM02color *TChanger = &theColor;
    
    int resulthChanger = XYZtoCorColorTemp(TChanger);
    if (resulthChanger == 0)
    {
        log("T calculation success");
    }
    else
    {
        log("bad XYZ input, color temp would be less than minimum of 1666.7 degrees, or too far towards blue");
        theColor.T = 0;
    }
    
    
    /*
    if (theVerbose == 1) {
        fprintf (theFile, "r=%lf g=%lf b=%lf\n", r, g, b);
        fprintf (theFile, "rw=%lf gw=%lf bw=%lf\n", rw, gw, bw);
        fprintf (theFile, "rc=%lf gc=%lf bc=%lf\n", rc, gc, bc);
        fprintf (theFile, "rp=%lf gp=%lf bp=%lf\n", rp, gp, bp);
        fprintf (theFile, "rpa=%lf gpa=%lf bpa=%lf\n", rpa, gpa, bpa);
        fprintf (theFile, "a=%lf b=%lf\n", ca, cb);
        fprintf (theFile, "a=%lf\n", a);
        fprintf (theFile, "h=%lf\n", theColor.h);
        fprintf (theFile, "J=%lf\n", theColor.J);
        fprintf (theFile, "et=%lf\n", et);
        fprintf (theFile, "t=%lf\n", t);
        fprintf (theFile, "C=%lf\n", theColor.C);
        fprintf (theFile, "Q=%lf\n", theColor.Q);
        fprintf (theFile, "M=%lf\n", theColor.M);
        fprintf (theFile, "s=%lf\n", theColor.s);
        fprintf (theFile, "ac=%lf bc=%lf\n", theColor.ac, theColor.bc);
        fprintf (theFile, "am=%lf bm=%lf\n", theColor.am, theColor.bm);
        fprintf (theFile, "as=%lf bs=%lf\n", theColor.as, theColor.bs);
        fprintf (theFile, "H=%lf\n\n", theColor.H);
    }
    */
    
    return(theColor);
}






///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


/* LERP(a,b,c) = linear interpolation macro, is 'a' when c == 0.0 and 'b' when c == 1.0 */
#define LERP(a,b,c)     (((b) - (a)) * (c) + (a))

typedef struct UVT {
    double  u;
    double  v;
    double  t;
} UVT;

double rt[31] = {       /* reciprocal temperature (K) */
    DBL_MIN,  10.0e-6,  20.0e-6,  30.0e-6,  40.0e-6,  50.0e-6,
    60.0e-6,  70.0e-6,  80.0e-6,  90.0e-6, 100.0e-6, 125.0e-6,
    150.0e-6, 175.0e-6, 200.0e-6, 225.0e-6, 250.0e-6, 275.0e-6,
    300.0e-6, 325.0e-6, 350.0e-6, 375.0e-6, 400.0e-6, 425.0e-6,
    450.0e-6, 475.0e-6, 500.0e-6, 525.0e-6, 550.0e-6, 575.0e-6,
    600.0e-6
};

UVT uvt[31] = {
    {0.18006, 0.26352, -0.24341},
    {0.18066, 0.26589, -0.25479},
    {0.18133, 0.26846, -0.26876},
    {0.18208, 0.27119, -0.28539},
    {0.18293, 0.27407, -0.30470},
    {0.18388, 0.27709, -0.32675},
    {0.18494, 0.28021, -0.35156},
    {0.18611, 0.28342, -0.37915},
    {0.18740, 0.28668, -0.40955},
    {0.18880, 0.28997, -0.44278},
    {0.19032, 0.29326, -0.47888},
    {0.19462, 0.30141, -0.58204},
    {0.19962, 0.30921, -0.70471},
    {0.20525, 0.31647, -0.84901},
    {0.21142, 0.32312, -1.0182},
    {0.21807, 0.32909, -1.2168},
    {0.22511, 0.33439, -1.4512},
    {0.23247, 0.33904, -1.7298},
    {0.24010, 0.34308, -2.0637},
    {0.24792, 0.34655, -2.4681},	/* Note: 0.24792 is a corrected value for the error found in W&S as 0.24702 */
    {0.25591, 0.34951, -2.9641},
    {0.26400, 0.35200, -3.5814},
    {0.27218, 0.35407, -4.3633},
    {0.28039, 0.35577, -5.3762},
    {0.28863, 0.35714, -6.7262},
    {0.29685, 0.35823, -8.5955},
    {0.30505, 0.35907, -11.324},
    {0.31320, 0.35968, -15.628},
    {0.32129, 0.36011, -23.325},
    {0.32931, 0.36038, -40.770},
    {0.33724, 0.36051, -116.45}
};


int RGB2JCH::XYZtoCorColorTemp(struct CIECAM02color *theColor)
{
    double us, vs, p, di, dm;
    int i;
    
    if ((theColor->x < 1.0e-20) && (theColor->y < 1.0e-20) && (theColor->z < 1.0e-20))
        return(-1);
     /* protect against possible divide-by-zero failure */
    
    
    us = (4.0 * theColor->x) / (theColor->x + 15.0 * theColor->y + 3.0 * theColor->z);
    vs = (6.0 * theColor->y) / (theColor->x + 15.0 * theColor->y + 3.0 * theColor->z);
    dm = 0.0;
    for (i = 0; i < 31; i++) {
        di = (vs - uvt[i].v) - uvt[i].t * (us - uvt[i].u);
        if ((i > 0) && (((di < 0.0) && (dm >= 0.0)) || ((di >= 0.0) && (dm < 0.0))))
            break;  /* found lines bounding (us, vs) : i-1 and i */
        dm = di;
    }
    if (i == 31)
        return(-1);     /* bad XYZ input, color temp would be less than minimum of 1666.7 degrees, or too far towards blue */
    di = di / sqrt(1.0 + uvt[i    ].t * uvt[i    ].t);
    dm = dm / sqrt(1.0 + uvt[i - 1].t * uvt[i - 1].t);
    p = dm / (dm - di);     /* p = interpolation parameter, 0.0 : i-1, 1.0 : i */
    p = 1.0 / (LERP(rt[i - 1], rt[i], p));
    theColor->T = p;
    return(0);      /* success */
}
