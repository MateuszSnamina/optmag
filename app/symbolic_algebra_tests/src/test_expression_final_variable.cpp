// TESTED LIBRARY:
#include <symbolic_algebra/expression_final_variable.hpp>
#include <symbolic_algebra/expression_final_constant.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;

TEST(FinalExpressionVariable, VariableExpression0) {
    const auto expression = 9_var;
    ASSERT_EQ(expression.str(), "x_9");
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), true);
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);
    const auto expression_casted = expression.casted_target<sa::VariableExpression>();
    ASSERT_TRUE(expression_casted);
    const auto expression_casted_index = expression_casted.unwrap().get().index();
    ASSERT_EQ(expression_casted_index, 9);
    {
        const auto expression1 = 9_var;
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 8_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }    {
        const auto expression1 = 9.0_const;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "x_9");
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}
