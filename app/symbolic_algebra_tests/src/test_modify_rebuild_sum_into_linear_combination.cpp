// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_rebuild_sum_into_linear_combination.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyRebuildSumIntoLinearCombination, OnBosonPrimitiveOperator) {
    auto expression = 9_var;
    ASSERT_EQ(expression.str(), "x_9");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_rebuild_sum_into_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "x_9");
}

TEST(ModifyRebuildSumIntoLinearCombination, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_rebuild_sum_into_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyRebuildSumIntoLinearCombination, OnEmptySum) {
    auto expression = sa::SumExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝟘");
    const auto modification_result = modify_rebuild_sum_into_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyRebuildSumIntoLinearCombination, OnProductOfBosonPrimitiveOperators) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_rebuild_sum_into_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifyRebuildSumIntoLinearCombination, OnSumOfBosonPrimitiveOperators) {
    auto expression = (0_var + 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴x_0+x_4❵");
    const auto modification_result = modify_rebuild_sum_into_linear_combination(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪+x_0❫+❪+x_4❫❵");
}

TEST(ModifyRebuildSumIntoLinearCombination, BigExample1) {
    auto expression = sa::SumExpression::make((4 * 7_var), (0_var * 3_var), (5 * 1_var), 10_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4x_7❫+❪x_0◦x_3❫+❪5x_1❫+x_10❵");
    const auto modification_result = modify_rebuild_sum_into_linear_combination(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪4x_7❫+❪+❪x_0◦x_3❫❫+❪5x_1❫+❪+x_10❫❵");
}
