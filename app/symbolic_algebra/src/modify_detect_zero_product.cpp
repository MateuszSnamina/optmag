// MY HEADER:
#include <symbolic_algebra/modify_detect_zero_product.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
// BOOST:
#include <boost/range/algorithm/find_if.hpp>

namespace symbolic_algebra {

ModificationResult modify_detect_zero_product(ExpressionHandler&& expression) {
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.crange();
    const auto subproduct_iter = boost::find_if(range, [](const ExpressionHandler& expression) {
        return expression.is_of_type<SumExpression>() && expression.casted_target<SumExpression>().unwrap().get().is_zero();
    });
    if (subproduct_iter == boost::end(range)) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    return ModificationResult::make_generated_result(SumExpression::make_zero());
}

}  // namespace symbolic_algebra