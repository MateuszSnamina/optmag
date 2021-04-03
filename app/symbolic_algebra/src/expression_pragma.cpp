//MY HEADER:
#include <symbolic_algebra/expression_pragma.hpp>
#include <symbolic_algebra/expression_final_constant.hpp>
#include <symbolic_algebra/expression_final_variable.hpp>
#include <symbolic_algebra/expression_final_structural_blocks.hpp>

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
    return std::move(RealFactoredExpression::make(factor, std::move(expr)));
}

ExpressionHandler operator*(ExpressionHandler&& expr1, ExpressionHandler&& expr2) {
    return std::move(ProductExpression::make(expr1, expr2));
}

ExpressionHandler operator+(ExpressionHandler&& expr1, ExpressionHandler&& expr2) {
    return std::move(SumExpression::make(expr1, expr2));
}

}  // namespace operators

}  // namespace symbolic_algebra
