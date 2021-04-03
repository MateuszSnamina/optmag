// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_rebuild_factor_sum_into_sum_factors.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyRebuildFactorSumIntoSumFactors, OnBosonPrimitiveOperator) {
    auto expression = 9_var;
    ASSERT_EQ(expression.str(), "x_9");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "x_9");
}

TEST(ModifyRebuildFactorSumIntoSumFactors, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyRebuildFactorSumIntoSumFactors, OnProductOfBosonPrimitiveOperators) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifyRebuildFactorSumIntoSumFactors, OnFactoredExpression1) {
    auto expression = (4 * 3_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4x_3❫");
    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪4x_3❫");
}

TEST(ModifyRebuildFactorSumIntoSumFactors, OnFactoredExpression2) {
    auto expression = (4 * (10_var * 0_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❪x_10◦x_0❫❫");
    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪4❪x_10◦x_0❫❫");
}

TEST(ModifyRebuildFactorSumIntoSumFactors, MinimalExample1) {
    auto expression = (4 * (10_var + 0_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❴x_10+x_0❵❫");
    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪4x_10❫+❪4x_0❫❵");
}

TEST(ModifyRebuildFactorSumIntoSumFactors, MinimalExample2) {
    auto expression = (4 * sa::SumExpression::make(10_var, 0_var, (2 * 6_var)));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❴x_10+x_0+❪2x_6❫❵❫");
    const auto modification_result = modify_rebuild_factor_sum_into_sum_factors(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪4x_10❫+❪4x_0❫+❪4❪2x_6❫❫❵");
}
