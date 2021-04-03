// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_simplify_linear_combination.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifySimplifyLinearCombination, OnBosonPrimitiveOperator) {
    auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "9.1");
}

TEST(ModifySimplifyLinearCombination, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifySimplifyLinearCombination, OnProductOfBosonPrimitiveOperators) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifySimplifyLinearCombination, OnFactorExpression) {
    auto expression = (4 * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4•x_4❫");
    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪4•x_4❫");
}

TEST(ModifySimplifyLinearCombination, MinimalWorkingExample1) {
    auto expression = (4 * 4_var) + (7 * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4•x_4❫+❪7•x_4❫❵");
    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪11•x_4❫❵");
}

TEST(ModifySimplifyLinearCombination, MinimalWorkingExample2) {
    auto expression = sa::SumExpression::make((4 * 4_var), (12 * 1_var), (-7 * 4_var), (31 * 3_var), (5 * 1_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4•x_4❫+❪12•x_1❫+❪-7•x_4❫+❪31•x_3❫+❪5•x_1❫❵");
    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪-3•x_4❫+❪17•x_1❫+❪31•x_3❫❵");
}

TEST(ModifySimplifyLinearCombination, MinimalWorkingExample3) {
    auto expression = sa::SumExpression::make((4 * (4_var * 0_var)), (12 * 1_var), (-7 * (4_var * 0_var)), (-7 * (4_var + 0_var)));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4•❪x_4◦x_0❫❫+❪12•x_1❫+❪-7•❪x_4◦x_0❫❫+❪-7•❴x_4+x_0❵❫❵");
    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪-3•❪x_4◦x_0❫❫+❪12•x_1❫+❪-7•❴x_4+x_0❵❫❵");
}

TEST(ModifySimplifyLinearCombination, MinimalNotWorkingExample1) {
    auto expression = (4 * 4_var) * (4 * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪4•x_4❫◦❪4•x_4❫❫");
    const auto modification_result = modify_simplify_linear_combination(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪❪4•x_4❫◦❪4•x_4❫❫");
}
