#ifndef SYMBOLIC_ALGEBRA_MODIFY_CANONICAL_MATH_HPP
#define SYMBOLIC_ALGEBRA_MODIFY_CANONICAL_MATH_HPP

// SELF:
#include <symbolic_algebra/algorithm_dfs.hpp>
#include <symbolic_algebra/expression_abstract.hpp>

namespace symbolic_algebra {

ModificationResult modify_canonical_math(ExpressionHandler&& expression);

}  // namespace symbolic_algebra

#endif
