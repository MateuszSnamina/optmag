// TESTED LIBRARY:
#include <symbolic_algebra/expression_final_math_functions.hpp>
#include <symbolic_algebra/expression_pragma.hpp>

// GTEST:
#include <gtest/gtest.h>
// BOOST:
#include <boost/range/algorithm/count.hpp>

namespace sa = symbolic_algebra;
using namespace sa::literals;
using namespace sa::math;

TEST(FinalMathFunctions, ConstantExpression) {
    {
        const auto expression_abs = abs(9.1_const);
        ASSERT_EQ(expression_abs.str(), "abs⦗9.1⦘");
        const auto expression_casted = expression_abs.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::abs(0.1234));
    }
    {
        const auto expression_inv = inv(9.1_const);
        ASSERT_EQ(expression_inv.str(), "inv⦗9.1⦘");
        const auto expression_casted = expression_inv.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), 1.0 / 0.1234);
    }
    {
        const auto expression_sq = sq(9.1_const);
        ASSERT_EQ(expression_sq.str(), "sq⦗9.1⦘");
        const auto expression_casted = expression_sq.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), 0.1234 * 0.1234);
    }
    {
        const auto expression_cb = cb(9.1_const);
        ASSERT_EQ(expression_cb.str(), "cb⦗9.1⦘");
        const auto expression_casted = expression_cb.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), 0.1234 * 0.1234 * 0.1234);
    }
    {
        const auto expression_sin = sin(9.1_const);
        ASSERT_EQ(expression_sin.str(), "sin⦗9.1⦘");
        const auto expression_casted = expression_sin.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::sin(0.1234));
    }
    {
        const auto expression_cos = cos(9.1_const);
        ASSERT_EQ(expression_cos.str(), "cos⦗9.1⦘");
        const auto expression_casted = expression_cos.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::cos(0.1234));
    }
    {
        const auto expression_tan = tan(9.1_const);
        ASSERT_EQ(expression_tan.str(), "tan⦗9.1⦘");
        const auto expression_casted = expression_tan.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::tan(0.1234));
    }
    {
        const auto expression_asin = asin(9.1_const);
        ASSERT_EQ(expression_asin.str(), "asin⦗9.1⦘");
        const auto expression_casted = expression_asin.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::asin(0.1234));
    }
    {
        const auto expression_acos = acos(9.1_const);
        ASSERT_EQ(expression_acos.str(), "acos⦗9.1⦘");
        const auto expression_casted = expression_acos.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::acos(0.1234));
    }
    {
        const auto expression_atan = atan(9.1_const);
        ASSERT_EQ(expression_atan.str(), "atan⦗9.1⦘");
        const auto expression_casted = expression_atan.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::atan(0.1234));
    }
    {
        const auto expression_sinh = sinh(9.1_const);
        ASSERT_EQ(expression_sinh.str(), "sinh⦗9.1⦘");
        const auto expression_casted = expression_sinh.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::sinh(0.1234));
    }
    {
        const auto expression_cosh = cosh(9.1_const);
        ASSERT_EQ(expression_cosh.str(), "cosh⦗9.1⦘");
        const auto expression_casted = expression_cosh.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::cosh(0.1234));
    }
    {
        const auto expression_tanh = tanh(9.1_const);
        ASSERT_EQ(expression_tanh.str(), "tanh⦗9.1⦘");
        const auto expression_casted = expression_tanh.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::tanh(0.1234));
    }
    {
        const auto expression_asinh = asinh(9.1_const);
        ASSERT_EQ(expression_asinh.str(), "asinh⦗9.1⦘");
        const auto expression_casted = expression_asinh.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::asinh(0.1234));
    }
    {
        const auto expression_acosh = acosh(9.1_const);
        ASSERT_EQ(expression_acosh.str(), "acosh⦗9.1⦘");
        const auto expression_casted = expression_acosh.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(1.1234), std::acosh(1.1234));
    }
    {
        const auto expression_atanh = atanh(9.1_const);
        ASSERT_EQ(expression_atanh.str(), "atanh⦗9.1⦘");
        const auto expression_casted = expression_atanh.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::atanh(0.1234));
    }
    {
        const auto expression_exp = exp(9.1_const);
        ASSERT_EQ(expression_exp.str(), "exp⦗9.1⦘");
        const auto expression_casted = expression_exp.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::exp(0.1234));
    }
    {
        const auto expression_log = log(9.1_const);
        ASSERT_EQ(expression_log.str(), "log⦗9.1⦘");
        const auto expression_casted = expression_log.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::log(0.1234));
    }
    {
        const auto expression_log10 = log10(9.1_const);
        ASSERT_EQ(expression_log10.str(), "log10⦗9.1⦘");
        const auto expression_casted = expression_log10.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::log10(0.1234));
    }
    {
        const auto expression_exp2 = exp2(9.1_const);
        ASSERT_EQ(expression_exp2.str(), "exp2⦗9.1⦘");
        const auto expression_casted = expression_exp2.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::exp2(0.1234));
    }
    {
        const auto expression_expm1 = expm1(9.1_const);
        ASSERT_EQ(expression_expm1.str(), "expm1⦗9.1⦘");
        const auto expression_casted = expression_expm1.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::expm1(0.1234));
    }
    {
        const auto expression_log1p = log1p(9.1_const);
        ASSERT_EQ(expression_log1p.str(), "log1p⦗9.1⦘");
        const auto expression_casted = expression_log1p.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::log1p(0.1234));
    }
    {
        const auto expression_log2 = log2(9.1_const);
        ASSERT_EQ(expression_log2.str(), "log2⦗9.1⦘");
        const auto expression_casted = expression_log2.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::log2(0.1234));
    }
    {
        const auto expression_sqrt = sqrt(9.1_const);
        ASSERT_EQ(expression_sqrt.str(), "sqrt⦗9.1⦘");
        const auto expression_casted = expression_sqrt.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::sqrt(0.1234));
    }
    {
        const auto expression_cbrt = cbrt(9.1_const);
        ASSERT_EQ(expression_cbrt.str(), "cbrt⦗9.1⦘");
        const auto expression_casted = expression_cbrt.casted_target<sa::UnaryFunctionExpression>();
        ASSERT_TRUE(expression_casted);
        ASSERT_DOUBLE_EQ(expression_casted.unwrap().get().eval(0.1234), std::cbrt(0.1234));
    }

}
