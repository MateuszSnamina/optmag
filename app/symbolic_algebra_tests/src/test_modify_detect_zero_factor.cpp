// TESTED LIBRARY:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_detect_zero_factor.hpp>
#include <symbolic_algebra/expression.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyDetectZeroFactor, OnBosonPrimitiveOperator) {
    auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "9.1");
}

TEST(ModifyDetectZeroFactor, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyDetectZeroFactor, OnProductOfBosonPrimitiveOperators) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifyDetectZeroFactor, OnNoZeroFactorExpression) {
    auto expression = (4 * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•x_4❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪4•x_4❫");
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression1) {
    auto expression = (0 * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪0•x_4❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression2) {
    auto expression = (4 * sa::SumExpression::make_zero());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•𝟘❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression3) {
    auto expression = (0 * sa::SumExpression::make_zero());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪0•𝟘❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnNestedFactorExpression) {
    auto expression = (4 * (0 * 4_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•❪0•x_4❫❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroFactor, NotWorking) {
    auto expression = (4 * (sa::SumExpression::make_zero() + sa::SumExpression::make_zero()));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•❴𝟘+𝟘❵❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
}
