// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_flatten_product.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = symbolic_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifyFlattenProduct, OnCost) {
    auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "9.1");
}

TEST(ModifyFlattenProduct, OnEmptyProduct) {
    auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyFlattenProduct, OnProductOfVars) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifyFlattenProduct, MinimalExample1) {
    auto expression = (7.2_const * (0_var * 3_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪7.2◦❪x_0◦x_3❫❫");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪7.2◦x_0◦x_3❫");
}

TEST(ModifyFlattenProduct, MinimalExample2) {
    auto expression = ba::ProductExpression::make(7.2_const, (0_var * 3_var), (10.2_const * 0_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪7.2◦❪x_0◦x_3❫◦❪10.2◦x_0❫❫");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪7.2◦x_0◦x_3◦10.2◦x_0❫");
}

TEST(ModifyFlattenProduct, BigTest1) {
    auto expression = make_expression_1();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪x_0◦x_4◦❪2•6.1❫❫◦❴6.1+6.1❵◦❪10.2◦11.3❫◦❴❴x_1+x_5❵+❴7.2+11.3❵❵❫");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4◦❪2•6.1❫◦❴6.1+6.1❵◦10.2◦11.3◦❴❴x_1+x_5❵+❴7.2+11.3❵❵❫");
}

TEST(ModifyFlattenProduct, BigTest2) {
    auto expression = make_expression_2();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪x_0◦x_4◦❪2•6.1❫❫+❴6.1+6.1❵+❪10.2◦11.3❫+❴❴x_1+x_5❵+❴7.2+11.3❵❵❵");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪x_0◦x_4◦❪2•6.1❫❫+❴6.1+6.1❵+❪10.2◦11.3❫+❴❴x_1+x_5❵+❴7.2+11.3❵❵❵");
}
