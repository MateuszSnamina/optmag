#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_PRAGMA_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_PRAGMA_HPP

//SELF:
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

namespace literals {

ExpressionHandler operator"" _const(long double);
ExpressionHandler operator"" _var(unsigned long long);

}  // namespace literals

namespace operators {

ExpressionHandler operator*(long long, ExpressionHandler&&);
ExpressionHandler operator*(ExpressionHandler&&, ExpressionHandler&&);
ExpressionHandler operator+(ExpressionHandler&&, ExpressionHandler&&);

}  // namespace operators

namespace math {

ExpressionHandler abs(ExpressionHandler&& expr);
ExpressionHandler inv(ExpressionHandler&& expr);
ExpressionHandler sq(ExpressionHandler&& expr);
ExpressionHandler cb(ExpressionHandler&& expr);
ExpressionHandler sin(ExpressionHandler&& expr);
ExpressionHandler cos(ExpressionHandler&& expr);
ExpressionHandler tan(ExpressionHandler&& expr);
ExpressionHandler asin(ExpressionHandler&& expr);
ExpressionHandler acos(ExpressionHandler&& expr);
ExpressionHandler atan(ExpressionHandler&& expr);
ExpressionHandler sinh(ExpressionHandler&& expr);
ExpressionHandler cosh(ExpressionHandler&& expr);
ExpressionHandler tanh(ExpressionHandler&& expr);
ExpressionHandler asinh(ExpressionHandler&& expr);
ExpressionHandler acosh(ExpressionHandler&& expr);
ExpressionHandler atanh(ExpressionHandler&& expr);
ExpressionHandler exp(ExpressionHandler&& expr);
ExpressionHandler log(ExpressionHandler&& expr);
ExpressionHandler log10(ExpressionHandler&& expr);
ExpressionHandler exp2(ExpressionHandler&& expr);
ExpressionHandler expm1(ExpressionHandler&& expr);
ExpressionHandler log1p(ExpressionHandler&& expr);
ExpressionHandler log2(ExpressionHandler&& expr);
ExpressionHandler sqrt(ExpressionHandler&& expr);
ExpressionHandler cbrt(ExpressionHandler&& expr);

} // namespace math

}  // namespace symbolic_algebra

#endif
