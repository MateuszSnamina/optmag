// MY HEADER:
#include <symbolic_algebra/modify_rebuild_prod_factors_into_factor_prod.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
#include <symbolic_algebra/expression_final_constant.hpp>
// BOOST:
#include<boost/range/algorithm/copy.hpp>
#include<boost/range/adaptor/filtered.hpp>
#include<boost/range/adaptor/transformed.hpp>
#include<boost/range/numeric.hpp>
// STD:
#include <numeric>
#include <cassert>

namespace symbolic_algebra {

ModificationResult modify_eval_partial_sum(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to sum expressions       **
    // ***************************************************************
    if (!expression.is_of_type<SumExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** the transformation applies only if                       **
    // *** there is at least one factor being                       **
    // *** of RealFactoredExpression type                           **
    // ***************************************************************
    const auto is_constant_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<ConstantExpression>();
    };
    const auto is_not_constant_expression = [](const ExpressionHandler& expression) {
        return !expression.is_of_type<ConstantExpression>();
    };
    const unsigned n_constant_subexpression = boost::size(expression.crange() | boost::adaptors::filtered(is_constant_expression));
    if (n_constant_subexpression < 2u) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    const auto extract_constant_expression_value = [](const ExpressionHandler& expression_handler) {
        assert(expression_handler.casted_target<ConstantExpression>());
        return expression_handler.casted_target<ConstantExpression>().unwrap().get().value();
    };
    const auto value_of_child_expressions =
            expression.crange() |
            boost::adaptors::filtered(is_constant_expression) |
            boost::adaptors::transformed(extract_constant_expression_value);
    const auto accumulated_value = boost::accumulate(value_of_child_expressions, 0.0, std::plus<double>());
    ExpressionHandlerVector new_subexpressions;
    new_subexpressions.push_back(ConstantExpression::make(accumulated_value));
    const auto r = expression.range() | boost::adaptors::filtered(is_not_constant_expression);
    std::move(std::begin(r), std::end(r), std::back_insert_iterator<ExpressionHandlerVector>(new_subexpressions));
    //boost::move(expression.range() |
    //            boost::adaptors::filtered(is_not_constant_expression),
    //            std::back_insert_iterator<ExpressionHandlerVector>(new_subexpressions));
    // ***************************************************************
    // *** return the factored product                              **
    // ***************************************************************
    auto new_product_expression = SumExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(new_product_expression));
}

}  // namespace symbolic_algebra
