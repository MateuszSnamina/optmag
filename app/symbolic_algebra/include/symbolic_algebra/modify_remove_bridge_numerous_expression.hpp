#ifndef SYMBOLIC_ALGEBRA_MODIFY_REMOVE_BRIDGE_NUMEROUS_EXPRESSION_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REMOVE_BRIDGE_NUMEROUS_EXPRESSION_HPP

// SELF:
#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>
#include <symbolic_algebra/expression_abstract_common.hpp>
// STD:
#include <type_traits>

namespace symbolic_algebra {

template <class VectorNumerousExpressionDerrivedClass>
ModificationResult modify_remove_bridge_numerous_expression(ExpressionHandler&& expression) {
    static_assert(std::is_base_of_v<VectorNumerousExpression, VectorNumerousExpressionDerrivedClass>);
    if (!expression.is_of_type<VectorNumerousExpressionDerrivedClass>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto is_bridge = (expression.n_subexpressions() == 1);
    if (!is_bridge) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    auto subexpression = std::move(expression.subexpression(0));
    return ModificationResult::make_generated_result(std::move(subexpression));
}

}  // namespace symbolic_algebra

#endif
