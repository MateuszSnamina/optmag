#ifndef SYMBOLIC_ALGEBRA_MODIFY_REMOVE_CONST_ZEROS_FROM_SUM_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REMOVE_CONST_ZEROS_FROM_SUM_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Detect sum of one ingredient and eliminate the not needed structural block
 * Transformation example: ❴0+a+0+b❵ => ❴a+b❵
 */

ModificationResult modify_remove_const_zeros_from_sum(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif

