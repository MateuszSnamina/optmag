// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp-OLD>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_rebuild_factor_sum_into_sum_factors.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

//TEST(ModifyRebuildFactorSumIntoSumFactors, OnBosonPrimitiveOperator) {
//    auto expression = 'd'_cr;
//    ASSERT_EQ(expression.str(), "♯d");
//    //std::cout << expression.str() << std::endl;
//    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "♯d");
//}

//TEST(ModifyRebuildFactorSumIntoSumFactors, OnEmptyProduct) {
//    auto expression = sa::ProductExpression::make();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "𝕀");
//    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝕀");
//}

//TEST(ModifyRebuildFactorSumIntoSumFactors, OnProductOfBosonPrimitiveOperators) {
//    auto expression = ('a'_cr * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
//    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
//}

//TEST(ModifyRebuildFactorSumIntoSumFactors, OnFactoredExpression1) {
//    auto expression = (4 * 'b'_cr);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4♯b❫");
//    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪4♯b❫");
//}

//TEST(ModifyRebuildFactorSumIntoSumFactors, OnFactoredExpression2) {
//    auto expression = (4 * ('d'_an * 'a'_cr));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4❪♭d◦♯a❫❫");
//    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪4❪♭d◦♯a❫❫");
//}

//TEST(ModifyRebuildFactorSumIntoSumFactors, MinimalExample1) {
//    auto expression = (4 * ('d'_an + 'a'_cr));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4❴♭d+♯a❵❫");
//    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪4♭d❫+❪4♯a❫❵");
//}

//TEST(ModifyRebuildFactorSumIntoSumFactors, MinimalExample2) {
//    auto expression = (4 * sa::SumExpression::make('d'_an, 'a'_cr, (2 * 'c'_cr)));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪4❴♭d+♯a+❪2♯c❫❵❫");
//    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪4♭d❫+❪4♯a❫+❪4❪2♯c❫❫❵");
//}
