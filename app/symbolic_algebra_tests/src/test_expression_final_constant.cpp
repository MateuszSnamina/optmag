// TESTED LIBRARY:
#include <symbolic_algebra/expression_final_constant.hpp>
// GTEST:
#include <gtest/gtest.h>
// BOOST:
#include <boost/range/algorithm/count.hpp>

namespace sa = symbolic_algebra;

//TEST(ExpressionBosonPrimitiveOperator, BosonCreationOperator) {
//    const auto expression = cr_d();
//    ASSERT_EQ(expression.str(), "♯d");
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
//        const auto expression1 = cr_d();
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = an_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "♯d");
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//TEST(ExpressionBosonPrimitiveOperator, BosonAnnihilationOperator) {
//    const auto expression = an_d();
//    ASSERT_EQ(expression.str(), "♭d");
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
//        const auto expression1 = an_d();
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = an_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "♭d");
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//TEST(ExpressionBosonPrimitiveOperator, BosonNumberOperator) {
//    const auto expression = n_d();
//    ASSERT_EQ(expression.str(), "ℕd");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonNumberOperator>(), true);
//    ASSERT_EQ(expression.n_subexpressions(), 0);
//    ASSERT_EQ(boost::size(expression.range()), 0);
//    ASSERT_EQ(boost::size(expression.crange()), 0);
//    const auto boson = expression.casted_target<sa::BosonPrimitiveOperators>().unwrap().get().boson();
//    ASSERT_TRUE(boson);
//    ASSERT_EQ(boson->str(), "d");
//    ASSERT_EQ(std::addressof(*boson), std::addressof(*d));
//    {
//        const auto expression1 = n_d();
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = n_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "ℕd");
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}
