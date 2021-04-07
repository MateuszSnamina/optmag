// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_remove_const_ones_from_product.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyRemoveConstOneFromProduct, OnConst) {
    auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "9.1");
}

TEST(ModifyRemoveConstOneFromProduct, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyRemoveConstOneFromProduct, OnEmptySum) {
    auto expression = sa::SumExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝟘");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyRemoveConstOneFromProduct, OnProductOfVars) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifyRemoveConstOneFromProduct, OnSumOfVars) {
    auto expression = (0_var + 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴x_0+x_4❵");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴x_0+x_4❵");
}

TEST(ModifyRemoveConstOneFromProduct, MinimalWorkingExample1) {
    auto expression = (0_var + 1.0_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴x_0+1❵");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴x_0+1❵");
}

TEST(ModifyRemoveConstOneFromProduct, MinimalWorkingExample2) {
    auto expression = sa::SumExpression::make(0_var, 1.0_const, 1.1_const, 1.0_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴x_0+1+1.1+1❵");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴x_0+1+1.1+1❵");
}

TEST(ModifyRemoveConstOneFromProduct, MinimalWorkingExample3) {
    auto expression = (0_var * 1.0_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦1❫");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0❫");
}

TEST(ModifyRemoveConstOneFromProduct, MinimalWorkingExample4) {
    auto expression = sa::ProductExpression::make(0_var, 1.0_const, 1.1_const, 1.0_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦1◦1.1◦1❫");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦1.1❫");
}

TEST(ModifyRemoveConstOneFromProduct, BigExample1) {
    auto expression = sa::SumExpression::make((4 * 7.2_const), (0_var * 3_var), (5 * 1_var), 10.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4•7.2❫+❪x_0◦x_3❫+❪5•x_1❫+10.2❵");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪4•7.2❫+❪x_0◦x_3❫+❪5•x_1❫+10.2❵");
}

TEST(ModifyRemoveConstOneFromProduct, BigExample2) {
    auto expression = sa::SumExpression::make((4 * 7.2_const), (0_var * 3_var), 0.0_const, (5 * 1_var), 10.2_const);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4•7.2❫+❪x_0◦x_3❫+0+❪5•x_1❫+10.2❵");
    const auto modification_result =  modify_remove_const_ones_from_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪4•7.2❫+❪x_0◦x_3❫+0+❪5•x_1❫+10.2❵");
}
