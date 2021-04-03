// TESTED LIBRARY:
#include <symbolic_algebra/expression_final_constant.hpp>
#include <symbolic_algebra/expression_pragma.hpp>

// GTEST:
#include <gtest/gtest.h>
// BOOST:
#include <boost/range/algorithm/count.hpp>

namespace sa = symbolic_algebra;
using namespace sa::literals;

//TEST(ExpressionBosonPrimitiveOperator, BosonCreationOperator) {
//    const auto expression = 9.1_const;
//    ASSERT_EQ(expression.str(), "9.1");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), true);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonNumberOperator>(), false);
//    ASSERT_EQ(expression.n_subexpressions(), 0);
//    ASSERT_EQ(boost::size(expression.range()), 0);
//    ASSERT_EQ(boost::size(expression.crange()), 0);
//    const auto boson = expression.casted_target<sa::BosonPrimitiveOperators>().unwrap().get().boson();
//    ASSERT_TRUE(boson);
//    ASSERT_EQ(boson->str(), "d");
//    ASSERT_EQ(std::addressof(*boson), std::addressof(*d));
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
//        const auto expression1 = 1_var;
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "9.1");
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//TEST(ExpressionBosonPrimitiveOperator, BosonAnnihilationOperator) {
//    const auto expression = 10.2_const;
//    ASSERT_EQ(expression.str(), "10.2");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), true);
//    ASSERT_EQ(expression.is_of_type<sa::BosonNumberOperator>(), false);
//    ASSERT_EQ(expression.n_subexpressions(), 0);
//    ASSERT_EQ(boost::size(expression.range()), 0);
//    ASSERT_EQ(boost::size(expression.crange()), 0);
//    const auto boson = expression.casted_target<sa::BosonPrimitiveOperators>().unwrap().get().boson();
//    ASSERT_TRUE(boson);
//    ASSERT_EQ(boson->str(), "d");
//    ASSERT_EQ(std::addressof(*boson), std::addressof(*d));
//    {
//        const auto expression1 = 10.2_const;
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = 1_var;
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = 0_var;
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "10.2");
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}
