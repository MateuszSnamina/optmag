// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_flatten_factor.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

//TEST(ModifyFlattenFactor, OnBosonPrimitiveOperator) {
//    auto expression = 'd'_cr;
//    ASSERT_EQ(expression.str(), "♯d");
//    //std::cout << expression.str() << std::endl;
//    const auto modification_result = modify_flatten_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "♯d");
//}

//TEST(ModifyFlattenFactor, OnEmptyProduct) {
//    auto expression = sa::ProductExpression::make();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "𝕀");
//    const auto modification_result = modify_flatten_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝕀");
//}

//TEST(ModifyFlattenFactor, OnProductOfBosonPrimitiveOperators) {
//    auto expression = ('a'_cr * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
//    const auto modification_result = modify_flatten_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
//}

//TEST(ModifyFlattenFactor, OnFactorExpression) {
//    auto expression = (4 * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4♭b❫");
//    const auto modification_result = modify_flatten_factor(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪4♭b❫");
//}

//TEST(ModifyFlattenFactor, OnNestedFactorExpression) {
//    auto expression = (4 * (-6 * 'b'_an));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4❪-6♭b❫❫");
//    const auto modification_result = modify_flatten_factor(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪-24♭b❫");
//}
