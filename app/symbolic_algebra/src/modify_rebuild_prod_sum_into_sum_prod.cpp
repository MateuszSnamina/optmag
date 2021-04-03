// MY HEADER:
#include <symbolic_algebra/modify_rebuild_prod_sum_into_sum_prod.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
// BOOST:
#include <boost/range/algorithm.hpp>
#include <boost/range/sub_range.hpp>

namespace symbolic_algebra {

ModificationResult modify_rebuild_prod_sum_into_sum_prod(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.range();
    const auto& range_begin = boost::begin(range);
    const auto& range_end = boost::end(range);
    // ***************************************************************
    // *** the transformation does apply to product expressions     **
    // *** with zero factors or only one factor                     **
    // ***************************************************************
    if (expression.n_subexpressions() < 2) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    };
    // ***************************************************************
    // *** the transformation applies only if                       **
    // *** there is at least one factor being                       **
    // *** of SumExpression type                                    **
    // ***************************************************************
    const auto is_sum_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<SumExpression>();
    };
    const auto subproduct_iter = boost::find_if(range, is_sum_expression);
    if (subproduct_iter == range_end) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    using ExpressionHandlerSinglePassSubRange = boost::sub_range<ExpressionHandlerSinglePassRange>;
    const ExpressionHandlerSinglePassSubRange range1(range_begin, subproduct_iter);
    const ExpressionHandlerSinglePassSubRange range2(subproduct_iter + 1, range_end);
    auto& subproduct = *subproduct_iter;
    auto subproduct_range = subproduct.range();
    ExpressionHandlerVector new_subexpressions;
    for (auto& subsubexpression : subproduct_range) {
        ExpressionHandlerVector new_subsubexpressions;
        for (auto& subexpression : range1) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        new_subsubexpressions.push_back(std::move(subsubexpression));
        for (auto& subexpression : range2) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        new_subexpressions.push_back(ProductExpression::make_from_buffer(std::move(new_subsubexpressions)));
    }
    // ***************************************************************
    // *** return the sum_prod_expression                           **
    // ***************************************************************
    auto sum_product_expression = SumExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(sum_product_expression));
}

}  // namespace symbolic_algebra