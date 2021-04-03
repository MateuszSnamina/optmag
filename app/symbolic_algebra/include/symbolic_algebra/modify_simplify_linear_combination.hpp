#ifndef SYMBOLIC_ALGEBRA_MODIFY_SIMPLIFY_LINEAR_COMBINATION_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_SIMPLIFY_LINEAR_COMBINATION_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Simplify linear combination expressions
 * Transformation example: ❴❪3*a❫+❪1*b❫+❪2*a❫+❪1*c❫+❪1*c❫❵ => ❴❪5*a❫+❪1*b❫+❪2*c❫❵
 */

ModificationResult modify_simplify_linear_combination(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
