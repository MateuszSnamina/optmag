#ifndef SYMBOLIC_ALGEBRA_MODIFY_REMOVE_CONST_ONES_FROM_PRODUCT_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REMOVE_CONST_ONES_FROM_PRODUCT_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Detect sum of one ingredient and eliminate the not needed structural block
 * Transformation example: ❪0◦a◦0◦b❫ => ❪a◦b❫
 */

ModificationResult modify_remove_const_ones_from_product(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
