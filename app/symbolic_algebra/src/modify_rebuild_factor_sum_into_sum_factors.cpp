// MY HEADER:
#include <symbolic_algebra/modify_rebuild_factor_sum_into_sum_factors.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
// STD:
#include <numeric>

namespace symbolic_algebra {

ModificationResult modify_rebuild_factor_sum_into_sum_factors(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to                       **
    // *** RealFactoredExpression expressions                       **
    // ***************************************************************
    if (!expression.is_of_type<RealFactoredExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    auto& subexpression = expression.subexpression(0);
    const auto factor = expression.casted_target<RealFactoredExpression>().unwrap().get().factor();
    // ***************************************************************
    // *** the transformation applies only when                     **
    // *** the subexpression is SumExpression                       **
    // ***************************************************************
    if (!subexpression.is_of_type<SumExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = subexpression.range();
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    for (auto& subsubexpression : range) {
        auto new_subexpression = RealFactoredExpression::make(factor, std::move(subsubexpression));
        new_subexpressions.push_back(std::move(new_subexpression));
    }
    // ***************************************************************
    // *** return the new_sum_product_expression                    **
    // ***************************************************************
    auto new_sum_product_expression = SumExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(new_sum_product_expression));
}

}  // namespace symbolic_algebra
