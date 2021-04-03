// MY HEADER:
#include <symbolic_algebra/modify_flatten_product.hpp>
// SELF:
#include <symbolic_algebra/modify_flatten_numerous_expression.hpp>
#include <symbolic_algebra/expression_final_structural_blocks.hpp>

namespace symbolic_algebra {

ModificationResult modify_flatten_product(ExpressionHandler&& expression){
    return modify_flatten_numerous_expression<ProductExpression>(std::move(expression));
}

}  // namespace symbolic_algebra
