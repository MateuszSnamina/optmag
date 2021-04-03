#ifndef SYMBOLIC_ALGEBRA_TEST_EXAMPLE_EXPRESSION_HPP
#define SYMBOLIC_ALGEBRA_TEST_EXAMPLE_EXPRESSION_HPP

#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>

namespace ca = symbolic_algebra;
using namespace ca::literals;
using namespace ca::operators;

inline symbolic_algebra::ExpressionHandler make_expression_1() {
    symbolic_algebra::ExpressionHandler expr01 = symbolic_algebra::ProductExpression::make(0_var, 4_var, (2 * 6.1_const));
    symbolic_algebra::ExpressionHandler expr02 = (6.1_const + 6.1_const);
    symbolic_algebra::ExpressionHandler expr03 = (10.2_const * 11.3_const);
    symbolic_algebra::ExpressionHandler expr04 = ((1_var + 5_var) + (7.2_const + 11.3_const));
    symbolic_algebra::ExpressionHandler expr0 = symbolic_algebra::ProductExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
    return expr0;
}

inline symbolic_algebra::ExpressionHandler make_expression_2() {
    symbolic_algebra::ExpressionHandler expr01 = symbolic_algebra::ProductExpression::make(0_var, 4_var, (2 * 6.1_const));
    symbolic_algebra::ExpressionHandler expr02 = (6.1_const + 6.1_const);
    symbolic_algebra::ExpressionHandler expr03 = (10.2_const * 11.3_const);
    symbolic_algebra::ExpressionHandler expr04 = ((1_var + 5_var) + (7.2_const + 11.3_const));
    symbolic_algebra::ExpressionHandler expr0 = symbolic_algebra::SumExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
    return expr0;
}

#endif
