#ifndef SYMBOLIC_ALGEBRA_MODIFY_EVAL_PARTIAL_SUM_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_EVAL_PARTIAL_SUM_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Perform simplification due to product associativity.
 * Transformation example: ❴4+b+❴c+d❵+2+❪f◦g❫❵ => ❴6+b+❴c+d❵+❪f◦g❫❵
 */

ModificationResult modify_eval_partial_sum(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
