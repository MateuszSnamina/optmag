#ifndef SYMBOLIC_ALGEBRA_MODIFY_DETECT_ONE_FACTOR_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_DETECT_ONE_FACTOR_HPP

#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

/*
 * Transformation goal: Detect when a factor expression has the factor equal to one and eliminate the not needed factor expression
 * Transformation example: ❪1a❫ => a
 */

ModificationResult modify_detect_one_factor(ExpressionHandler&&);

}  // namespace symbolic_algebra

#endif
