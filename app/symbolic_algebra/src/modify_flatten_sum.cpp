// MY HEADER:
#include <symbolic_algebra/modify_flatten_sum.hpp>
// SELF:
#include <symbolic_algebra/modify_flatten_numerous_expression.hpp>
#include <symbolic_algebra/expression_final_structural_blocks.hpp>

namespace symbolic_algebra {

ModificationResult modify_flatten_sum(ExpressionHandler&& expression){
    return modify_flatten_numerous_expression<SumExpression>(std::move(expression));
}

}  // namespace symbolic_algebra