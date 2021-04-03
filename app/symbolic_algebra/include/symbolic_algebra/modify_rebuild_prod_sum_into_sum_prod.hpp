#ifndef SYMBOLIC_ALGEBRA_MODIFY_REBUILD_PROD_SUM_INTO_SUM_PROD_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REBUILD_PROD_SUM_INTO_SUM_PROD_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Standard expand.
 * Transformation example: ❪a◦❴b+c❵◦d❫ => ❴❪a◦b◦d❫+❪a◦c◦d❫❵
 */
ModificationResult modify_rebuild_prod_sum_into_sum_prod(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif