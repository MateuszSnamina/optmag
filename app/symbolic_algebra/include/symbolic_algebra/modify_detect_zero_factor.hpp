#ifndef SYMBOLIC_ALGEBRA_MODIFY_DETECT_ZERO_FACTOR_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_DETECT_ZERO_FACTOR_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Detect when a factor expression has the zero factor or the zero subexpression
 * Transformation example: ❪0a❫ => 𝟘
 * Transformation example: ❪5𝟘❫ => 𝟘
 */

ModificationResult modify_detect_zero_factor(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
