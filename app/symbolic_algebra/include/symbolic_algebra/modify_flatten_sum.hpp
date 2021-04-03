#ifndef SYMBOLIC_ALGEBRA_MODIFY_FLATTEN_SUM_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_FLATTEN_SUM_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Perform simplification due to sum associativity.
 * Transformation example: ❴a+b+❴c+d❵+e+❴f+g❵❵ => ❴a+b+c+d+e+f+g❵
 */

ModificationResult modify_flatten_sum(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif