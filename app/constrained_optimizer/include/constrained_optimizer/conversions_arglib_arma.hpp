#ifndef CONSTRAINED_OPTIMIZER_CONVERSIONS_ARGLIB_ARMA_HPP
#define CONSTRAINED_OPTIMIZER_CONVERSIONS_ARGLIB_ARMA_HPP

//ARMA:
#include<armadillo>
//ARGLIB:
#include<ap.h>

namespace arglib2arma {

arma::vec vec_view(const alglib::real_1d_array& from);
//void vec_view(alglib::real_1d_array& from, arma::vec& to);
arma::vec vec_copy(const alglib::real_1d_array& from);

} // end of namespace arglib2arma

namespace arma2arglib {

//void vec_view(arma::vec& x, alglib::real_1d_array& to);
void vec_view(arma::vec& x, alglib::real_1d_array& to);
alglib::real_1d_array vec_copy(const arma::vec& x);

} // end of namespace arma2arglib

#endif
