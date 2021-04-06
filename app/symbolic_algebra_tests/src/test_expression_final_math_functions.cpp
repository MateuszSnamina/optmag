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

    const auto expression_abs = abs(9.1_const);
    ASSERT_EQ(expression_abs.str(), "abs⦗9.1⦘");

    const auto expression_inv = inv(9.1_const);
    ASSERT_EQ(expression_inv.str(), "inv⦗9.1⦘");

    const auto expression_sq = sq(9.1_const);
    ASSERT_EQ(expression_sq.str(), "sq⦗9.1⦘");

    const auto expression_cb = cb(9.1_const);
    ASSERT_EQ(expression_cb.str(), "cb⦗9.1⦘");

    const auto expression_sin = sin(9.1_const);
    ASSERT_EQ(expression_sin.str(), "sin⦗9.1⦘");

    const auto expression_cos = cos(9.1_const);
    ASSERT_EQ(expression_cos.str(), "cos⦗9.1⦘");

    const auto expression_tan = tan(9.1_const);
    ASSERT_EQ(expression_tan.str(), "tan⦗9.1⦘");

    const auto expression_asin = asin(9.1_const);
    ASSERT_EQ(expression_asin.str(), "asin⦗9.1⦘");

    const auto expression_acos = acos(9.1_const);
    ASSERT_EQ(expression_acos.str(), "acos⦗9.1⦘");

    const auto expression_atan = atan(9.1_const);
    ASSERT_EQ(expression_atan.str(), "atan⦗9.1⦘");

    const auto expression_sinh = sinh(9.1_const);
    ASSERT_EQ(expression_sinh.str(), "sinh⦗9.1⦘");

    const auto expression_cosh = cosh(9.1_const);
    ASSERT_EQ(expression_cosh.str(), "cosh⦗9.1⦘");

    const auto expression_tanh = tanh(9.1_const);
    ASSERT_EQ(expression_tanh.str(), "tanh⦗9.1⦘");

    const auto expression_asinh = asinh(9.1_const);
    ASSERT_EQ(expression_asinh.str(), "asinh⦗9.1⦘");

    const auto expression_acosh = acosh(9.1_const);
    ASSERT_EQ(expression_acosh.str(), "acosh⦗9.1⦘");

    const auto expression_atanh = atanh(9.1_const);
    ASSERT_EQ(expression_atanh.str(), "atanh⦗9.1⦘");

    const auto expression_exp = exp(9.1_const);
    ASSERT_EQ(expression_exp.str(), "exp⦗9.1⦘");

    const auto expression_log = log(9.1_const);
    ASSERT_EQ(expression_log.str(), "log⦗9.1⦘");

    const auto expression_log10 = log10(9.1_const);
    ASSERT_EQ(expression_log10.str(), "log10⦗9.1⦘");

    const auto expression_exp2 = exp2(9.1_const);
    ASSERT_EQ(expression_exp2.str(), "exp2⦗9.1⦘");

    const auto expression_expm1 = expm1(9.1_const);
    ASSERT_EQ(expression_expm1.str(), "expm1⦗9.1⦘");

    const auto expression_log1p = log1p(9.1_const);
    ASSERT_EQ(expression_log1p.str(), "log1p⦗9.1⦘");

    const auto expression_log2 = log2(9.1_const);
    ASSERT_EQ(expression_log2.str(), "log2⦗9.1⦘");

    const auto expression_sqrt = sqrt(9.1_const);
    ASSERT_EQ(expression_sqrt.str(), "sqrt⦗9.1⦘");

    const auto expression_cbrt = cbrt(9.1_const);
    ASSERT_EQ(expression_cbrt.str(), "cbrt⦗9.1⦘");

}
