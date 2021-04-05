#include<symbolic_algebra/expression_final_unary_functions.hpp>

// TESTED LIBRARY:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/expression.hpp>
#include <symbolic_algebra/calculate_expression_value.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

const char* foo1_name = "foo1";
const char* foo2_name = "foo2";
const char* foo3_name = "foo3";

double foo1_function(double x) {
    return 2.5 * x + 6.7;
}

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
    const auto expression = sa::UnaryFunctionExpression<&foo2_name, FunctionalT>::make(foo1_function, std::move(sub_expression));
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
