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

//TEST(TransformFlattenProduct, OnBosonPrimitiveOperator) {
//    auto expression = 'd'_cr;
//    ASSERT_EQ(expression.str(), "♯d");
//    //std::cout << expression.str() << std::endl;
//    const auto modification_result = modify_flatten_product(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "♯d");
//}

//TEST(TransformFlattenProduct, OnEmptyProduct) {
//    auto expression = ba::ProductExpression::make();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "𝕀");
//    const auto modification_result = modify_flatten_product(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "𝕀");
//}

//TEST(TransformFlattenProduct, OnProductOfBosonPrimitiveOperators) {
//    auto expression = ('a'_cr * 'b'_an);
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
//    const auto modification_result = modify_flatten_product(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
//}

//TEST(TransformFlattenProduct, MinimalExample1) {
//    auto expression = ('c'_an * ('a'_cr * 'b'_cr));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♭c◦❪♯a◦♯b❫❫");
//    const auto modification_result = modify_flatten_product(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♭c◦♯a◦♯b❫");
//}

//TEST(TransformFlattenProduct, MinimalExample2) {
//    auto expression = ba::ProductExpression::make('c'_an, ('a'_cr * 'b'_cr), ('d'_an * 'a'_cr));
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪♭c◦❪♯a◦♯b❫◦❪♭d◦♯a❫❫");
//    const auto modification_result = modify_flatten_product(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♭c◦♯a◦♯b◦♭d◦♯a❫");
//}

//TEST(TransformFlattenProduct, BigTest1) {
//    auto expression = make_expression_1();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❪❪♯a◦♭b◦❪2♯c❫❫◦❴♯c+♯c❵◦❪♭d◦ℕd❫◦❴❴♭a+ℕb❵+❴♭c+ℕd❵❵❫");
//    const auto modification_result = modify_flatten_product(std::move(expression));
//    ASSERT_TRUE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b◦❪2♯c❫◦❴♯c+♯c❵◦♭d◦ℕd◦❴❴♭a+ℕb❵+❴♭c+ℕd❵❵❫");
//}

//TEST(TransformFlattenProduct, BigTest2) {
//    auto expression = make_expression_2();
//    //std::cout << expression.str() << std::endl;
//    ASSERT_EQ(expression.str(), "❴❪♯a◦♭b◦❪2♯c❫❫+❴♯c+♯c❵+❪♭d◦ℕd❫+❴❴♭a+ℕb❵+❴♭c+ℕd❵❵❵");
//    const auto modification_result = modify_flatten_product(std::move(expression));
//    ASSERT_FALSE(modification_result);
//    const auto& modified_expression = *modification_result;
//    //std::cout << modified_expression.str() << std::endl;
//    ASSERT_EQ(modified_expression.str(), "❴❪♯a◦♭b◦❪2♯c❫❫+❴♯c+♯c❵+❪♭d◦ℕd❫+❴❴♭a+ℕb❵+❴♭c+ℕd❵❵❵");
//}
