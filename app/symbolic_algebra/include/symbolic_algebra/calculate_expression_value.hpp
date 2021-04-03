#ifndef SYMBOLIC_ALGEBRA_CALCULATE_EXPRESSION_VALUE_HPP
#define SYMBOLIC_ALGEBRA_CALCULATE_EXPRESSION_VALUE_HPP

#include<symbolic_algebra/expression_abstract.hpp>

#include<symbolic_algebra/expression_final_constant.hpp>
#include<symbolic_algebra/expression_final_variable.hpp>
#include<symbolic_algebra/expression_final_structural_blocks.hpp>

namespace symbolic_algebra {

double calculate_expression_value(ExpressionHandler expression_handler, arma::vec x) {
    if (const auto& casted_expression = expression_handler.casted_target<ConstantExpression>()) {
        return casted_expression.unwrap().get().value();
    } else if (const auto& casted_expression = expression_handler.casted_target<VariableExpression>()) {
        auto index = casted_expression.unwrap().get().index();
        assert(index <= x.n_rows);
        return x(index);
    } else if (const auto& casted_expression = expression_handler.casted_target<SumExpression>()) {
        //TODO
    } else if (const auto& casted_expression = expression_handler.casted_target<ProductExpression>()) {
        //TODO
    } else if (const auto& casted_expression = expression_handler.casted_target<RealFactoredExpression>()) {
        //TODO
    }
    throw std::runtime_error("No receipt for expression value calculation for expression `" + expression_handler.str() "`.");
}

}

#endif
