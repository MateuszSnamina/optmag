// MY HEADER:
#include <symbolic_algebra/modify_flatten_factor.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>

namespace symbolic_algebra {

ModificationResult modify_flatten_factor(ExpressionHandler&& expression) {
    if (!expression.is_of_type<RealFactoredExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    auto& subexpression = expression.subexpression(0);
    if (!subexpression.is_of_type<RealFactoredExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    auto subsubexpression = std::move(subexpression.subexpression(0));
    const auto expression_factor = expression.casted_target<RealFactoredExpression>().unwrap().get().factor();
    const auto subexpression_factor =  subexpression.casted_target<RealFactoredExpression>().unwrap().get().factor();
    auto flatten_factor_expression = RealFactoredExpression::make(expression_factor*subexpression_factor, std::move(subsubexpression));
    return ModificationResult::make_generated_result(std::move(flatten_factor_expression));
}

}  // namespace symbolic_algebra
