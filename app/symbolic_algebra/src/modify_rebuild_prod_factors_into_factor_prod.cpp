// MY HEADER:
#include <symbolic_algebra/modify_rebuild_prod_factors_into_factor_prod.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
// STD:
#include <numeric>

namespace symbolic_algebra {

ModificationResult modify_rebuild_prod_factors_into_factor_prod(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.range();
    // ***************************************************************
    // *** the transformation applies only if                       **
    // *** there is at least one factor being                       **
    // *** of RealFactoredExpression type                           **
    // ***************************************************************
    const auto is_integer_factored_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<RealFactoredExpression>();
    };
    const bool are_any_subexpression_factors =
        boost::algorithm::any_of(range, is_integer_factored_expression);
    if (!are_any_subexpression_factors) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    long long accumulated_factor = 1;
    for (auto& subexpression : range) {
        if (subexpression.is_of_type<RealFactoredExpression>()) {
            accumulated_factor *= subexpression.casted_target<RealFactoredExpression>().unwrap().get().factor();
            new_subexpressions.push_back(std::move(subexpression.subexpression(0)));
        } else {
            new_subexpressions.push_back(std::move(subexpression));
        }
    }
    // ***************************************************************
    // *** return the factored product                              **
    // ***************************************************************
    auto new_product_expression = ProductExpression::make_from_buffer(std::move(new_subexpressions));
    auto new_factor_product_expression = RealFactoredExpression::make(accumulated_factor, std::move(new_product_expression));
    return ModificationResult::make_generated_result(std::move(new_factor_product_expression));
}

}  // namespace symbolic_algebra
