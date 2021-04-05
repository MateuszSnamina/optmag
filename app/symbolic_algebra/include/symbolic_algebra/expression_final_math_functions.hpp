#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_FINAL_MATH_FUNCTIONS_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_FINAL_MATH_FUNCTIONS_HPP

#include<symbolic_algebra/expression_final_unary_functions.hpp>

#include<cmath>

using RealUnaryRawFunction = double(*)(double);

const char* sin_name = "sin";
const char* cos_name = "cos";
const char* tan_name = "tan";
const char* asin_name = "asin";
const char* acos_name = "acos";
const char* atan_name = "atan";

using SinExpression = symbolic_algebra::UnaryFunctionStaticExpression<&sin_name, RealUnaryRawFunction, std::sin>;
using CosExpression = symbolic_algebra::UnaryFunctionStaticExpression<&cos_name, RealUnaryRawFunction, std::cos>;
using TanExpression = symbolic_algebra::UnaryFunctionStaticExpression<&tan_name, RealUnaryRawFunction, std::tan>;
using AsinExpression = symbolic_algebra::UnaryFunctionStaticExpression<&asin_name, RealUnaryRawFunction, std::asin>;
using AcosExpression = symbolic_algebra::UnaryFunctionStaticExpression<&acos_name, RealUnaryRawFunction, std::acos>;
using AtanExpression = symbolic_algebra::UnaryFunctionStaticExpression<&atan_name, RealUnaryRawFunction, std::atan>;

const char* sinh_name = "sinh";
const char* cosh_name = "cosh";
const char* tanh_name = "tanh";
const char* asinh_name = "asinh";
const char* acosh_name = "acosh";
const char* atanh_name = "atanh";

using SinhExpression = symbolic_algebra::UnaryFunctionStaticExpression<&sinh_name, RealUnaryRawFunction, std::sinh>;
using CoshExpression = symbolic_algebra::UnaryFunctionStaticExpression<&cosh_name, RealUnaryRawFunction, std::cosh>;
using TanhExpression = symbolic_algebra::UnaryFunctionStaticExpression<&tanh_name, RealUnaryRawFunction, std::tanh>;
using AsinhExpression = symbolic_algebra::UnaryFunctionStaticExpression<&asinh_name, RealUnaryRawFunction, std::asinh>;
using AcoshExpression = symbolic_algebra::UnaryFunctionStaticExpression<&acosh_name, RealUnaryRawFunction, std::acosh>;
using AtanhExpression = symbolic_algebra::UnaryFunctionStaticExpression<&atanh_name, RealUnaryRawFunction, std::atanh>;

const char* exp_name = "exp";
const char* log_name = "log";
const char* log10_name = "log10";
const char* exp2_name = "exp2";
const char* expm1_name = "expm1";
const char* log1p_name = "log1p";
const char* log2_name = "log2";

using ExpExpression = symbolic_algebra::UnaryFunctionStaticExpression<&exp_name, RealUnaryRawFunction, std::exp>;
using LogExpression = symbolic_algebra::UnaryFunctionStaticExpression<&log_name, RealUnaryRawFunction, std::log>;
using Log10Expression = symbolic_algebra::UnaryFunctionStaticExpression<&log10_name, RealUnaryRawFunction, std::log10>;
using Exp2Expression = symbolic_algebra::UnaryFunctionStaticExpression<&exp2_name, RealUnaryRawFunction, std::exp2>;
using Expm1Expression = symbolic_algebra::UnaryFunctionStaticExpression<&expm1_name, RealUnaryRawFunction, std::expm1>;
using Log1pExpression = symbolic_algebra::UnaryFunctionStaticExpression<&log1p_name, RealUnaryRawFunction, std::log1p>;
using Log2Expression = symbolic_algebra::UnaryFunctionStaticExpression<&log2_name, RealUnaryRawFunction, std::log2>;

const char* sqrt_name = "sqrt";
const char* cbrt_name = "cbrt";

using SqrtExpression = symbolic_algebra::UnaryFunctionStaticExpression<&sqrt_name, RealUnaryRawFunction, std::sqrt>;
using CbrtExpression = symbolic_algebra::UnaryFunctionStaticExpression<&cbrt_name, RealUnaryRawFunction, std::cbrt>;

#endif
