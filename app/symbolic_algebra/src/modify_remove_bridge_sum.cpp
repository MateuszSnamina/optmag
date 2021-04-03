// MY HEADER:
#include <symbolic_algebra/modify_remove_bridge_sum.hpp>
// SELF:
#include <symbolic_algebra/expression_final_structural_blocks.hpp>
#include <symbolic_algebra/modify_remove_bridge_numerous_expression.hpp>

namespace symbolic_algebra {

ModificationResult modify_remove_bridge_sum(ExpressionHandler&& expression) {
    return modify_remove_bridge_numerous_expression<SumExpression>(std::move(expression));
}

}  // namespace symbolic_algebra