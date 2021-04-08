// TESTED LIBRARY:
#include<constrained_optimizer/optimizer.hpp>
// SYMBOLIC ALGEBRA:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/calculate_expression_value.hpp>
#include <symbolic_algebra/calculate_expression_derivative.hpp>
#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/modify_canonical_math.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;
using namespace sa::math;

TEST(ConstrainedOptimizer, Example1) {
    // ********************************************************
    // ********** handle d/dx_0[loss_function] ****************
    const auto loss_function = sa::ProductExpression::make(4.0_const, 0_var, sin(sq(1_var) + 5.0_const));
    ASSERT_EQ(loss_function.str(), "❪4◦x_0◦sin⦗❴sq⦗x_1⦘+5❵⦘❫");
    // ********** handle d/dx_0[loss_function] ****************
    sa::ExpressionHandler derrivative_1_loss_function = sa::calculate_derivative_expression(loss_function, 0);
    ASSERT_EQ(derrivative_1_loss_function.str(), "❴❪❪x_0◦sin⦗❴sq⦗x_1⦘+5❵⦘❫◦0❫+❪❪4◦sin⦗❴sq⦗x_1⦘+5❵⦘❫◦1❫+❪❪4◦x_0❫◦❴❪cos⦗❴sq⦗x_1⦘+5❵⦘◦❴❪1◦❴❪❪2◦x_1❫◦0❫❵❫+❪1◦0❫❵❫❵❫❵");
    sa::dfs_transform(derrivative_1_loss_function, sa::modify_canonical_math, sa::GreedinessLevel::DoDfsForReplacedExpressions);
    ASSERT_EQ(derrivative_1_loss_function.str(), "❪4◦sin⦗❴sq⦗x_1⦘+5❵⦘❫");
    // ********** handle d/dx_1[loss_function] ****************
    sa::ExpressionHandler derrivative_2_loss_function = sa::calculate_derivative_expression(loss_function, 1);
    ASSERT_EQ(derrivative_2_loss_function.str(), "❴❪❪x_0◦sin⦗❴sq⦗x_1⦘+5❵⦘❫◦0❫+❪❪4◦sin⦗❴sq⦗x_1⦘+5❵⦘❫◦0❫+❪❪4◦x_0❫◦❴❪cos⦗❴sq⦗x_1⦘+5❵⦘◦❴❪1◦❴❪❪2◦x_1❫◦1❫❵❫+❪1◦0❫❵❫❵❫❵");
    sa::dfs_transform(derrivative_2_loss_function, sa::modify_canonical_math, sa::GreedinessLevel::DoDfsForReplacedExpressions);
    ASSERT_EQ(derrivative_2_loss_function.str(), "❪8◦x_0◦cos⦗❴sq⦗x_1⦘+5❵⦘◦x_1❫");
    // ********** vector (d/dx_1, d/dx_1)  ********************
    sa::ExpressionHandlerVector loss_function_deivatives;
    loss_function_deivatives.push_back(std::move(derrivative_1_loss_function));
    loss_function_deivatives.push_back(std::move(derrivative_2_loss_function));
    // ********************************************************
    // ********** handle d/dx_0[constraint_function] **********
    const auto constraint_function = sa::ProductExpression::make(4.0_const, 0_var, sin(sq(1_var) + 5.0_const));
    ASSERT_EQ(constraint_function.str(), "❪4◦x_0◦sin⦗❴sq⦗x_1⦘+5❵⦘❫");
    // ********** handle d/dx_0[constraint_function] **********
    sa::ExpressionHandler derrivative_1_constraint_function = sa::calculate_derivative_expression(constraint_function, 0);
    ASSERT_EQ(derrivative_1_constraint_function.str(), "❴❪❪x_0◦sin⦗❴sq⦗x_1⦘+5❵⦘❫◦0❫+❪❪4◦sin⦗❴sq⦗x_1⦘+5❵⦘❫◦1❫+❪❪4◦x_0❫◦❴❪cos⦗❴sq⦗x_1⦘+5❵⦘◦❴❪1◦❴❪❪2◦x_1❫◦0❫❵❫+❪1◦0❫❵❫❵❫❵");
    sa::dfs_transform(derrivative_1_constraint_function, sa::modify_canonical_math, sa::GreedinessLevel::DoDfsForReplacedExpressions);
    ASSERT_EQ(derrivative_1_constraint_function.str(), "❪4◦sin⦗❴sq⦗x_1⦘+5❵⦘❫");
    // ********** handle d/dx_1[constraint_function] **********
    sa::ExpressionHandler derrivative_2_constraint_function = sa::calculate_derivative_expression(constraint_function, 1);
    ASSERT_EQ(derrivative_2_constraint_function.str(), "❴❪❪x_0◦sin⦗❴sq⦗x_1⦘+5❵⦘❫◦0❫+❪❪4◦sin⦗❴sq⦗x_1⦘+5❵⦘❫◦0❫+❪❪4◦x_0❫◦❴❪cos⦗❴sq⦗x_1⦘+5❵⦘◦❴❪1◦❴❪❪2◦x_1❫◦1❫❵❫+❪1◦0❫❵❫❵❫❵");
    sa::dfs_transform(derrivative_2_constraint_function, sa::modify_canonical_math, sa::GreedinessLevel::DoDfsForReplacedExpressions);
    ASSERT_EQ(derrivative_2_constraint_function.str(), "❪8◦x_0◦cos⦗❴sq⦗x_1⦘+5❵⦘◦x_1❫");
    // ********** vector (d/dx_1, d/dx_1)  ********************
    sa::ExpressionHandlerVector constraint_function_deivatives;
    constraint_function_deivatives.push_back(std::move(derrivative_1_constraint_function));
    constraint_function_deivatives.push_back(std::move(derrivative_2_constraint_function));
    // ********************************************************
    std::cout << "A" << std::endl;
    const constrained_optimizer::OptimizationMethodParams optimization_method_params =
            constrained_optimizer::SlpParamsBuilder().build();
    std::cout << "B" << std::endl;
    constrained_optimizer::OptimizationProblemDefinition optimization_problem_definition =
            constrained_optimizer::OptimizationProblemDefinitionBuilder()
            .set_n_variables(2)
            .set_loss_function(loss_function.clone())
            .set_loss_function_deivatives(loss_function_deivatives)
            .set_constraint_function(constraint_function.clone())
            .set_constraint_function_deivatives(constraint_function_deivatives)
            .build();
    std::cout << "C" << std::endl;
    constrained_optimizer::optimize(optimization_problem_definition, optimization_method_params);
}
