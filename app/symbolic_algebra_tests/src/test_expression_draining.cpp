// TESTED LIBRARY:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::operators;

TEST(Draining, Test0) {
    auto expression = sa::ProductExpression::make(0_var, 1_var, 2_var);
    ASSERT_EQ(expression.str(), "❪x_0◦x_1◦x_2❫");

    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    auto& expression_ref = expression.subexpression(1);

    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    sa::ExpressionHandler expression1{std::move(expression_ref)};

    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    expression1 = std::move(expression.subexpression(0));

    ASSERT_EQ(expression.n_subexpressions(), 3);
    ASSERT_TRUE(expression.subexpression(0).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    swap(expression.subexpression(1), expression.subexpression(2));

    ASSERT_EQ(expression.n_subexpressions(), 3);
    ASSERT_TRUE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(2).is_shallow_drained());
}

TEST(Draining, Test1) {
    auto expression = sa::SumExpression::make(0_var, 1_var, 2_var);
    ASSERT_EQ(expression.str(), "❴x_0+x_1+x_2❵");

    ASSERT_EQ(expression.n_subexpressions(), 3);
    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    bool blinking_flag = true;
    for (auto& _ : expression.range()) {
        if (blinking_flag) {
            sa::ExpressionHandler new_expr{std::move(_)};
        }
        blinking_flag = !blinking_flag;
    }
    ASSERT_EQ(expression.n_subexpressions(), 3);
    ASSERT_TRUE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(2).is_shallow_drained());
}

TEST(Draining, Test3) {
    auto expression = (0_var * (1_var + 2_var));
    ASSERT_EQ(expression.str(), "❪x_0◦❴x_1+x_2❵❫");

    ASSERT_EQ(expression.n_subexpressions(), 2);
    ASSERT_EQ(expression.subexpression(0).n_subexpressions(), 0);
    ASSERT_EQ(expression.subexpression(1).n_subexpressions(), 2);
    ASSERT_EQ(expression.subexpression(1).subexpression(0).n_subexpressions(), 0);
    ASSERT_EQ(expression.subexpression(1).subexpression(1).n_subexpressions(), 0);
    ASSERT_FALSE(expression.is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).subexpression(1).is_shallow_drained());

    ASSERT_FALSE(expression.is_deep_drained());
    ASSERT_FALSE(expression.subexpression(0).is_deep_drained());
    ASSERT_FALSE(expression.subexpression(1).is_deep_drained());
    ASSERT_FALSE(expression.subexpression(1).subexpression(0).is_deep_drained());
    ASSERT_FALSE(expression.subexpression(1).subexpression(1).is_deep_drained());

    sa::ExpressionHandler new_expr{std::move(expression.subexpression(1).subexpression(0))};

    ASSERT_FALSE(expression.is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(1).subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).subexpression(1).is_shallow_drained());

    ASSERT_TRUE(expression.is_deep_drained());
    ASSERT_FALSE(expression.subexpression(0).is_deep_drained());
    ASSERT_TRUE(expression.subexpression(1).is_deep_drained());
    ASSERT_TRUE(expression.subexpression(1).subexpression(0).is_deep_drained());
    ASSERT_FALSE(expression.subexpression(1).subexpression(1).is_deep_drained());
}
