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

TEST(TransformFlattenProduct, OnBosonPrimitiveOperator) {
    auto expression = 9_var;
    ASSERT_EQ(expression.str(), "x_9");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "x_9");
}

TEST(TransformFlattenProduct, OnEmptyProduct) {
    auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(TransformFlattenProduct, OnProductOfBosonPrimitiveOperators) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(TransformFlattenProduct, MinimalExample1) {
    auto expression = (7_var * (0_var * 3_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_7◦❪x_0◦x_3❫❫");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_7◦x_0◦x_3❫");
}

TEST(TransformFlattenProduct, MinimalExample2) {
    auto expression = ba::ProductExpression::make(7_var, (0_var * 3_var), (10_var * 0_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_7◦❪x_0◦x_3❫◦❪x_10◦x_0❫❫");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_7◦x_0◦x_3◦x_10◦x_0❫");
}

TEST(TransformFlattenProduct, BigTest1) {
    auto expression = make_expression_1();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪x_0◦x_4◦❪2x_6❫❫◦❴x_6+x_6❵◦❪x_10◦x_11❫◦❴❴x_1+x_5❵+❴x_7+x_11❵❵❫");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4◦❪2x_6❫◦❴x_6+x_6❵◦x_10◦x_11◦❴❴x_1+x_5❵+❴x_7+x_11❵❵❫");
}

TEST(TransformFlattenProduct, BigTest2) {
    auto expression = make_expression_2();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪x_0◦x_4◦❪2x_6❫❫+❴x_6+x_6❵+❪x_10◦x_11❫+❴❴x_1+x_5❵+❴x_7+x_11❵❵❵");
    const auto modification_result = modify_flatten_product(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪x_0◦x_4◦❪2x_6❫❫+❴x_6+x_6❵+❪x_10◦x_11❫+❴❴x_1+x_5❵+❴x_7+x_11❵❵❵");
}
