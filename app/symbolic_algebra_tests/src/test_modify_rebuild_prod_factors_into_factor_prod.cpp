// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_rebuild_prod_factors_into_factor_prod.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ModifyRebuildProdFactorsIntoFactorProd, OnBosonPrimitiveOperator) {
    auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyRebuildProdFactorsIntoFactorProd, OnEmptyProduct) {
    auto expression = sa::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyRebuildProdFactorsIntoFactorProd, OnProductOfBosonPrimitiveOperators) {
    auto expression = (0_var * 4_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪x_0◦x_4❫");
    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyRebuildProdFactorsIntoFactorProd, MinimalExample1) {
    auto expression = sa::ProductExpression::make(4 * 3_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪4•x_3❫❫");
    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪4•❪x_3❫❫");
}

TEST(ModifyRebuildProdFactorsIntoFactorProd, MinimalExample2) {
    auto expression = sa::ProductExpression::make((0_var * 3_var), 5 * 7.2_const, (10.2_const * 0_var));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪x_0◦x_3❫◦❪5•7.2❫◦❪10.2◦x_0❫❫");
    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪5•❪❪x_0◦x_3❫◦7.2◦❪10.2◦x_0❫❫❫");
}

TEST(ModifyRebuildProdFactorsIntoFactorProd, MinimalExample3) {
    auto expression = sa::ProductExpression::make((0_var * 3_var), 5 * 7.2_const, (10.2_const * 0_var), -1 * 9.1_const, 7 * 0_var);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪x_0◦x_3❫◦❪5•7.2❫◦❪10.2◦x_0❫◦❪-9.1❫◦❪7•x_0❫❫");
    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪-35•❪❪x_0◦x_3❫◦7.2◦❪10.2◦x_0❫◦9.1◦x_0❫❫");
}
