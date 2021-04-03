// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_detect_zero_product.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyDetectZeroProduct, OnConst) {
    auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnProductOfVars) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnFactorExpression) {
    auto expression = (4 * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•x_4❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnNestedFactorExpression) {
    auto expression = (4 * (-6 * 4_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•❪-6•x_4❫❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnZeroProduct1) {
    auto expression = (sa::SumExpression::make_zero() * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪𝟘◦x_4❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroProduct, OnZeroProduct2) {
    auto expression = sa::ProductExpression::make(4_var, sa::SumExpression::make_zero(), 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_4◦𝟘◦x_4❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroProduct, OnSumWithZero) {
    auto expression = (sa::SumExpression::make_zero() + 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴𝟘+x_4❵");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}
