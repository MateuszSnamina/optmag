// TESTED LIBRARY:
#include <symbolic_algebra/expression.hpp>
// GTEST:
#include <gtest/gtest.h>
// BOOST
#include <boost/range/algorithm/count.hpp>

namespace sa = symbolic_algebra;

// **********************************************************
// ***  IntegerFactoredExpression                         ***
// **********************************************************

//TEST(ExpressionStructuralBlocks, IntegerFactored) {
//    const auto expression = sa::IntegerFactoredExpression::make(-5, cr_b());
//    ASSERT_EQ(expression.str(), "❪-5♯b❫");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::IntegerFactoredExpression>(), true);
//    ASSERT_EQ(expression.n_subexpressions(), 1);
//    ASSERT_EQ(boost::size(expression.range()), 1);
//    ASSERT_EQ(boost::size(expression.crange()), 1);
//    ASSERT_EQ(expression.casted_target<sa::IntegerFactoredExpression>().unwrap().get().factor(), -5);
//    {
//        ASSERT_EQ(expression.subexpression(0).str(), "♯b");
//    }
//    {
//        ASSERT_EQ(expression.range()[0].str(), "♯b");
//    }
//    {
//        const auto expression1 = sa::IntegerFactoredExpression::make(-5, cr_b());
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make(cr_b(), cr_b());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make(cr_b());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "❪-5♯b❫");
//        ASSERT_TRUE(expression1.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//// **********************************************************
//// ***  ProdExpression                                    ***
//// **********************************************************

//TEST(ExpressionStructuralBlocks, EmptyProcut) {
//    const auto expression = sa::ProductExpression::make();
//    ASSERT_EQ(expression.str(), "𝕀");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), true);
//    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), false);
//    ASSERT_EQ(expression.n_subexpressions(), 0);
//    ASSERT_EQ(boost::size(expression.range()), 0);
//    ASSERT_EQ(boost::size(expression.crange()), 0);
//    ASSERT_TRUE(expression.casted_target<sa::ProductExpression>().unwrap().get().is_identity());
//    {
//        const auto expression1 = sa::ProductExpression::make();
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make_identity();
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make(an_d());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "𝕀");
//        ASSERT_TRUE(expression1.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//TEST(ExpressionStructuralBlocks, SingleChildProcut) {
//    const auto expression = sa::ProductExpression::make(cr_b());
//    ASSERT_EQ(expression.str(), "❪♯b❫");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), true);
//    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), false);
//    ASSERT_EQ(expression.n_subexpressions(), 1);
//    ASSERT_EQ(boost::size(expression.range()), 1);
//    ASSERT_EQ(boost::size(expression.crange()), 1);
//    ASSERT_FALSE(expression.casted_target<sa::ProductExpression>().unwrap().get().is_identity());
//    {
//        ASSERT_EQ(expression.subexpression(0).str(), "♯b");
//    }
//    {
//        ASSERT_EQ(expression.range()[0].str(), "♯b");
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make(cr_b());
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make(cr_b(), cr_b());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make(cr_b());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "❪♯b❫");
//        ASSERT_TRUE(expression1.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//TEST(ExpressionStructuralBlocks, ThreeChildrenProcut) {
//    const auto expression = sa::ProductExpression::make(cr_b(), cr_a(), an_d());
//    ASSERT_EQ(expression.str(), "❪♯b◦♯a◦♭d❫");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), true);
//    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), false);
//    ASSERT_EQ(expression.n_subexpressions(), 3);
//    ASSERT_EQ(boost::size(expression.range()), 3);
//    ASSERT_EQ(boost::size(expression.crange()), 3);
//    ASSERT_FALSE(expression.casted_target<sa::ProductExpression>().unwrap().get().is_identity());
//    {
//        ASSERT_EQ(expression.subexpression(0).str(), "♯b");
//        ASSERT_EQ(expression.subexpression(1).str(), "♯a");
//        ASSERT_EQ(expression.subexpression(2).str(), "♭d");
//    }
//    {
//        ASSERT_EQ(expression.range()[0].str(), "♯b");
//        ASSERT_EQ(expression.range()[1].str(), "♯a");
//        ASSERT_EQ(expression.range()[2].str(), "♭d");
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make(cr_b(), cr_a(), an_d());
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make(cr_b(), cr_b());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make(cr_b(), cr_a(), an_d());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "❪♯b◦♯a◦♭d❫");
//        ASSERT_TRUE(expression1.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//// **********************************************************
//// ***  SumExpression                                     ***
//// **********************************************************

