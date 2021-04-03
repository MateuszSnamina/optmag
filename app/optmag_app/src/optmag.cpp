#include <iostream>
#include <armadillo>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "optimization.h"


// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_mixed
// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_equality
// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_inequality

using namespace alglib;
void  nlcfunc2_jac(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr)
{
    //
    // this callback calculates
    //
    //     f0(x0,x1,x2) = x1^2
    //     f1(x0,x1,x2) = x0^2 + x1^2 - 1
    //
    // and Jacobian matrix J = [dfi/dxj]
    //

    // fisrt index is for function, the second for variable.
    double a = 2;
    double b = 1;
    double w = a * x[0] + b * x[1];
    fi[0] = w * w;
    fi[1] = x[0] * x[0] + x[1] * x[1] - 1.0;
    jac[0][0] = 2 * w * a;
    jac[0][1] = 2 * w * b;
    jac[1][0] = 2 * x[0];
    jac[1][1] = 2 * x[1];
}

// Note:     alglib::real_2d_array a, b, c;
// Note:     a.setlength(n, n);
// Note:     a[i][j] = 0.5;

int main(int argc, char **argv)
{
    real_1d_array x0 = "[1,0]"; // variables value 
    real_1d_array s = "[1,1]"; // variables scale
    double epsx = 0.000001;
    ae_int_t maxits = 0;
    minnlcstate state;
    minnlcreport rep;
    real_1d_array x1;

    //
    // Create optimizer object and tune its settings:
    // * epsx=0.000001  stopping condition for inner iterations
    // * s=[1,1]        all variables have unit scale
    // * upper limit on step length is specified (to avoid probing locations where exp() is large)
    //
    minnlccreate(2, x0, state);
    minnlcsetcond(state, epsx, maxits);
    minnlcsetscale(state, s);
    minnlcsetstpmax(state, 10.0);

    double rho = 1000.0;
    ae_int_t outerits = 5;
    minnlcsetalgoaul(state, rho, outerits);

    //minnlcsetalgoslp(state);

    minnlcsetnlc(state, 1, 0);  // first parameter is number of equality constraints,second one is number of inequality constraints.
    minnlcoptguardsmoothness(state);
    minnlcoptguardgradient(state, 0.001);

    alglib::minnlcoptimize(state, nlcfunc2_jac);
    minnlcresults(state, x1, rep);
    printf("%s\n", x1.tostring(2).c_str());

    optguardreport ogrep;
    minnlcoptguardresults(state, ogrep);
    printf("%s\n", ogrep.badgradsuspected ? "true" : "false"); // EXPECTED: false
    printf("%s\n", ogrep.nonc0suspected ? "true" : "false"); // EXPECTED: false
    printf("%s\n", ogrep.nonc1suspected ? "true" : "false"); // EXPECTED: false
    return 0;
}
