//MY HEADER:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/expression_final_constant.hpp>
#include <symbolic_algebra/expression_final_variable.hpp>
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
#include <symbolic_algebra/expression_final_math_functions.hpp>

//STD:
#include <vector>

namespace symbolic_algebra {

namespace literals {

ExpressionHandler operator"" _const(long double value) {
    //TODO check overflow
    return ConstantExpression::make(value);
}

ExpressionHandler operator"" _var(unsigned long long index) {
    //TODO check overflow
    return VariableExpression::make(index);
}

}  // namespace literals

namespace operators {
ExpressionHandler operator*(long long factor, ExpressionHandler&& expr) {
    return RealFactoredExpression::make(factor, std::move(expr));
}

ExpressionHandler operator*(ExpressionHandler&& expr1, ExpressionHandler&& expr2) {
    return ProductExpression::make(std::move(expr1), std::move(expr2));
}

ExpressionHandler operator+(ExpressionHandler&& expr1, ExpressionHandler&& expr2) {
    return SumExpression::make(std::move(expr1), std::move(expr2));
}

}  // namespace operators

namespace math {

ExpressionHandler abs(ExpressionHandler&& expr) {
    return AbsExpression::make(std::move(expr));
}

ExpressionHandler inv(ExpressionHandler&& expr) {
    return InvExpression::make(std::move(expr));
}

ExpressionHandler sq(ExpressionHandler&& expr) {
    return SqExpression::make(std::move(expr));
}

ExpressionHandler cb(ExpressionHandler&& expr) {
    return CbExpression::make(std::move(expr));
}

ExpressionHandler sin(ExpressionHandler&& expr) {
    return SinExpression::make(std::move(expr));
}

ExpressionHandler cos(ExpressionHandler&& expr) {
    return CosExpression::make(std::move(expr));
}

ExpressionHandler tan(ExpressionHandler&& expr) {
    return TanExpression::make(std::move(expr));
}

ExpressionHandler asin(ExpressionHandler&& expr) {
    return AsinExpression::make(std::move(expr));
}

ExpressionHandler acos(ExpressionHandler&& expr) {
    return AcosExpression::make(std::move(expr));
}

ExpressionHandler atan(ExpressionHandler&& expr) {
    return AtanExpression::make(std::move(expr));
}

ExpressionHandler sinh(ExpressionHandler&& expr) {
    return SinhExpression::make(std::move(expr));
}

ExpressionHandler cosh(ExpressionHandler&& expr) {
    return CoshExpression::make(std::move(expr));
}

ExpressionHandler tanh(ExpressionHandler&& expr) {
    return TanhExpression::make(std::move(expr));
}

ExpressionHandler asinh(ExpressionHandler&& expr) {
    return AsinhExpression::make(std::move(expr));
}

ExpressionHandler acosh(ExpressionHandler&& expr) {
    return AcoshExpression::make(std::move(expr));
}

ExpressionHandler atanh(ExpressionHandler&& expr) {
    return AtanhExpression::make(std::move(expr));
}

ExpressionHandler exp(ExpressionHandler&& expr) {
    return ExpExpression::make(std::move(expr));
}

ExpressionHandler log(ExpressionHandler&& expr) {
    return LogExpression::make(std::move(expr));
}

ExpressionHandler log10(ExpressionHandler&& expr) {
    return Log10Expression::make(std::move(expr));
}

ExpressionHandler exp2(ExpressionHandler&& expr) {
    return Exp2Expression::make(std::move(expr));
}

ExpressionHandler expm1(ExpressionHandler&& expr) {
    return Expm1Expression::make(std::move(expr));
}

ExpressionHandler log1p(ExpressionHandler&& expr) {
    return Log1pExpression::make(std::move(expr));
}

ExpressionHandler log2(ExpressionHandler&& expr) {
    return Log2Expression::make(std::move(expr));
}

ExpressionHandler sqrt(ExpressionHandler&& expr) {
    return SqrtExpression::make(std::move(expr));
}

ExpressionHandler cbrt(ExpressionHandler&& expr) {
    return CbrtExpression::make(std::move(expr));
}

} // namespace math

}  // namespace symbolic_algebra
