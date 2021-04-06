#include<symbolic_algebra/calculate_expression_value.hpp>

// TESTED LIBRARY:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/calculate_expression_value.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;
using namespace sa::math;

TEST(CalculateExpressionValue, OnConst) {
    const auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, 9.1);
}

TEST(CalculateExpressionValue, OnVar) {
    const auto expression = 3_var;
    ASSERT_EQ(expression.str(), "x_3");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9});
    ASSERT_DOUBLE_EQ(value, -8.9);
}

TEST(CalculateExpressionValue, OnRealFactored1) {
    const auto expression = 4*9.1_const;
    ASSERT_EQ(expression.str(), "❪4•9.1❫");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, 4 * 9.1);
}

TEST(CalculateExpressionValue, OnRealFactored2) {
    const auto expression = sa::RealFactoredExpression::make(-5.6, 9.1_const);
    ASSERT_EQ(expression.str(), "❪-5.6•9.1❫");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, (-5.6) * 9.1);
}

TEST(CalculateExpressionValue, OnRealFactored3) {
    const auto expression = sa::RealFactoredExpression::make(5.6, sa::ConstantExpression::make(-9.1));
    ASSERT_EQ(expression.str(), "❪5.6•-9.1❫");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_EQ(value, 5.6 * (-9.1));
}

TEST(CalculateExpressionValue, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_EQ(value, 1);
}

TEST(CalculateExpressionValue, OnProductOneConst) {
    auto expression = sa::ProductExpression::make(4.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4.2❫");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_EQ(value, 4.2);
}

TEST(CalculateExpressionValue, OnProductTwoConsts) {
    auto expression = sa::ProductExpression::make(4.2_const, 1.7_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4.2◦1.7❫");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_EQ(value, 4.2 * 1.7);
}

TEST(CalculateExpressionValue, OnProductThreeConsts) {
    auto expression = sa::ProductExpression::make(4.2_const, 1.7_const, 3.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4.2◦1.7◦3.2❫");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, 4.2 * 1.7 * 3.2);
}

TEST(CalculateExpressionValue, OnEmptySum) {
    auto expression = sa::SumExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝟘");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, 0);
}

TEST(CalculateExpressionValue, OnSumOneConst) {
    auto expression = sa::SumExpression::make(4.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴4.2❵");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, 4.2);
}

TEST(CalculateExpressionValue, OnSumTwoConsts) {
    auto expression = sa::SumExpression::make(4.2_const, 1.7_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴4.2+1.7❵");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, 4.2 + 1.7);
}

TEST(CalculateExpressionValue, OnSumThreeConsts) {
    auto expression = sa::SumExpression::make(4.2_const, 1.7_const, 3.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴4.2+1.7+3.2❵");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, 4.2 + 1.7 + 3.2);
}

TEST(CalculateExpressionValue, OnSin) {
    auto expression = sin(4.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "sin⦗4.2⦘");
    //std::cout << expression.str() << std::endl;
    const auto value = sa::calculate_expression_value(expression, arma::vec{});
    ASSERT_DOUBLE_EQ(value, std::sin(4.2));
}

TEST(CalculateExpressionValue, MinimalExample1) {
    auto expression = sa::ProductExpression::make(0_var, (4_var + 6.1_const), 9.1_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦❴x_4+6.1❵◦9.1❫");
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9, -11.3});
    ASSERT_DOUBLE_EQ(value, (+1.2)*((-11.3)+6.1)*9.1);
}

TEST(CalculateExpressionValue, MinimalExample2) {
    auto expression = (0_var * (4_var + 6.1_const));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦❴x_4+6.1❵❫");
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9, -11.3});
    ASSERT_DOUBLE_EQ(value, (+1.2)*((-11.3)+6.1));
}

TEST(CalculateExpressionValue, MinimalExample3) {
    auto expression = ((4_var + 6.1_const) * 9.1_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴x_4+6.1❵◦9.1❫");
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9, -11.3});
    ASSERT_DOUBLE_EQ(value, ((-11.3)+6.1)*9.1);
}

TEST(CalculateExpressionValue, MinimalExample4) {
    auto expression = sa::ProductExpression::make((4_var + 6.1_const));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴x_4+6.1❵❫");
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9, -11.3});
    ASSERT_DOUBLE_EQ(value, (-11.3)+6.1);
}

TEST(CalculateExpressionValue, MinimalExample5) {
    auto expression = sa::ProductExpression::make(sa::SumExpression::make_zero());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪𝟘❫");
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9, -11.3});
    ASSERT_DOUBLE_EQ(value, 0);
}

TEST(CalculateExpressionValue, MinimalExample6) {
    auto expression = ((4_var + 6.1_const) * (2 * 9.1_const));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴x_4+6.1❵◦❪2•9.1❫❫");
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9, -11.3});
    ASSERT_DOUBLE_EQ(value, ((-11.3)+6.1)*(2*9.1));}

TEST(CalculateExpressionValue, MinimalExample7) {
    auto expression = sin(sa::ProductExpression::make(0_var, (4_var * 6.1_const), 9.1_const));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "sin⦗❪x_0◦❪x_4◦6.1❫◦9.1❫⦘");
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9, -11.3});
    ASSERT_DOUBLE_EQ(value, std::sin((+1.2)*((-11.3)*6.1)*9.1));
}

TEST(CalculateExpressionValue, MinimalExample8) {
    auto expression = (sa::SumExpression::make_zero() * 9.1_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪𝟘◦9.1❫");
    const auto value = sa::calculate_expression_value(expression, arma::vec{+1.2, -3.4, +4.5, -8.9, -11.3});
    ASSERT_DOUBLE_EQ(value, 0*9.1);
}
