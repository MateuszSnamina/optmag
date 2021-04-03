// MY HEADER:
#include <symbolic_algebra/modify_detect_zero_factor.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>

namespace symbolic_algebra {

ModificationResult modify_detect_zero_factor(ExpressionHandler&& expression) {
    if (!expression.is_of_type<RealFactoredExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));;
    }
    const auto expression_factor = expression.casted_target<RealFactoredExpression>().unwrap().get().factor();
    const auto& subexpression = expression.subexpression(0);
    const auto is_expression_factor_zero = (expression_factor == 0);
    const auto is_subexpression_zero = subexpression.is_of_type<SumExpression>() && subexpression.casted_target<SumExpression>().unwrap().get().is_zero();
    if ((!is_subexpression_zero) && (!is_expression_factor_zero)) {
        return ModificationResult::make_passed_through_result(std::move(expression));;
    }
    return ModificationResult::make_generated_result(SumExpression::make_zero());
}

}  // namespace symbolic_algebra