#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_HPP

// EXPRESSION-ABSTRACT:

#include<symbolic_algebra/expression_abstract.hpp>
#include<symbolic_algebra/expression_abstract_common.hpp>

// EXPRESSION-FINAL:

#include<symbolic_algebra/expression_final_structural_blocks.hpp>
#include<symbolic_algebra/expression_final_variable.hpp>
#include<symbolic_algebra/expression_final_constant.hpp>

#include<symbolic_algebra/expression_pragma.hpp>

// MODIFY:

#include<symbolic_algebra/modify_rebuild_prod_sum_into_sum_prod.hpp>
#include<symbolic_algebra/modify_rebuild_factor_sum_into_sum_factors.hpp>
#include<symbolic_algebra/modify_rebuild_prod_factors_into_factor_prod.hpp>
#include<symbolic_algebra/modify_rebuild_sum_into_linear_combination.hpp>

#include<symbolic_algebra/modify_remove_bridge_numerous_expression.hpp>
#include<symbolic_algebra/modify_remove_bridge_sum.hpp>
#include<symbolic_algebra/modify_remove_bridge_product.hpp>

#include<symbolic_algebra/modify_flatten_numerous_expression.hpp>
#include<symbolic_algebra/modify_flatten_sum.hpp>
#include<symbolic_algebra/modify_flatten_product.hpp>
#include<symbolic_algebra/modify_flatten_factor.hpp>

#include<symbolic_algebra/modify_detect_zero_product.hpp>
#include<symbolic_algebra/modify_detect_zero_factor.hpp>
#include<symbolic_algebra/modify_detect_one_factor.hpp>

#include<symbolic_algebra/modify_simplify_linear_combination.hpp>

// ALGO:

#include<symbolic_algebra/algorithm_dfs.hpp>

#endif
