// TESTED LIBRARY:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/calculate_expression_value.hpp>
#include <symbolic_algebra/calculate_expression_derivative.hpp>
#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/modify_canonical_math.hpp>
#include <symbolic_algebra/util_make.hpp>

// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;
using namespace sa::math;


/*
 * **Holistic example**
 *
 * This is holistic example for expression = ❪4◦x_1◦sin⦗❴sq⦗x_2⦘+5❵⦘❫
 *
 * **Calculation of d/dx_1[expression]**
 *
 * d/dx_1[expression] = ❴❪❪x_1◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦AAAA1❫+❪❪4◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦AAAA2❫+❪❪4◦x_1❫◦AAAA3❫❵
 * where: AAAA1 = d/dx_1 4
 *              = 0
 * where: AAAA2 = d/dx_1 x_1
 *              = 1
 * where: AAAA3 = d/dx_1 sin⦗❴sq⦗x_2⦘+5❵⦘
 *              = ❴❪cos⦗❴sq⦗x_2⦘+5❵⦘◦BBBBB❫❵
 * where: BBBB  = d/dx_1 ❴sq⦗x_2⦘+5❵
 *              = ❴❪1◦CCCC❫+❪1◦0❫❵
 * where: CCCC  = d/dx_1 sq⦗x_2⦘
 *              = ❴❪❪2◦x_2❫◦DDDD❫❵
 * where: DDDD  = d/dx_1 x_2
 *              = 0
 * So:
 * d/dx_1[expression] = ❴❪❪x_1◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦0❫+❪❪4◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦1❫+❪❪4◦x_1❫◦❴❪cos⦗❴sq⦗x_2⦘+5❵⦘◦❴❪1◦❴❪❪2◦x_2❫◦0❫❵❫+❪1◦0❫❵❫❵❫❵
 *
 * **Calculation of d/dx_2[expression]**
 *
 * d/dx_1[expression] = ❴❪❪x_1◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦AAAA1❫+❪❪4◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦AAAA2❫+❪❪4◦x_1❫◦AAAA3❫❵
 * where: AAAA1 = d/dx_2 4
 *              = 0
 * where: AAAA2 = d/dx_2 x_1
 *              = 0
 * where: AAAA3 = d/dx_2 sin⦗❴sq⦗x_2⦘+5❵⦘
 *              = ❴❪cos⦗❴sq⦗x_2⦘+5❵⦘◦BBBBB❫❵
 * where: BBBB  = d/dx_2 ❴sq⦗x_2⦘+5❵
 *              = ❴❪1◦CCCC❫+❪1◦0❫❵
 * where: CCCC  = d/dx_2 sq⦗x_2⦘
 *              = ❴❪❪2◦x_2❫◦DDDD❫❵
 * where: DDDD  = d/dx_2 x_2
 *              = 1
 * So:
 * d/dx_1[expression] = ❴❪❪x_1◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦0❫+❪❪4◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦0❫+❪❪4◦x_1❫◦❴❪cos⦗❴sq⦗x_2⦘+5❵⦘◦❴❪1◦❴❪❪2◦x_2❫◦1❫❵❫+❪1◦0❫❵❫❵❫❵
 *
 * ** Queries in Woflra Alpha **
 * Query: f(x,y)=(4*x*sin((y*y+5))) at x=1, y=2
 * Gives: f(x,y)=3.17583
 * Query: f1(x,y)=d/dx(4*x*sin((y*y+5))) at x=-1.1, y=2.6
 * Gives: f1(x,y)=-2.88712
 * Query: f2(x,y)=d/dy(4*x*sin((y*y+5))) at x=-1.1, y=2.6
 * Gives: f2(x,y)=-15.8358
 */
TEST(Holistic, Example1) {
    const auto expression = sa::ProductExpression::make(4.0_const, 1_var, sin(sq(2_var) + 5.0_const));
    ASSERT_EQ(expression.str(), "❪4◦x_1◦sin⦗❴sq⦗x_2⦘+5❵⦘❫");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{5.6, -1.1, 2.6});
    ASSERT_DOUBLE_EQ(value, 3.1758317969075889);
    // ********************************
    {
        // ********** handle d/dx_1[expression] **********
        sa::ExpressionHandler derrivative_1_expression = sa::calculate_derivative_expression(expression, 1);
        std::cout << derrivative_1_expression.str() << std::endl;
        ASSERT_EQ(derrivative_1_expression.str(), "❴❪❪x_1◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦0❫+❪❪4◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦1❫+❪❪4◦x_1❫◦❴❪cos⦗❴sq⦗x_2⦘+5❵⦘◦❴❪1◦❴❪❪2◦x_2❫◦0❫❵❫+❪1◦0❫❵❫❵❫❵");
        const auto value_1 = sa::calculate_expression_value(derrivative_1_expression, arma::vec{5.6, -1.1, 2.6});
        ASSERT_DOUBLE_EQ(value_1, -2.8871198153705353);
        // ********** simplify ***************************
        sa::dfs_transform(derrivative_1_expression, sa::modify_canonical_math, sa::GreedinessLevel::RepeatForReplacedExpressions);
        // sa::dfs_transform(expression, sa::modify_rebuild_sum_into_linear_combination);
        // sa::dfs_transform(expression, sa::modify_simplify_linear_combination);
        // sa::dfs_transform(expression, sa::modify_detect_one_factor);
        // sa::dfs_transform(expression, sa::modify_detect_zero_factor);
        std::cout << derrivative_1_expression.str() << std::endl;
        //ASSERT_EQ(derrivative_1_expression.str(), "XXXXXXXXXXX");
        const auto value_1_re = sa::calculate_expression_value(derrivative_1_expression, arma::vec{5.6, -1.1, 2.6});
        ASSERT_DOUBLE_EQ(value_1_re, -2.8871198153705353);
    }
    {
        // ********** handle d/dx_2[expression] **********
        sa::ExpressionHandler derrivative_2_expression = sa::calculate_derivative_expression(expression, 2);
        // std::cout << derrivative_2_expression.str() << std::endl;
        ASSERT_EQ(derrivative_2_expression.str(), "❴❪❪x_1◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦0❫+❪❪4◦sin⦗❴sq⦗x_2⦘+5❵⦘❫◦0❫+❪❪4◦x_1❫◦❴❪cos⦗❴sq⦗x_2⦘+5❵⦘◦❴❪1◦❴❪❪2◦x_2❫◦1❫❵❫+❪1◦0❫❵❫❵❫❵");
        const auto value_2 = sa::calculate_expression_value(derrivative_2_expression, arma::vec{5.6, -1.1, 2.6});
        ASSERT_DOUBLE_EQ(value_2, -15.835765167341281);
        // ********** simplify ***************************
        sa::dfs_transform(derrivative_2_expression, sa::modify_canonical_math, sa::GreedinessLevel::RepeatForReplacedExpressions);
        // sa::dfs_transform(expression, sa::modify_rebuild_sum_into_linear_combination);
        // sa::dfs_transform(expression, sa::modify_simplify_linear_combination);
        // sa::dfs_transform(expression, sa::modify_detect_one_factor);
        // sa::dfs_transform(expression, sa::modify_detect_zero_factor);
        std::cout << derrivative_2_expression.str() << std::endl;
        //ASSERT_EQ(derrivative_2_expression.str(), "XXXXXXXXXXX");
        const auto value_2_re = sa::calculate_expression_value(derrivative_2_expression, arma::vec{5.6, -1.1, 2.6});
        ASSERT_DOUBLE_EQ(value_2_re, -15.835765167341281);
    }
}


