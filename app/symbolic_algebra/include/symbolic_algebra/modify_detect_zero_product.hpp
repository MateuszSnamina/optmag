#ifndef SYMBOLIC_ALGEBRA_MODIFY_DETECT_ZERO_PRODUCT_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_DETECT_ZERO_PRODUCT_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Detect when product expression has the zero factor
 * Transformation example: ❪a◦b◦𝟘◦c◦d❫ => 𝟘
 */

ModificationResult modify_detect_zero_product_1(ExpressionHandler&&);

/*
 * Transformation goal: Detect when product expression has the zero factor
 * Transformation example: ❪a◦b◦0◦c◦d❫ => 0
 */

ModificationResult modify_detect_zero_product_2(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
