#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_FINAL_MATH_FUNCTIONS_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_FINAL_MATH_FUNCTIONS_HPP

#include<symbolic_algebra/expression_final_unary_functions.hpp>

#include<cmath>

namespace symbolic_algebra {

inline double inv(double x) {
    return 1.0 / x;
}

inline double sq(double x) {
    return x * x;
}

inline double cb(double x) {
    return x * x * x;
}

using RealUnaryRawFunction = double(*)(double);

inline const char* abs_name = "abs";
inline const char* inv_name = "inv";
inline const char* sq_name = "sq";
inline const char* cb_name = "cb";

using AbsExpression = symbolic_algebra::UnaryFunctionStaticExpression<&abs_name, RealUnaryRawFunction, std::abs>;
using InvExpression = symbolic_algebra::UnaryFunctionStaticExpression<&inv_name, RealUnaryRawFunction, inv>;
using SqExpression = symbolic_algebra::UnaryFunctionStaticExpression<&sq_name, RealUnaryRawFunction, sq>;
using CbExpression = symbolic_algebra::UnaryFunctionStaticExpression<&cb_name, RealUnaryRawFunction, cb>;

inline const char* sin_name = "sin";
inline const char* cos_name = "cos";
inline const char* tan_name = "tan";
inline const char* asin_name = "asin";
inline const char* acos_name = "acos";
inline const char* atan_name = "atan";

using SinExpression = symbolic_algebra::UnaryFunctionStaticExpression<&sin_name, RealUnaryRawFunction, std::sin>;
using CosExpression = symbolic_algebra::UnaryFunctionStaticExpression<&cos_name, RealUnaryRawFunction, std::cos>;
using TanExpression = symbolic_algebra::UnaryFunctionStaticExpression<&tan_name, RealUnaryRawFunction, std::tan>;
using AsinExpression = symbolic_algebra::UnaryFunctionStaticExpression<&asin_name, RealUnaryRawFunction, std::asin>;
using AcosExpression = symbolic_algebra::UnaryFunctionStaticExpression<&acos_name, RealUnaryRawFunction, std::acos>;
using AtanExpression = symbolic_algebra::UnaryFunctionStaticExpression<&atan_name, RealUnaryRawFunction, std::atan>;

inline const char* sinh_name = "sinh";
inline const char* cosh_name = "cosh";
inline const char* tanh_name = "tanh";
inline const char* asinh_name = "asinh";
inline const char* acosh_name = "acosh";
inline const char* atanh_name = "atanh";

using SinhExpression = symbolic_algebra::UnaryFunctionStaticExpression<&sinh_name, RealUnaryRawFunction, std::sinh>;
using CoshExpression = symbolic_algebra::UnaryFunctionStaticExpression<&cosh_name, RealUnaryRawFunction, std::cosh>;
using TanhExpression = symbolic_algebra::UnaryFunctionStaticExpression<&tanh_name, RealUnaryRawFunction, std::tanh>;
using AsinhExpression = symbolic_algebra::UnaryFunctionStaticExpression<&asinh_name, RealUnaryRawFunction, std::asinh>;
using AcoshExpression = symbolic_algebra::UnaryFunctionStaticExpression<&acosh_name, RealUnaryRawFunction, std::acosh>;
using AtanhExpression = symbolic_algebra::UnaryFunctionStaticExpression<&atanh_name, RealUnaryRawFunction, std::atanh>;

inline const char* exp_name = "exp";
inline const char* log_name = "log";
inline const char* log10_name = "log10";
inline const char* exp2_name = "exp2";
inline const char* expm1_name = "expm1";
inline const char* log1p_name = "log1p";
inline const char* log2_name = "log2";

using ExpExpression = symbolic_algebra::UnaryFunctionStaticExpression<&exp_name, RealUnaryRawFunction, std::exp>;
using LogExpression = symbolic_algebra::UnaryFunctionStaticExpression<&log_name, RealUnaryRawFunction, std::log>;
using Log10Expression = symbolic_algebra::UnaryFunctionStaticExpression<&log10_name, RealUnaryRawFunction, std::log10>;
using Exp2Expression = symbolic_algebra::UnaryFunctionStaticExpression<&exp2_name, RealUnaryRawFunction, std::exp2>;
using Expm1Expression = symbolic_algebra::UnaryFunctionStaticExpression<&expm1_name, RealUnaryRawFunction, std::expm1>;
using Log1pExpression = symbolic_algebra::UnaryFunctionStaticExpression<&log1p_name, RealUnaryRawFunction, std::log1p>;
using Log2Expression = symbolic_algebra::UnaryFunctionStaticExpression<&log2_name, RealUnaryRawFunction, std::log2>;

inline const char* sqrt_name = "sqrt";
inline const char* cbrt_name = "cbrt";

using SqrtExpression = symbolic_algebra::UnaryFunctionStaticExpression<&sqrt_name, RealUnaryRawFunction, std::sqrt>;
using CbrtExpression = symbolic_algebra::UnaryFunctionStaticExpression<&cbrt_name, RealUnaryRawFunction, std::cbrt>;

}  // namespace symbolic_algebra

#endif
