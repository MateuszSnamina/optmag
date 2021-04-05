#ifndef SYMBOLIC_ALGEBRA_CALCULATE_EXPRESSION_DERIVATIVE_HPP
#define SYMBOLIC_ALGEBRA_CALCULATE_EXPRESSION_DERIVATIVE_HPP

#include<symbolic_algebra/expression_abstract.hpp>

#include<symbolic_algebra/expression_final_constant.hpp>
#include<symbolic_algebra/expression_final_variable.hpp>
#include<symbolic_algebra/expression_final_structural_blocks.hpp>

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/indexed.hpp>

#include <boost/range.hpp>
#include <boost/range/irange.hpp>

#include <cassert>

namespace symbolic_algebra::derivatives_table {

/*
 * derivatives_table is produce expression
 *
 * ∂/∂a_index f(a_1, a_2, ... , a_n) |_{a_1 = formal_argument_1, a_2 = formal_argument_2}
 *
 *
 * For gixen `index`, `formal_argument_*` and `f(.,.,...,.)`.
 *
 * Each supported `f(.,.,...,.)` has its exclusive C++-class,
 * `index`, `formal_argument_*` are passed as the a member function arguments.
 *
 */

/*
 * For f(a_1, a_2, ... , a_n) =  a_1 * a_2 * ... * a_n
 */
struct ProductDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(index < n_formal_arguments);
        ExpressionHandlerVector new_subexpressions;
        for (const auto& formal_argument_with_index : formal_arguments | boost::adaptors::indexed(0) ) {
            if (formal_argument_with_index.index() != index) {
                new_subexpressions.push_back(formal_argument_with_index.value().clone());
            }
        }
        return ProductExpression::make_from_buffer(std::move(new_subexpressions));
    }
};

/*
 * For f(a_1, a_2, ... , a_n) =  a_1 + a_2 + ... + a_n
 */
struct SumDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(index < n_formal_arguments);
        return ConstantExpression::make(1.0);
    }
};

}

namespace symbolic_algebra {

template<class SubExpressionsRange, class DerivativeExpressionMaker>
ExpressionHandler apply_chain_rule_helper(const unsigned index, const SubExpressionsRange& subexpressions, DerivativeExpressionMaker derivative_expression_maker) {
    // const auto n_subexpressions = boost::size(subexpressions);
    // TODO: one-subexpresion optimization.
    ExpressionHandlerVector new_subexpressions;
    for (const auto& outer_function_subexpression_indexed : subexpressions | boost::adaptors::indexed(0)) {
        ExpressionHandler outer_function_derrivative = derivative_expression_maker.make(outer_function_subexpression_indexed.index(), subexpressions);
        ExpressionHandler inner_function_derrivative = calculate_derivative_expression(outer_function_subexpression_indexed.value(), index);
        new_subexpressions.push_back(ProductExpression::make(std::move(outer_function_derrivative), std::move(inner_function_derrivative)));
    }
    return SumExpression::make_from_buffer(std::move(new_subexpressions));
}


inline ExpressionHandler calculate_derivative_expression(const ExpressionHandler& expression_handler, const unsigned index) {
        if (const auto& casted_expression = expression_handler.casted_target<ConstantExpression>()) {
            return ConstantExpression::make(0.0); //or: SumExpression::make_zero();
        } else if (const auto& casted_expression = expression_handler.casted_target<VariableExpression>()) {
            const auto var_index = casted_expression.unwrap().get().index();
            return (var_index == index ? ConstantExpression::make(1.0) : ConstantExpression::make(0.0));
        } else if (const auto& casted_expression = expression_handler.casted_target<RealFactoredExpression>()) {
                const auto factor = casted_expression.unwrap().get().factor();
                auto subexpression_derivative = calculate_derivative_expression(expression_handler.subexpression(0), index);
                return RealFactoredExpression::make(factor, std::move(subexpression_derivative));
        } else if (const auto& casted_expression = expression_handler.casted_target<SumExpression>()) {
            return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::SumDerivativeExpressionMaker{});
        } else if (const auto& casted_expression = expression_handler.casted_target<ProductExpression>()) {
            return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::ProductDerivativeExpressionMaker{});
        }
    throw std::runtime_error("No receipt for expression derivative calculation for expression `" + expression_handler.str() + "`.");
}

}

#endif
