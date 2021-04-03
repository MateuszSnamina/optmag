#ifndef SYMBOLIC_ALGEBRA_MODIFY_FLATTEN_FACTOR_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_FLATTEN_FACTOR_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Perform simplification due to factor product associativity.
 * Transformation example: ❪5❪3a❫❫ => ❪15a❫
 */

ModificationResult modify_flatten_factor(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
