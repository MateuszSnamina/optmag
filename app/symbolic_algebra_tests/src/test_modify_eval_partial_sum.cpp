// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_eval_partial_sum.hpp>
#include <symbolic_algebra/expression_final_structural_blocks.hpp>

// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyEvalPartialSum, OnConst) {
    auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "9.1");
}

TEST(ModifyEvalPartialSum, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyEvalPartialSum, OnProductOfVars) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifyEvalPartialSum, OnFactoredExpression1) {
    auto expression = (4 * 3_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•x_3❫");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪4•x_3❫");
}

TEST(ModifyEvalPartialSum, MinimalExample1) {
    auto expression = (6.1_const * 5.4_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪6.1◦5.4❫");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪6.1◦5.4❫");
}

TEST(ModifyEvalPartialSum, MinimalExample2) {
    auto expression = sa::ProductExpression::make(6.1_const, 6_var,  5.4_const, 9_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪6.1◦x_6◦5.4◦x_9❫");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪6.1◦x_6◦5.4◦x_9❫");
}

TEST(ModifyEvalPartialSum, MinimalExample3) {
    auto expression = sa::ProductExpression::make(6.1_const, 6_var,  5.4_const, 9_var, 5.9_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪6.1◦x_6◦5.4◦x_9◦5.9❫");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪6.1◦x_6◦5.4◦x_9◦5.9❫");
}

TEST(ModifyEvalPartialSum, MinimalExample4) {
    auto expression = (6.1_const + 5.4_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴6.1+5.4❵");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴11.5❵");
}

TEST(ModifyEvalPartialSum, MinimalExample5) {
    auto expression = sa::SumExpression::make(6.1_const, 6_var, 5.4_const, 9_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴6.1+x_6+5.4+x_9❵");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴11.5+x_6+x_9❵");
}

TEST(ModifyEvalPartialSum, MinimalExample6) {
    auto expression = sa::SumExpression::make(6.1_const, 6_var, 5.4_const, 9_var, 5.9_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴6.1+x_6+5.4+x_9+5.9❵");
    const auto modification_result = modify_eval_partial_sum(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴17.4+x_6+x_9❵");
}

