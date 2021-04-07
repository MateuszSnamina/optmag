#ifndef SYMBOLIC_ALGEBRA_MODIFY_REMOVE_BRIDGE_PRODUCT_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REMOVE_BRIDGE_PRODUCT_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Detect product of one factor and eliminate the not needed structural block
 * Transformation example: ❪a❫ => a
 */

ModificationResult modify_remove_bridge_product(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
