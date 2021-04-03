#ifndef SYMBOLIC_ALGEBRA_MODIFY_REBUILD_FACTOR_SUM_INTO_SUM_FACTORS_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_REBUILD_FACTOR_SUM_INTO_SUM_FACTORS_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: standard expand
 * Transformation example: 4❴a+b+c❵ => ❴❪4a❫+❪4b❫+❪4a❫❵
 * 
 */

ModificationResult modify_rebuild_factor_sum_into_sum_factors(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
