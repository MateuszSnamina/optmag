#ifndef SYMBOLIC_ALGEBRA_MODIFY_REBUILD_PROD_FACTORS_INTO_FACTOR_PROD_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REBUILD_PROD_FACTORS_INTO_FACTOR_PROD_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Take out the accumulated factor of the product factors
 * Transformation example: ❪❪3a❫◦❪1b❫◦❪2a❫❫ => ❪6❪a◦b◦a❫❫
 * 
 */

ModificationResult modify_rebuild_prod_factors_into_factor_prod(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
