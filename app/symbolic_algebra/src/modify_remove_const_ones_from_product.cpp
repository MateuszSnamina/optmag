// MY HEADER:
#include <symbolic_algebra/modify_remove_const_ones_from_product.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
#include <symbolic_algebra/expression_final_constant.hpp>
#include <symbolic_algebra/modify_remove_bridge_numerous_expression.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>

namespace symbolic_algebra {

ModificationResult modify_remove_const_ones_from_product(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to                       **
    // *** ProductExpression expressions                            **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.range();
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // *** with at least one ingredient being of type               **
    // *** ConstantExpression and having value 1.0                  **
    // ***************************************************************
    const auto is_one = [](const ExpressionHandler& expression) {
        return expression.is_of_type<ConstantExpression>() && (expression.casted_target<ConstantExpression>().unwrap().get().is_one());
    };
    const bool are_any_of_subexpression_one = boost::algorithm::any_of(range, is_one);
    if (!are_any_of_subexpression_one) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** build new sum                                            **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    for (auto& subexpression : range) {
        if (!is_one(subexpression)) {
            new_subexpressions.push_back(std::move(subexpression));
        }
    }
    // ***************************************************************
    // *** return the new_sum_product_expression                    **
    // ***************************************************************
    auto new_product_expression = ProductExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(new_product_expression));
}

}  // namespace symbolic_algebra
