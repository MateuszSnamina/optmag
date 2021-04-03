// TESTED LIBRARY:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_detect_zero_factor.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

//TEST(ModifyDetectZeroFactor, OnBosonPrimitiveOperator) {
//    auto expression = 'd'_cr;
//    ASSERT_EQ(expression.str(), "♯d");
//    //std::cout << expression.str() << std::endl;
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "♯d");
//}

//TEST(ModifyDetectZeroFactor, OnEmptyProduct) {
//    auto expression = sa::ProductExpression::make();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "𝕀");
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝕀");
//}

//TEST(ModifyDetectZeroFactor, OnProductOfBosonPrimitiveOperators) {
//    auto expression = ('a'_cr * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
//}

//TEST(ModifyDetectZeroFactor, OnNoZeroFactorExpression) {
//    auto expression = (4 * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4♭b❫");
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪4♭b❫");
//}

//TEST(ModifyDetectZeroFactor, OnZeroFactorExpression1) {
//    auto expression = (0 * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪0♭b❫");
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝟘");
//}

//TEST(ModifyDetectZeroFactor, OnZeroFactorExpression2) {
//    auto expression = (4 * sa::SumExpression::make_zero());
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4𝟘❫");
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝟘");
//}

//TEST(ModifyDetectZeroFactor, OnZeroFactorExpression3) {
//    auto expression = (0 * sa::SumExpression::make_zero());
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪0𝟘❫");
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝟘");
//}

//TEST(ModifyDetectZeroFactor, OnNestedFactorExpression) {
//    auto expression = (4 * (0 * 'b'_an));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4❪0♭b❫❫");
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//}

//TEST(ModifyDetectZeroFactor, NotWorking) {
//    auto expression = (4 * (sa::SumExpression::make_zero() + sa::SumExpression::make_zero()));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4❴𝟘+𝟘❵❫");
//    const auto modification_result = modify_detect_zero_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//}
