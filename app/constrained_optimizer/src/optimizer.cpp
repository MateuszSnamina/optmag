// MY HEADER:
#include <constrained_optimizer/optimizer.hpp>
// BOOST:
#include <boost/range/irange.hpp>
// SYMBOLIC_ALGEBRA:
#include <symbolic_algebra/calculate_expression_value.hpp>
// ALGLIB:
#include <optimization.h>

// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_mixed
// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_equality
// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_inequality


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

namespace  {

class SetupVisitor {
public:
    SetupVisitor(alglib::minnlcstate& state) : _state(state){
    }
    void operator()(const constrained_optimizer::SqpParams&) {
        alglib::minnlcsetalgosqp(_state);
    }
    void operator()(const constrained_optimizer::AulParams&) {
        const double rho = 1000.0;
        const alglib::ae_int_t outerits = 5;
        alglib::minnlcsetalgoaul(_state, rho, outerits);
    }
    void operator()(const constrained_optimizer::SlpParams&) {
        alglib::minnlcsetalgoslp(_state);
    }
private:
    alglib::minnlcstate& _state;
};

void nlcfunc_jac(const alglib::real_1d_array &x_arglib, alglib::real_1d_array &fi, alglib::real_2d_array &jac, void *ptr)
{
    std::cout << "nlcfunc_jac -- enter" << std::endl;
    const constrained_optimizer::OptimizationProblemDefinition& problem_definition = *reinterpret_cast<const constrained_optimizer::OptimizationProblemDefinition*>(ptr);
    std::cout << "PROBLEM DEF| " << "_n_variables: " << problem_definition._n_variables << std::endl; //TODO remove
    std::cout << "PROBLEM DEF| " << "_loss_function: " << problem_definition._loss_function.str() << std::endl; //TODO remove
    for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
        std::cout << "PROBLEM DEF| " << "idx, _loss_function_deivatives[idx]: "
                    << idx << ", "
                      << problem_definition._loss_function_deivatives[idx].str()
                      << std::endl;
    }
    std::cout << "PROBLEM DEF| " << "_constraint_function: " << problem_definition._constraint_function.str() << std::endl; //TODO remove
    for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
        std::cout << "PROBLEM DEF| " << "idx, _constraint_function_deivatives[idx]: "
                    << idx << ", "
                      << problem_definition._constraint_function_deivatives[idx].str()
                      << std::endl;
    }
    // Expects:
    assert(problem_definition._loss_function_deivatives.size() == problem_definition._n_variables);
    assert(problem_definition._constraint_function_deivatives.size() == problem_definition._n_variables);
    // Frameworks conversion:
    const arma::vec& x_arma = arglib2arma::vec_view(x_arglib);
    // Printing (for debug):
    std::cout << "X ARGLIB| " << "length, data:" << x_arglib.length() << ", " << x_arglib.getcontent() << std::endl; //TODO remove
    std::cout << "X ARMA  | " << "length, data:" << x_arma.n_rows << ", " << x_arma.memptr() << std::endl; //TODO remove
    std::cout << "X ARGLIB| (";
    for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
        std::cout << x_arglib(idx) << ", ";
    }
    std::cout << ")" << std::endl;//TODO remove
    std::cout << "X ARMA  | (";
    for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
        std::cout << x_arma(idx) << ", ";
    }
    std::cout << ")" << std::endl;//TODO remove
    // Calculate functions:
    ///////fi.setlength(2);
    std::cout << "nlcfunc_jac -- calculate functions" << std::endl;
    fi[0] = symbolic_algebra::calculate_expression_value(problem_definition._loss_function, x_arma);
    fi[1] = symbolic_algebra::calculate_expression_value(problem_definition._constraint_function, x_arma);
    // Calculate derivatives:
    std::cout << "nlcfunc_jac -- calculate derivatives" << std::endl;
    ///////jac.setlength(2, problem_definition._n_variables);
    for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
        jac[0][idx] = symbolic_algebra::calculate_expression_value(problem_definition._loss_function_deivatives[idx], x_arma);
        jac[1][idx] = symbolic_algebra::calculate_expression_value(problem_definition._constraint_function_deivatives[idx], x_arma);
    }
    std::cout << "nlcfunc_jac -- exit" << std::endl;
}

// Note:     alglib::real_2d_array a, b, c;
// Note:     a.setlength(n, n);
// Note:     a[i][j] = 0.5;

} // end of anonymous namespace.

namespace constrained_optimizer {

void optimize(
        const OptimizationProblemDefinition& problem_definition,
        const OptimizationMethodParams& method_params,
        bool optguard) {
    std::cout << "OptA" << std::endl;
    alglib::real_1d_array x0 = "[1,0]"; // variables value
    alglib::real_1d_array s; // variables scale
    double epsx = 0.000001;
    alglib::ae_int_t maxits = 0;
    alglib::minnlcstate state;
    // Setupt:
    //
    // Create optimizer object and tune its settings:
    // * epsx=0.000001  stopping condition for inner iterations
    // * s=[1,1]        all variables have unit scale
    // * upper limit on step length is specified (to avoid probing locations where exp() is large)
    //
    s.setlength(problem_definition._n_variables);
    for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
        s(idx) = 1.0;
    }
    std::cout << "OptB" << std::endl;
    alglib::minnlccreate(problem_definition._n_variables, x0, state);
    alglib::minnlcsetcond(state, epsx, maxits);
    alglib::minnlcsetscale(state, s);
    //alglib::minnlcsetstpmax(state, 10.0);
    std::visit(SetupVisitor{state}, method_params);
    alglib::minnlcsetnlc(state, 1, 0); // first argument is number of equality constraints, second is number of inequality constraints.
    std::cout << "OptC" << std::endl;
    if (optguard) {
        alglib::minnlcoptguardsmoothness(state);
        alglib::minnlcoptguardgradient(state, 0.001);
    }
    std::cout << "OptD" << std::endl;
    // Optimize:
    alglib::minnlcoptimize(state, nlcfunc_jac, nullptr, &const_cast<OptimizationProblemDefinition&>(problem_definition));
    std::cout << "OptE" << std::endl;
    // Get optimization result:
    alglib::real_1d_array x1_arglib;
    alglib::minnlcreport rep;
    alglib::minnlcresults(state, x1_arglib, rep);
    arma::vec x1_arma = arglib2arma::vec_copy(x1_arglib);
    std::cout << "ARGLIB RESULT| " << x1_arglib.tostring(6).c_str() << std::endl; //  x1_arglib.tostring(6) => format is `.6d`
    std::cout << "ARMA   RESULT| " << x1_arma << std::endl;
    // Get optguard result:
    if (optguard) {
        alglib::optguardreport ogrep;
        alglib::minnlcoptguardresults(state, ogrep);
        std::cout << "ogrep.badgradsuspected: " << (ogrep.badgradsuspected ? "true" : "false") << std::endl;
        std::cout << "ogrep.nonc0suspected: " << (ogrep.badgradsuspected ? "true" : "false") << std::endl;
        std::cout << "ogrep.nonc1suspected: " << (ogrep.badgradsuspected ? "true" : "false") << std::endl;
    }
}

}  // namespace constrained_optimizer
