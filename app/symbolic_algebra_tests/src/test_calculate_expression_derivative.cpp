#include<symbolic_algebra/calculate_expression_value.hpp>

// TESTED LIBRARY:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/calculate_expression_derivative.hpp>
#include <symbolic_algebra/util_make.hpp>

// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(CalculateExpressionDerivative, ProductDerivativeExpressionMaker) {
    const auto formal_arguments = sa::util::make<sa::ExpressionHandlerVector>(11.1_const, 12.1_const, 13.1_const, 14.1_const);
    const sa::ExpressionHandler derrivative_expression = sa::derivatives_table::ProductDerivativeExpressionMaker{}.make(2, formal_arguments);
    ASSERT_EQ(derrivative_expression.str(), "❪11.6◦12.6◦14.6❫");
}

TEST(CalculateExpressionDerivative, SumDerivativeExpressionMaker) {
    const auto formal_arguments = sa::util::make<sa::ExpressionHandlerVector>(11.1_const, 12.1_const, 13.1_const, 14.1_const);
    const sa::ExpressionHandler derrivative_expression = sa::derivatives_table::SumDerivativeExpressionMaker{}.make(2, formal_arguments);
    ASSERT_EQ(derrivative_expression.str(), "1");
}

TEST(CalculateExpressionDerivative, OnConst) {
    const auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "0");
}

TEST(CalculateExpressionDerivative, OnVar0) {
    const auto expression = 3_var;
    ASSERT_EQ(expression.str(), "x_3");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "0");
}

TEST(CalculateExpressionDerivative, OnVar1) {
    const auto expression = 2_var;
    ASSERT_EQ(expression.str(), "x_2");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "1");
}

TEST(CalculateExpressionDerivative, OnRealFactored1) {
    const auto expression = 4*9.1_const;
    ASSERT_EQ(expression.str(), "❪4•9.1❫");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❪4•0❫");
}

TEST(CalculateExpressionDerivative, OnRealFactored2) {
    const auto expression = sa::RealFactoredExpression::make(-5.6, 9.1_const);
    ASSERT_EQ(expression.str(), "❪-5.6•9.1❫");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❪-5.6•0❫");
}

TEST(CalculateExpressionDerivative, OnSum1) {
    auto expression = sa::SumExpression::make(10.2_const, 0_var, 2_var, 3.0_const);
    ASSERT_EQ(expression.str(), "❴10.2+x_0+x_2+3❵");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪1◦0❫+❪1◦0❫+❪1◦1❫+❪1◦0❫❵");
}

TEST(CalculateExpressionDerivative, OnSum2) {
    auto expression = sa::SumExpression::make(10.2_const, 0_var, 2_var, 3.0_const);
    ASSERT_EQ(expression.str(), "❴10.2+x_0+x_2+3❵");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 1);
    ASSERT_EQ(derrivative_expression.str(), "❴❪1◦0❫+❪1◦0❫+❪1◦0❫+❪1◦0❫❵");
}

TEST(CalculateExpressionDerivative, OnProduct1) {
    auto expression = sa::ProductExpression::make(10.2_const, 0_var, 2_var, 3.0_const);
    ASSERT_EQ(expression.str(), "❪10.2◦x_0◦x_2◦3❫");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪❪x_0◦x_2◦3❫◦0❫+❪❪10.2◦x_2◦3❫◦0❫+❪❪10.2◦x_0◦3❫◦1❫+❪❪10.2◦x_0◦x_2❫◦0❫❵");
}

TEST(CalculateExpressionDerivative, OnProduct2) {
    auto expression = sa::ProductExpression::make(10.2_const, 0_var, 2_var, 3.0_const);
    ASSERT_EQ(expression.str(), "❪10.2◦x_0◦x_2◦3❫");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 1);
    ASSERT_EQ(derrivative_expression.str(), "❴❪❪x_0◦x_2◦3❫◦0❫+❪❪10.2◦x_2◦3❫◦0❫+❪❪10.2◦x_0◦3❫◦0❫+❪❪10.2◦x_0◦x_2❫◦0❫❵");
}

TEST(CalculateExpressionDerivative, MinimalExample1) {
    auto expression = (4 * sa::SumExpression::make(10.2_const, 0_var, 2_var, 3.0_const));
    ASSERT_EQ(expression.str(), "❪4•❴10.2+x_0+x_2+3❵❫");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❪4•❴❪1◦0❫+❪1◦0❫+❪1◦1❫+❪1◦0❫❵❫");
}


TEST(CalculateExpressionDerivative, MinimalExample2) {
    auto expression = (4 * sa::SumExpression::make(10.2_const, 0_var, 2_var, 3.0_const));
    ASSERT_EQ(expression.str(), "❪4•❴10.2+x_0+x_2+3❵❫");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 1);
    ASSERT_EQ(derrivative_expression.str(), "❪4•❴❪1◦0❫+❪1◦0❫+❪1◦0❫+❪1◦0❫❵❫");
}

TEST(CalculateExpressionDerivative, MinimalExample3) {
    auto expression = (4 * sa::SumExpression::make(10.2_const, 2_var, (2 * 2_var)));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•❴10.2+x_2+❪2•x_2❫❵❫");
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❪4•❴❪1◦0❫+❪1◦1❫+❪1◦❪2•1❫❫❵❫");
}
