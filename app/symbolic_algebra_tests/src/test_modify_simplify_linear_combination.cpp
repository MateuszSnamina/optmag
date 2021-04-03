// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_simplify_linear_combination.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

//TEST(ModifySimplifyLinearCombination, OnBosonPrimitiveOperator) {
//    auto expression = 'd'_cr;
//    ASSERT_EQ(expression.str(), "♯d");
//    //std::cout << expression.str() << std::endl;
//    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "♯d");
//}

//TEST(ModifySimplifyLinearCombination, OnEmptyProduct) {
//    auto expression = sa::ProductExpression::make();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "𝕀");
//    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝕀");
//}

//TEST(ModifySimplifyLinearCombination, OnProductOfBosonPrimitiveOperators) {
//    auto expression = ('a'_cr * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
//    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
//}

//TEST(ModifySimplifyLinearCombination, OnFactorExpression) {
//    auto expression = (4 * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4♭b❫");
//    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪4♭b❫");
//}

//TEST(ModifySimplifyLinearCombination, MinimalWorkingExample1) {
//    auto expression = (4 * 'b'_an) + (7 * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❴❪4♭b❫+❪7♭b❫❵");
//    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪11♭b❫❵");
//}

//TEST(ModifySimplifyLinearCombination, MinimalWorkingExample2) {
//    auto expression = sa::SumExpression::make((4 * 'b'_an), (12 * 'a'_an), (-7 * 'b'_an), (31 * 'b'_cr), (5 * 'a'_an));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❴❪4♭b❫+❪12♭a❫+❪-7♭b❫+❪31♯b❫+❪5♭a❫❵");
//    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪-3♭b❫+❪17♭a❫+❪31♯b❫❵");
//}

//TEST(ModifySimplifyLinearCombination, MinimalWorkingExample3) {
//    auto expression = sa::SumExpression::make((4 * ('b'_an * 'a'_cr)), (12 * 'a'_an), (-7 * ('b'_an * 'a'_cr)), (-7 * ('b'_an + 'a'_cr)));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❴❪4❪♭b◦♯a❫❫+❪12♭a❫+❪-7❪♭b◦♯a❫❫+❪-7❴♭b+♯a❵❫❵");
//    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪-3❪♭b◦♯a❫❫+❪12♭a❫+❪-7❴♭b+♯a❵❫❵");
//}

//TEST(ModifySimplifyLinearCombination, MinimalNotWorkingExample1) {
//    auto expression = (4 * 'b'_an) * (4 * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪❪4♭b❫◦❪4♭b❫❫");
//    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪❪4♭b❫◦❪4♭b❫❫");
//}
