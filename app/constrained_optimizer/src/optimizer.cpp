// MY HEADER:
#include <constrained_optimizer/optimizer.hpp>
// SELF:
#include <constrained_optimizer/conversions_arglib_arma.hpp>
// SYMBOLIC_ALGEBRA:
#include <symbolic_algebra/calculate_expression_value.hpp>
// ALGLIB:
#include <optimization.h>
// BOOST:
#include <boost/range/irange.hpp>

// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_mixed
// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_equality
// Ref: https://www.alglib.net/translator/man/manual.cpp.html#example_minnlc_d_inequality

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
    //    std::cout << "nlcfunc_jac -- enter" << std::endl;
    // *************** Context *****************************
    const constrained_optimizer::OptimizationProblemDefinition& problem_definition = *reinterpret_cast<const constrained_optimizer::OptimizationProblemDefinition*>(ptr);
    //    {
    //        std::cout << "PROBLEM DEF| " << "_n_variables: " << problem_definition._n_variables << std::endl; //TODO remove
    //        std::cout << "PROBLEM DEF| " << "_loss_function: " << problem_definition._loss_function.str() << std::endl; //TODO remove
    //        for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
    //            std::cout << "PROBLEM DEF| " << "idx, _loss_function_deivatives[idx]: "
    //                        << idx << ", "
    //                          << problem_definition._loss_function_deivatives[idx].str()
    //                          << std::endl;
    //        }
    //        std::cout << "PROBLEM DEF| " << "_constraint_function: " << problem_definition._constraint_function.str() << std::endl; //TODO remove
    //        for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
    //            std::cout << "PROBLEM DEF| " << "idx, _constraint_function_deivatives[idx]: "
    //                        << idx << ", "
    //                          << problem_definition._constraint_function_deivatives[idx].str()
    //                          << std::endl;
    //        }
    //    }
    // *************** Expects *****************************
    assert(problem_definition._loss_function_deivatives.size() == problem_definition._n_variables);
    assert(problem_definition._constraint_function_deivatives.size() == problem_definition._n_variables);
    // *************** Frameworks conversion ***************
    const arma::vec& x_arma = arglib2arma::vec_view(x_arglib);
    //    {
    //        std::cout << "X ARGLIB| " << "length, data:" << x_arglib.length() << ", " << x_arglib.getcontent() << std::endl; //TODO remove
    //        std::cout << "X ARMA  | " << "length, data:" << x_arma.n_rows << ", " << x_arma.memptr() << std::endl; //TODO remove
    //        std::cout << "X ARGLIB| (";
    //        for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
    //            std::cout << x_arglib(idx) << ", ";
    //        }
    //        std::cout << ")" << std::endl;//TODO remove
    //        std::cout << "X ARMA  | (";
    //        for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
    //            std::cout << x_arma(idx) << ", ";
    //        }
    //        std::cout << ")" << std::endl;//TODO remove
    //    }
    // *************** Calculate functions *****************
    //std::cout << "nlcfunc_jac -- calculate functions" << std::endl;
    fi[0] = symbolic_algebra::calculate_expression_value(problem_definition._loss_function, x_arma);
    fi[1] = symbolic_algebra::calculate_expression_value(problem_definition._constraint_function, x_arma);
    // *************** Calculate derivatives ***************
    //std::cout << "nlcfunc_jac -- calculate derivatives" << std::endl;
    for (const unsigned idx : boost::irange(0u, problem_definition._n_variables)) {
        jac[0][idx] = symbolic_algebra::calculate_expression_value(problem_definition._loss_function_deivatives[idx], x_arma);
        jac[1][idx] = symbolic_algebra::calculate_expression_value(problem_definition._constraint_function_deivatives[idx], x_arma);
    }
    //std::cout << "nlcfunc_jac -- exit" << std::endl;
}

} // end of anonymous namespace.

namespace constrained_optimizer {

arma::vec optimize(
        const OptimizationProblemDefinition& problem_definition,
        const arma::vec& x0_arma,
        const OptimizationMethodParams& method_params,
        bool optguard) {
    // *************** Setup *******************************
    const alglib::real_1d_array x0_arglib = arma2arglib::vec_copy(x0_arma); // variables value
    const alglib::real_1d_array s_arglib = arma2arglib::vec_copy(problem_definition._variables_scale); // variables scale
    double epsx = 0.000001;
    alglib::ae_int_t maxits = 0;
    alglib::minnlcstate state;
    alglib::minnlccreate(problem_definition._n_variables, x0_arglib, state);
    alglib::minnlcsetcond(state, epsx, maxits);
    alglib::minnlcsetscale(state, s_arglib);
    //alglib::minnlcsetstpmax(state, 10.0);
    std::visit(SetupVisitor{state}, method_params);
    alglib::minnlcsetnlc(state, 1, 0); // first argument is number of equality constraints, second is number of inequality constraints.
    if (optguard) {
        alglib::minnlcoptguardsmoothness(state);
        alglib::minnlcoptguardgradient(state, 0.001);
    }
    // *************** Optimize ****************************
    alglib::minnlcoptimize(state, nlcfunc_jac, nullptr, &const_cast<OptimizationProblemDefinition&>(problem_definition));
    // *************** Get optimization resultSetup ********
    alglib::real_1d_array x1_arglib;
    alglib::minnlcreport rep;
    alglib::minnlcresults(state, x1_arglib, rep);
    arma::vec x1_arma = arglib2arma::vec_copy(x1_arglib);
    //    std::cout << "ARGLIB RESULT| " << x1_arglib.tostring(6).c_str() << std::endl; //  x1_arglib.tostring(6) => format is `.6d`
    //    std::cout << "ARMA   RESULT| " << x1_arma << std::endl;
    // *************** Get optguard result *****************
    if (optguard) {
        alglib::optguardreport ogrep;
        alglib::minnlcoptguardresults(state, ogrep);
        std::cout << "ogrep.badgradsuspected: " << (ogrep.badgradsuspected ? "true" : "false") << std::endl;
        std::cout << "ogrep.nonc0suspected:   " << (ogrep.badgradsuspected ? "true" : "false") << std::endl;
        std::cout << "ogrep.nonc1suspected:   " << (ogrep.badgradsuspected ? "true" : "false") << std::endl;
    }
    return x1_arma;
}

}  // namespace constrained_optimizer
