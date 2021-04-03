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

}  // namespace symbolic_algebra
