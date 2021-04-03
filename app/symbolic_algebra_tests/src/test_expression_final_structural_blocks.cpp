// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
// GTEST:
#include <gtest/gtest.h>
// BOOST
#include <boost/range/algorithm/count.hpp>

namespace sa = symbolic_algebra;
using namespace sa::literals;

// **********************************************************
// ***  RealFactoredExpression                            ***
// **********************************************************

TEST(ExpressionStructuralBlocks, RealFactoredExpression) {
    const auto expression = sa::RealFactoredExpression::make(-5, 3_var);
    ASSERT_EQ(expression.str(), "❪-5•x_3❫");
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::RealFactoredExpression>(), true);
    ASSERT_EQ(expression.n_subexpressions(), 1);
    ASSERT_EQ(boost::size(expression.range()), 1);
    ASSERT_EQ(boost::size(expression.crange()), 1);
    ASSERT_EQ(expression.casted_target<sa::RealFactoredExpression>().unwrap().get().factor(), -5);
    {
        ASSERT_EQ(expression.subexpression(0).str(), "x_3");
    }
    {
        ASSERT_EQ(expression.range()[0].str(), "x_3");
    }
    {
        const auto expression1 = sa::RealFactoredExpression::make(-5, 3_var);
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make(3_var, 3_var);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make(3_var);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "❪-5•x_3❫");
        ASSERT_TRUE(expression1.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

// **********************************************************
// ***  ProdExpression                                    ***
// **********************************************************

TEST(ExpressionStructuralBlocks, EmptyProcut) {
    const auto expression = sa::ProductExpression::make();
    ASSERT_EQ(expression.str(), "𝕀");
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), true);
    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);
    ASSERT_TRUE(expression.casted_target<sa::ProductExpression>().unwrap().get().is_identity());
    {
        const auto expression1 = sa::ProductExpression::make();
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make_identity();
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make(10.2_const);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "𝕀");
        ASSERT_TRUE(expression1.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

TEST(ExpressionStructuralBlocks, SingleChildProcut) {
    const auto expression = sa::ProductExpression::make(3_var);
    ASSERT_EQ(expression.str(), "❪x_3❫");
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), true);
    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 1);
    ASSERT_EQ(boost::size(expression.range()), 1);
    ASSERT_EQ(boost::size(expression.crange()), 1);
    ASSERT_FALSE(expression.casted_target<sa::ProductExpression>().unwrap().get().is_identity());
    {
        ASSERT_EQ(expression.subexpression(0).str(), "x_3");
    }
    {
        ASSERT_EQ(expression.range()[0].str(), "x_3");
    }
    {
        const auto expression1 = sa::ProductExpression::make(3_var);
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make(3_var, 3_var);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make(3_var);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "❪x_3❫");
        ASSERT_TRUE(expression1.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

TEST(ExpressionStructuralBlocks, ThreeChildrenProcut) {
    const auto expression = sa::ProductExpression::make(3_var, 0_var, 10.2_const);
    ASSERT_EQ(expression.str(), "❪x_3◦x_0◦10.2❫");
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), true);
    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 3);
    ASSERT_EQ(boost::size(expression.range()), 3);
    ASSERT_EQ(boost::size(expression.crange()), 3);
    ASSERT_FALSE(expression.casted_target<sa::ProductExpression>().unwrap().get().is_identity());
    {
        ASSERT_EQ(expression.subexpression(0).str(), "x_3");
        ASSERT_EQ(expression.subexpression(1).str(), "x_0");
        ASSERT_EQ(expression.subexpression(2).str(), "10.2");
    }
    {
        ASSERT_EQ(expression.range()[0].str(), "x_3");
        ASSERT_EQ(expression.range()[1].str(), "x_0");
        ASSERT_EQ(expression.range()[2].str(), "10.2");
    }
    {
        const auto expression1 = sa::ProductExpression::make(3_var, 0_var, 10.2_const);
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make(3_var, 3_var);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make(3_var, 0_var, 10.2_const);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "❪x_3◦x_0◦10.2❫");
        ASSERT_TRUE(expression1.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

// **********************************************************
// ***  SumExpression                                     ***
// **********************************************************

TEST(ExpressionStructuralBlocks, EmptySum) {
    const auto expression = sa::SumExpression::make();
    ASSERT_EQ(expression.str(), "𝟘");
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), true);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);
    ASSERT_TRUE(expression.casted_target<sa::SumExpression>().unwrap().get().is_zero());
    {
        const auto expression1 = sa::SumExpression::make();
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make_zero();
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make(10.2_const);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "𝟘");
        ASSERT_TRUE(expression1.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

TEST(ExpressionStructuralBlocks, SingleChildSum) {
    const auto expression = sa::SumExpression::make(3_var);
    ASSERT_EQ(expression.str(), "❴x_3❵");
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), true);
    ASSERT_EQ(expression.n_subexpressions(), 1);
    ASSERT_EQ(boost::size(expression.range()), 1);
    ASSERT_EQ(boost::size(expression.crange()), 1);
    ASSERT_FALSE(expression.casted_target<sa::SumExpression>().unwrap().get().is_zero());
    {
        ASSERT_EQ(expression.subexpression(0).str(), "x_3");
    }
    {
        ASSERT_EQ(expression.range()[0].str(), "x_3");
    }
    {
        const auto expression1 = sa::SumExpression::make(3_var);
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make(3_var, 3_var);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make(3_var);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "❴x_3❵");
        ASSERT_TRUE(expression1.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

TEST(ExpressionStructuralBlocks, ThreeChildrenSum) {
    const auto expression = sa::SumExpression::make(3_var, 0_var, 10.2_const);
    ASSERT_EQ(expression.str(), "❴x_3+x_0+10.2❵");
    ASSERT_EQ(expression.is_of_type<sa::VariableExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ConstantExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), false);
    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), true);
    ASSERT_EQ(expression.n_subexpressions(), 3);
    ASSERT_EQ(boost::size(expression.range()), 3);
    ASSERT_EQ(boost::size(expression.crange()), 3);
    ASSERT_FALSE(expression.casted_target<sa::SumExpression>().unwrap().get().is_zero());
    {
        ASSERT_EQ(expression.subexpression(0).str(), "x_3");
        ASSERT_EQ(expression.subexpression(1).str(), "x_0");
        ASSERT_EQ(expression.subexpression(2).str(), "10.2");
    }
    {
        ASSERT_EQ(expression.range()[0].str(), "x_3");
        ASSERT_EQ(expression.range()[1].str(), "x_0");
        ASSERT_EQ(expression.range()[2].str(), "10.2");
    }
    {
        const auto expression1 = sa::SumExpression::make(3_var, 0_var, 10.2_const);
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::SumExpression::make(3_var, 3_var);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = 0_var;
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = sa::ProductExpression::make(3_var, 0_var, 10.2_const);
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "❴x_3+x_0+10.2❵");
        ASSERT_TRUE(expression1.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}
