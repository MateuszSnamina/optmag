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
using namespace sa::math;

TEST(CalculateExpressionDerivative, ProductDerivativeExpressionMaker) {
    const auto formal_arguments = sa::util::make<sa::ExpressionHandlerVector>(11.1_const, 12.1_const, 13.1_const, 14.1_const);
    const sa::ExpressionHandler derrivative_expression = sa::derivatives_table::ProductDerivativeExpressionMaker{}.make(2, formal_arguments);
    ASSERT_EQ(derrivative_expression.str(), "❪11.1◦12.1◦14.1❫");
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

TEST(CalculateExpressionDerivative, OnInv) {
    const auto expression = inv(2_var);
    ASSERT_EQ(expression.str(), "inv⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪❪-1◦inv⦗sq⦗x_2⦘⦘❫◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnSq) {
    const auto expression = sq(2_var);
    ASSERT_EQ(expression.str(), "sq⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪❪2◦x_2❫◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnCb) {
    const auto expression = cb(2_var);
    ASSERT_EQ(expression.str(), "cb⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪❪3◦sq⦗x_2⦘❫◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnSin) {
    const auto expression = sin(2_var);
    ASSERT_EQ(expression.str(), "sin⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪cos⦗x_2⦘◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnCos) {
    const auto expression = cos(2_var);
    ASSERT_EQ(expression.str(), "cos⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪❪-1◦sin⦗x_2⦘❫◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnTan) {
    const auto expression = tan(2_var);
    ASSERT_EQ(expression.str(), "tan⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪inv⦗sq⦗cos⦗x_2⦘⦘⦘◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnAsin) {
    const auto expression = asin(2_var);
    ASSERT_EQ(expression.str(), "asin⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪inv⦗sqrt⦗❴1+❪-1◦sq⦗x_2⦘❫❵⦘⦘◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnAcos) {
    const auto expression = acos(2_var);
    ASSERT_EQ(expression.str(), "acos⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪❪-1◦inv⦗sqrt⦗❴1+❪-1◦sq⦗x_2⦘❫❵⦘⦘❫◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnAtan) {
    const auto expression = atan(2_var);
    ASSERT_EQ(expression.str(), "atan⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    ASSERT_EQ(derrivative_expression.str(), "❴❪inv⦗❴1+sq⦗x_2⦘❵⦘◦1❫❵");
}

TEST(CalculateExpressionDerivative, OnSqrt) {
    const auto expression = sqrt(2_var);
    ASSERT_EQ(expression.str(), "sqrt⦗x_2⦘");
    //std::cout << expression.str() << std::endl;
    //const sa::ExpressionHandler derrivative_expression = sa::calculate_derivative_expression(expression, 2);
    //ASSERT_EQ(derrivative_expression.str(), "❴❪❪0.5◦sqrt⦗x_2⦘❫◦1❫❵");
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
