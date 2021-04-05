#include<symbolic_algebra/expression_final_unary_functions.hpp>

// TESTED LIBRARY:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/expression.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace {

double foo1_function(double x) {
    return 2.5 * x + 6.7;
}

}

const char* foo1_name = "foo1";
const char* foo2_name = "foo2";
const char* foo3_name = "foo3";
const char* foo4_name = "foo4";

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(ExpressionUnaryFunction, WithFunctionPointer) {
    auto sub_expression = 9.1_const;
    using FunctionPtrT = double(*)(double);
    const auto expression = sa::UnaryFunctionExpression<&foo1_name, FunctionPtrT>::make(foo1_function, std::move(sub_expression));
    ASSERT_EQ(expression.str(), "foo1⦗9.1⦘");
}

TEST(ExpressionUnaryFunction, WithFunctional) {
    auto sub_expression = 9.1_const;
    using FunctionalT = std::function<double(double)>;
    const FunctionalT foo2_functional = [](double x){return 2.5 * x + 6.7;};
    const auto expression = sa::UnaryFunctionExpression<&foo2_name, FunctionalT>::make(foo2_functional, std::move(sub_expression));
    ASSERT_EQ(expression.str(), "foo2⦗9.1⦘");
}

TEST(ExpressionUnaryFunction, WithCustomFunctor) {
    auto sub_expression = 9.1_const;
    struct CustomFunctorT {
        double operator()(double x){
            return 2.5 * x + 6.7;
        }
    } foo3_custom_functor;
    const auto expression = sa::UnaryFunctionExpression<&foo3_name, CustomFunctorT>::make(foo3_custom_functor, std::move(sub_expression));
    ASSERT_EQ(expression.str(), "foo3⦗9.1⦘");
}

TEST(ExpressionUnaryFunction, WithLambda) {
    auto sub_expression = 9.1_const;
    const auto foo4_lambda = [](double x){return 2.5 * x + 6.7;};
    using LambdaT = decltype(foo4_lambda);
    const auto expression = sa::UnaryFunctionExpression<&foo4_name, LambdaT>::make(foo4_lambda, std::move(sub_expression));
    ASSERT_EQ(expression.str(), "foo4⦗9.1⦘");
}

TEST(UnaryFunctionStaticExpression, WithFunctionPointer) {
    auto sub_expression = 9.1_const;
    using FunctionPtrT = double(*)(double);
    const auto expression = sa::UnaryFunctionStaticExpression<&foo1_name, FunctionPtrT, foo1_function>::make(std::move(sub_expression));
    ASSERT_EQ(expression.str(), "foo1⦗9.1⦘");
}

//TEST(UnaryFunctionStaticExpression, WithFunctional) {
//    // C++20 ??
//    auto sub_expression = 9.1_const;
//    using FunctionalT = std::function<double(double)>;
//    constexpr FunctionalT foo2_functional = [](double x){return 2.5 * x + 6.7;};
//    //const auto expression = sa::UnaryFunctionStaticExpression<&foo2_name, FunctionalT, foo1_function>::make(std::move(sub_expression));
//    //ASSERT_EQ(expression.str(), "foo2⦗9.1⦘");
//}

//TEST(UnaryFunctionStaticExpression, WithCustomFunctor) {
//    // C++20 ??
//    auto sub_expression = 9.1_const;
//    struct CustomFunctorT {
//        double operator()(double x) {
//            return 2.5 * x + 6.7;
//        }
//    } foo3_custom_functor;
//    const auto expression = sa::UnaryFunctionStaticExpression<&foo3_name, CustomFunctorT, foo3_custom_functor>::make(std::move(sub_expression));
//    ASSERT_EQ(expression.str(), "foo3⦗9.1⦘");
//}
