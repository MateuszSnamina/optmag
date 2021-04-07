// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_remove_const_zeros_from_sum.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyRemoveConstZerosFromSum, OnConst) {
    auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "9.1");
}

TEST(ModifyRemoveConstZerosFromSum, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyRemoveConstZerosFromSum, OnEmptySum) {
    auto expression = sa::SumExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝟘");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyRemoveConstZerosFromSum, OnProductOfVars) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifyRemoveConstZerosFromSum, OnSumOfVars) {
    auto expression = (0_var + 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴x_0+x_4❵");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴x_0+x_4❵");
}

TEST(ModifyRemoveConstZerosFromSum, MinimalWorkingExample1) {
    auto expression = (0_var + 0.0_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴x_0+0❵");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴x_0❵");
}

TEST(ModifyRemoveConstZerosFromSum, MinimalWorkingExample2) {
    auto expression = sa::SumExpression::make(0_var, 0.0_const, 1.1_const, 0.0_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴x_0+0+1.1+0❵");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴x_0+1.1❵");
}

TEST(ModifyRemoveConstZerosFromSum, MinimalWorkingExample3) {
    auto expression = (0_var * 0.0_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦0❫");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦0❫");
}

TEST(ModifyRemoveConstZerosFromSum, MinimalWorkingExample4) {
    auto expression = sa::ProductExpression::make(0_var, 0.0_const, 1.1_const, 0.0_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦0◦1.1◦0❫");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦0◦1.1◦0❫");
}

TEST(ModifyRemoveConstZerosFromSum, BigExample1) {
    auto expression = sa::SumExpression::make((4 * 7.2_const), (0_var * 3_var), (5 * 1_var), 10.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4•7.2❫+❪x_0◦x_3❫+❪5•x_1❫+10.2❵");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪4•7.2❫+❪x_0◦x_3❫+❪5•x_1❫+10.2❵");
}

TEST( ModifyRemoveConstZerosFromSum, BigExample2) {
    auto expression = sa::SumExpression::make((4 * 7.2_const), (0_var * 3_var), 0.0_const, (5 * 1_var), 10.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4•7.2❫+❪x_0◦x_3❫+0+❪5•x_1❫+10.2❵");
    const auto modification_result =  modify_remove_const_zeros_from_sum(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪4•7.2❫+❪x_0◦x_3❫+❪5•x_1❫+10.2❵");
}
