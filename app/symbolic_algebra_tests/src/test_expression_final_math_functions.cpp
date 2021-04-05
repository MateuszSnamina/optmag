// TESTED LIBRARY:
#include <symbolic_algebra/expression_final_math_functions.hpp>
#include <symbolic_algebra/expression_pragma.hpp>

// GTEST:
#include <gtest/gtest.h>
// BOOST:
#include <boost/range/algorithm/count.hpp>

namespace sa = symbolic_algebra;
using namespace sa::literals;

//TODO: everything
//TODO: the same for VariableExpression

TEST(FinalExpressionSin, ConstantExpression) {
//    const auto expression = 9.1_const;
//    ASSERT_EQ(expression.str(), "9.1");
//    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), true);
//    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
//    ASSERT_EQ(expression.n_subexpressions(), 0);
//    ASSERT_EQ(boost::size(expression.range()), 0);
//    ASSERT_EQ(boost::size(expression.crange()), 0);
//    const auto expression_casted_value = expression.casted_target<sa::ConstantExpression>().unwrap().get().value();
//    ASSERT_EQ(expression_casted_value, 9.1);
//    {
//        const auto expression1 = 9.1_const;
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = 0_var;
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "9.1");
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
}
