// MY HEADER:
#include <symbolic_algebra/modify_detect_one_factor.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>

namespace symbolic_algebra {

ModificationResult modify_detect_one_factor(ExpressionHandler&& expression) {
    if (!expression.is_of_type<RealFactoredExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto expression_factor = expression.casted_target<RealFactoredExpression>().unwrap().get().factor();
    auto& subexpression = expression.subexpression(0);
    const auto is_expression_factor_one = (expression_factor == 1);
    if (!is_expression_factor_one) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    return ModificationResult::make_generated_result(std::move(subexpression));
}

}  // namespace symbolic_algebra