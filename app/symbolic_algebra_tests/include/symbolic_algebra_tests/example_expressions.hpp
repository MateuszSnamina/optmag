#ifndef SYMBOLIC_ALGEBRA_TEST_EXAMPLE_EXPRESSION_HPP
#define SYMBOLIC_ALGEBRA_TEST_EXAMPLE_EXPRESSION_HPP

#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>

namespace ca = symbolic_algebra;
using namespace ca::literals;
using namespace ca::operators;

//inline symbolic_algebra::ExpressionHandler make_expression_1() {
//    symbolic_algebra::ExpressionHandler expr01 = symbolic_algebra::ProductExpression::make('a'_cr, 'b'_an, (2 * 'c'_cr));
//    symbolic_algebra::ExpressionHandler expr02 = ('c'_cr + 'c'_cr);
//    symbolic_algebra::ExpressionHandler expr03 = ('d'_an * 'd'_no);
//    symbolic_algebra::ExpressionHandler expr04 = (('a'_an + 'b'_no) + ('c'_an + 'd'_no));
//    symbolic_algebra::ExpressionHandler expr0 = symbolic_algebra::ProductExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
//    return expr0;
//}

//inline symbolic_algebra::ExpressionHandler make_expression_2() {
//    symbolic_algebra::ExpressionHandler expr01 = symbolic_algebra::ProductExpression::make('a'_cr, 'b'_an, (2 * 'c'_cr));
//    symbolic_algebra::ExpressionHandler expr02 = ('c'_cr + 'c'_cr);
//    symbolic_algebra::ExpressionHandler expr03 = ('d'_an * 'd'_no);
//    symbolic_algebra::ExpressionHandler expr04 = (('a'_an + 'b'_no) + ('c'_an + 'd'_no));
//    symbolic_algebra::ExpressionHandler expr0 = symbolic_algebra::SumExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
//    return expr0;
//}

#endif
