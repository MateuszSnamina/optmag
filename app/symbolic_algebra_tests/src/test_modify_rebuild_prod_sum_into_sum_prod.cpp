// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_rebuild_prod_sum_into_sum_prod.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyRebuildProdSumIntoSumProd, OnBosonPrimitiveOperator) {
    auto expression = 9_var;
    ASSERT_EQ(expression.str(), "x_9");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "x_9");
}

TEST(ModifyRebuildProdSumIntoSumProd, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyRebuildProdSumIntoSumProd, OnProductOfBosonPrimitiveOperators) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦x_4❫");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample1) {
    auto expression = sa::ProductExpression::make(0_var, (4_var + 6_var), 9_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦❴x_4+x_6❵◦x_9❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪x_0◦x_4◦x_9❫+❪x_0◦x_6◦x_9❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample2) {
    auto expression = (0_var * (4_var + 6_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦❴x_4+x_6❵❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪x_0◦x_4❫+❪x_0◦x_6❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample3) {
    auto expression = ((4_var + 6_var) * 9_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴x_4+x_6❵◦x_9❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪x_4◦x_9❫+❪x_6◦x_9❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample4) {
    auto expression = sa::ProductExpression::make((4_var + 6_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴x_4+x_6❵❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪❴x_4+x_6❵❫");
    // TODO: consider changing the desired behavior so to get the following:
    // const auto& modified_expression = *modification_result;
    // //std::cout << modified_expression.str() << std::endl;
    // ASSERT_EQ(modified_expression.str(), "❴❪x_4❫+❪x_6❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample5) {
    auto expression = sa::ProductExpression::make(sa::SumExpression::make_zero());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪𝟘❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪𝟘❫");
    // TODO: consider changing the desired behavior so to get the following:
    // const auto& modified_expression = *modification_result;
    // //std::cout << modified_expression.str() << std::endl;
    // ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample6) {
    auto expression = ((4_var + 6_var) * (2 * 9_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴x_4+x_6❵◦❪2x_9❫❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪x_4◦❪2x_9❫❫+❪x_6◦❪2x_9❫❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample7) {
    auto expression = sa::ProductExpression::make(0_var, (4_var * 6_var), 9_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦❪x_4◦x_6❫◦x_9❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪x_0◦❪x_4◦x_6❫◦x_9❫");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample8) {
    auto expression = (sa::SumExpression::make_zero() * 9_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪𝟘◦x_9❫");
    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}
