#include<constrained_optimizer/conversions_arglib_arma.hpp>

//https://www.alglib.net/translator/man/manual.cpp.html

namespace arglib2arma {

arma::vec vec_view(const alglib::real_1d_array& from) {
    arma::vec result(const_cast<double*>(from.getcontent()), from.length(), false, true);  // copy_aux_mem = false, strict = true
    return result;
}

//void vec_view(alglib::real_1d_array& from, arma::vec& to) {
//    arma::vec result(from.getcontent(), from.length(), false, true);  // copy_aux_mem = false, strict = true
//    to = result;
//}

arma::vec vec_copy(const alglib::real_1d_array& from) {
    arma::vec result(const_cast<double*>(from.getcontent()), from.length(), true, true);  // copy_aux_mem = true, strict = true
    return result;
}

} // end of namespace arglib2arma

namespace arma2arglib {

//void vec_view(arma::vec& x, alglib::real_1d_array& to) {
//    alglib::real_1d_array result;
//    result.attach_to_ptr(x.n_rows, x.memptr());
//    to = result;
//}

void vec_view(arma::vec& x, alglib::real_1d_array& to) {
    alglib::real_1d_array result;
    result.attach_to_ptr(x.n_rows, x.memptr());
    to = result;
}

alglib::real_1d_array vec_copy(const arma::vec& x) {
    alglib::real_1d_array result;
    result.setcontent(x.n_rows, x.memptr());
    return result;
}

} // end of namespace arglib2arma
