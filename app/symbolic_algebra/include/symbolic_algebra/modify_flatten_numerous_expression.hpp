#ifndef SYMBOLIC_ALGEBRA_MODIFY_FLATTEN_NUMEROUS_EXPRESSION_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_FLATTEN_NUMEROUS_EXPRESSION_HPP

// SELF
#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract_common.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
// STD:
#include <type_traits>

namespace symbolic_algebra {

template <class VectorNumerousExpressionDerrivedClass>
ModificationResult modify_flatten_numerous_expression(ExpressionHandler&& expression) {
    static_assert(std::is_base_of_v<VectorNumerousExpression, VectorNumerousExpressionDerrivedClass>);
    // ***************************************************************
    // *** the transformation applies only to expressions being     **
    // *** of VectorNumerousExpressionDerrivedClass type            **
    // ***************************************************************
    if (!expression.is_of_type<VectorNumerousExpressionDerrivedClass>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.range();
    // ***************************************************************
    // *** the transformation applies only to expressions           **
    // *** with at least one subexpressions being                   **
    // *** of VectorNumerousExpressionDerrivedClass type            **
    // ***************************************************************
    const auto is_given_type_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<VectorNumerousExpressionDerrivedClass>();
    };
    const bool is_any_of_subexpressions_of_given_type = boost::algorithm::any_of(range, is_given_type_expression);
    if (!is_any_of_subexpressions_of_given_type) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector v;
    for (auto& subexpression : range) {
        if (subexpression.is_of_type<VectorNumerousExpressionDerrivedClass>()) {
            for (auto& subsubexpression : subexpression.range()) {
                v.emplace_back(std::move(subsubexpression));
            }
        } else {
            v.emplace_back(std::move(subexpression));
        }
    }
    // ***************************************************************
    // *** return the flattened expression                          **
    // ***************************************************************
    auto flattened_expression = VectorNumerousExpressionDerrivedClass::make_from_buffer(std::move(v));
    return ModificationResult::make_generated_result(std::move(flattened_expression));
}

}  // namespace symbolic_algebra

#endif