//TEST(ExpressionStructuralBlocks, EmptySum) {
//    const auto expression = sa::SumExpression::make();
//    ASSERT_EQ(expression.str(), "𝟘");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), true);
//    ASSERT_EQ(expression.n_subexpressions(), 0);
//    ASSERT_EQ(boost::size(expression.range()), 0);
//    ASSERT_EQ(boost::size(expression.crange()), 0);
//    ASSERT_TRUE(expression.casted_target<sa::SumExpression>().unwrap().get().is_zero());
//    {
//        const auto expression1 = sa::SumExpression::make();
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make_zero();
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make(an_d());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "𝟘");
//        ASSERT_TRUE(expression1.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//TEST(ExpressionStructuralBlocks, SingleChildSum) {
//    const auto expression = sa::SumExpression::make(cr_b());
//    ASSERT_EQ(expression.str(), "❴♯b❵");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), true);
//    ASSERT_EQ(expression.n_subexpressions(), 1);
//    ASSERT_EQ(boost::size(expression.range()), 1);
//    ASSERT_EQ(boost::size(expression.crange()), 1);
//    ASSERT_FALSE(expression.casted_target<sa::SumExpression>().unwrap().get().is_zero());
//    {
//        ASSERT_EQ(expression.subexpression(0).str(), "♯b");
//    }
//    {
//        ASSERT_EQ(expression.range()[0].str(), "♯b");
//    }
//    {
//        const auto expression1 = sa::SumExpression::make(cr_b());
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make(cr_b(), cr_b());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make(cr_b());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "❴♯b❵");
//        ASSERT_TRUE(expression1.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}

//TEST(ExpressionStructuralBlocks, ThreeChildrenSum) {
//    const auto expression = sa::SumExpression::make(cr_b(), cr_a(), an_d());
//    ASSERT_EQ(expression.str(), "❴♯b+♯a+♭d❵");
//    ASSERT_EQ(expression.is_of_type<sa::BosonCreationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::BosonAnnihilationOperator>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::ProductExpression>(), false);
//    ASSERT_EQ(expression.is_of_type<sa::SumExpression>(), true);
//    ASSERT_EQ(expression.n_subexpressions(), 3);
//    ASSERT_EQ(boost::size(expression.range()), 3);
//    ASSERT_EQ(boost::size(expression.crange()), 3);
//    ASSERT_FALSE(expression.casted_target<sa::SumExpression>().unwrap().get().is_zero());
//    {
//        ASSERT_EQ(expression.subexpression(0).str(), "♯b");
//        ASSERT_EQ(expression.subexpression(1).str(), "♯a");
//        ASSERT_EQ(expression.subexpression(2).str(), "♭d");
//    }
//    {
//        ASSERT_EQ(expression.range()[0].str(), "♯b");
//        ASSERT_EQ(expression.range()[1].str(), "♯a");
//        ASSERT_EQ(expression.range()[2].str(), "♭d");
//    }
//    {
//        const auto expression1 = sa::SumExpression::make(cr_b(), cr_a(), an_d());
//        ASSERT_TRUE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::SumExpression::make(cr_b(), cr_b());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = cr_a();
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = sa::ProductExpression::make(cr_b(), cr_a(), an_d());
//        ASSERT_FALSE(expression.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//    {
//        const auto expression1 = expression.clone();
//        ASSERT_EQ(expression1.str(), "❴♯b+♯a+♭d❵");
//        ASSERT_TRUE(expression1.equals(expression1));
//        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
//    }
//}
