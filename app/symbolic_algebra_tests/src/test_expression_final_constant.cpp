// TESTED LIBRARY:
#include <symbolic_algebra/expression_final_constant.hpp>
#include <symbolic_algebra/expression_final_variable.hpp>
#include <symbolic_algebra/expression_pragma.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;

TEST(FinalExpressionConstant, ConstantExpression0) {
    const auto expression = 9.1_const;
    ASSERT_EQ(expression.str(), "9.1");
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), true);
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);
    const auto expression_casted = expression.casted_target<sa::ConstantExpression>();
    ASSERT_TRUE(expression_casted);
    const auto expression_casted_value = expression_casted.unwrap().get().value();
    ASSERT_EQ(expression_casted_value, 9.1);
    {
        const auto expression1 = 9.1_const;
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 9.0_const;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "9.1");
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

TEST(FinalExpressionConstant, ConstantExpression1) {
    const auto expression = sa::ConstantExpression::make(-9.1);
    ASSERT_EQ(expression.str(), "-9.1");
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), true);
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);
    const auto expression_casted = expression.casted_target<sa::ConstantExpression>();
    ASSERT_TRUE(expression_casted);
    const auto expression_casted_value = expression_casted.unwrap().get().value();
    ASSERT_EQ(expression_casted_value, -9.1);
    {
        const auto expression1 = sa::ConstantExpression::make(-9.1);
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "-9.1");
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}
