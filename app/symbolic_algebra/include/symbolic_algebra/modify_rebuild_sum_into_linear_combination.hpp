#ifndef SYMBOLIC_ALGEBRA_MODIFY_REBUILD_SUM_INTO_LINEAR_COMBINATION_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REBUILD_SUM_INTO_LINEAR_COMBINATION_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Transform sum expression into the corresponding linear combination expression 
 * Transformation example: ❴a+❪3a❫+b+c❵ => ❴❪1a❫+❪3a❫+❪1b❫+(1c❫❵
 */

ModificationResult modify_rebuild_sum_into_linear_combination(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
