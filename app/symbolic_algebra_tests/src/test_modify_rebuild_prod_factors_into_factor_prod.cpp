// SELF:
#include <symbolic_algebra_tests/example_expressions.hpp-OLD>
// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_rebuild_prod_factors_into_factor_prod.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

//TEST(ModifyRebuildProdFactorsIntoFactorProd, OnBosonPrimitiveOperator) {
//    auto expression = 'd'_cr;
//    ASSERT_EQ(expression.str(), "♯d");
//    //std::cout << expression.str() << std::endl;
//    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//}

//TEST(ModifyRebuildProdFactorsIntoFactorProd, OnEmptyProduct) {
//    auto expression = sa::ProductExpression::make();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "𝕀");
//    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//}

//TEST(ModifyRebuildProdFactorsIntoFactorProd, OnProductOfBosonPrimitiveOperators) {
//    auto expression = ('a'_cr * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
//    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//}

//TEST(ModifyRebuildProdFactorsIntoFactorProd, MinimalExample1) {
//    auto expression = sa::ProductExpression::make(4 * 'b'_cr);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪❪4♯b❫❫");
//    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪4❪♯b❫❫");
//}

//TEST(ModifyRebuildProdFactorsIntoFactorProd, MinimalExample2) {
//    auto expression = sa::ProductExpression::make(('a'_cr * 'b'_cr), 5 * 'c'_an, ('d'_an * 'a'_cr));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪❪♯a◦♯b❫◦❪5♭c❫◦❪♭d◦♯a❫❫");
//    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪5❪❪♯a◦♯b❫◦♭c◦❪♭d◦♯a❫❫❫");
//}

//TEST(ModifyRebuildProdFactorsIntoFactorProd, MinimalExample3) {
//    auto expression = sa::ProductExpression::make(('a'_cr * 'b'_cr), 5 * 'c'_an, ('d'_an * 'a'_cr), -1 * 'd'_cr, 7 * 'a'_cr);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪❪♯a◦♯b❫◦❪5♭c❫◦❪♭d◦♯a❫◦❪-♯d❫◦❪7♯a❫❫");
//    const auto modification_result = modify_rebuild_prod_factors_into_factor_prod(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪-35❪❪♯a◦♯b❫◦♭c◦❪♭d◦♯a❫◦♯d◦♯a❫❫");
//}
