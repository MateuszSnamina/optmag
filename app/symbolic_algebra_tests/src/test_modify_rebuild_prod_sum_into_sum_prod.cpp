// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/modify_rebuild_prod_sum_into_sum_prod.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

//TEST(ModifyRebuildProdSumIntoSumProd, OnBosonPrimitiveOperator) {
//    auto expression = 'd'_cr;
//    ASSERT_EQ(expression.str(), "♯d");
//    //std::cout << expression.str() << std::endl;
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "♯d");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, OnEmptyProduct) {
//    auto expression = sa::ProductExpression::make();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "𝕀");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝕀");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, OnProductOfBosonPrimitiveOperators) {
//    auto expression = ('a'_cr * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample1) {
//    auto expression = sa::ProductExpression::make('a'_cr, ('b'_an + 'c'_cr), 'd'_cr);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦❴♭b+♯c❵◦♯d❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪♯a◦♭b◦♯d❫+❪♯a◦♯c◦♯d❫❵");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample2) {
//    auto expression = ('a'_cr * ('b'_an + 'c'_cr));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦❴♭b+♯c❵❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪♯a◦♭b❫+❪♯a◦♯c❫❵");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample3) {
//    auto expression = (('b'_an + 'c'_cr) * 'd'_cr);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪❴♭b+♯c❵◦♯d❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪♭b◦♯d❫+❪♯c◦♯d❫❵");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample4) {
//    auto expression = sa::ProductExpression::make(('b'_an + 'c'_cr));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪❴♭b+♯c❵❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪❴♭b+♯c❵❫");
//    // TODO: consider changing the desired behavior so to get the following:
//    // const auto& modified_expression = *modification_result;
//    // //std::cout << modified_expression.str() << std::endl;
//    // ASSERT_EQ(modified_expression.str(), "❴❪♭b❫+❪♯c❫❵");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample5) {
//    auto expression = sa::ProductExpression::make(sa::SumExpression::make_zero());
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪𝟘❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪𝟘❫");
//    // TODO: consider changing the desired behavior so to get the following:
//    // const auto& modified_expression = *modification_result;
//    // //std::cout << modified_expression.str() << std::endl;
//    // ASSERT_EQ(modified_expression.str(), "𝟘");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample6) {
//    auto expression = (('b'_an + 'c'_cr) * (2 * 'd'_cr));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪❴♭b+♯c❵◦❪2♯d❫❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪♭b◦❪2♯d❫❫+❪♯c◦❪2♯d❫❫❵");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample7) {
//    auto expression = sa::ProductExpression::make('a'_cr, ('b'_an * 'c'_cr), 'd'_cr);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦❪♭b◦♯c❫◦♯d❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♯a◦❪♭b◦♯c❫◦♯d❫");
//}

//TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample8) {
//    auto expression = (sa::SumExpression::make_zero() * 'd'_cr);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪𝟘◦♯d❫");
//    const auto modification_result = modify_rebuild_prod_sum_into_sum_prod(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝟘");
//}
