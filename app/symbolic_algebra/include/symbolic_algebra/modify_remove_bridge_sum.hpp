#ifndef SYMBOLIC_ALGEBRA_MODIFY_REMOVE_BRIDGE_SUM_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REMOVE_BRIDGE_SUM_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Detect sum of one ingredient and eliminate the not needed structural block
 * Transformation example: ❴a❵ => a
 */

ModificationResult modify_remove_bridge_sum(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif