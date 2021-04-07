#ifndef SYMBOLIC_ALGEBRA_CALCULATE_EXPRESSION_VALUE_HPP
#define SYMBOLIC_ALGEBRA_CALCULATE_EXPRESSION_VALUE_HPP

#include<symbolic_algebra/expression_abstract.hpp>

#include<symbolic_algebra/expression_final_constant.hpp>
#include<symbolic_algebra/expression_final_variable.hpp>
#include<symbolic_algebra/expression_final_structural_blocks.hpp>
#include<symbolic_algebra/expression_final_unary_functions.hpp>

#include<armadillo>

#include<boost/range/adaptor/transformed.hpp>
#include<boost/range/numeric.hpp>

#include<optional>

namespace symbolic_algebra {

template<class T>
struct PlusOptional {
    std::optional<T> operator()(const std::optional<T>& value1, const std::optional<T>& value2) const {
        return (value1 && value2 ? std::optional<T>(*value1 + *value2) : std::optional<T>{} );
    }
};


template<class T>
struct MultipliesOptional {
    std::optional<T> operator()(const std::optional<T>& value1, const std::optional<T>& value2) const {
        return (value1 && value2 ? std::optional<T>(*value1 * *value2) : std::optional<T>{} );
    }
};

// **********************************************************
// ***  calculate_expression_value (without substituion)  ***
// **********************************************************

inline double calculate_expression_value(const ExpressionHandler& expression_handler) {
    if (const auto& casted_expression = expression_handler.casted_target<ConstantExpression>()) {
        return casted_expression.unwrap().get().value();
    } else if (const auto& casted_expression = expression_handler.casted_target<VariableExpression>()) {
        throw std::runtime_error("No substitution for expression `" + expression_handler.str() + "`.");
    } else if (const auto& casted_expression = expression_handler.casted_target<SumExpression>()) {
        const auto value_of_child_expressions = expression_handler.crange() | boost::adaptors::transformed(calculate_expression_value);
        const auto value = boost::accumulate(value_of_child_expressions, 0.0, std::plus<double>());
        return value;
    } else if (const auto& casted_expression = expression_handler.casted_target<ProductExpression>()) {
        const auto value_of_child_expressions = expression_handler.crange() | boost::adaptors::transformed(calculate_expression_value);
        const auto value = boost::accumulate(value_of_child_expressions, 1.0, std::multiplies<double>());
        return value;
    } else if (const auto& casted_expression = expression_handler.casted_target<RealFactoredExpression>()) {
        const auto factor = casted_expression.unwrap().get().factor();
        const auto value_of_child_expression = calculate_expression_value(expression_handler.subexpression(0));
        return factor * value_of_child_expression;
    } else if (const auto& casted_expression = expression_handler.casted_target<UnaryFunctionExpression>()) {
        const auto value_of_child_expression = calculate_expression_value(expression_handler.subexpression(0));
        return casted_expression.unwrap().get().eval(value_of_child_expression);
    }
    throw std::runtime_error("No receipt for expression value calculation for expression `" + expression_handler.str() + "`.");
}

// **********************************************************
// ***  calculate_expression_value (with substituion)     ***
// **********************************************************

inline double calculate_expression_value(const ExpressionHandler& expression_handler, const arma::vec& x) {
    const auto calculate_expression_value_closure = [&x](const ExpressionHandler& expression_handler) {
        return calculate_expression_value(expression_handler, x);
    };
    if (const auto& casted_expression = expression_handler.casted_target<ConstantExpression>()) {
        return casted_expression.unwrap().get().value();
    } else if (const auto& casted_expression = expression_handler.casted_target<VariableExpression>()) {
        const auto index = casted_expression.unwrap().get().index();
        assert(index <= x.n_rows);
        return x(index);
    } else if (const auto& casted_expression = expression_handler.casted_target<SumExpression>()) {
        const auto value_of_child_expressions = expression_handler.crange() | boost::adaptors::transformed(calculate_expression_value_closure);
        const auto value = boost::accumulate(value_of_child_expressions, 0.0, std::plus<double>());
        return value;
    } else if (const auto& casted_expression = expression_handler.casted_target<ProductExpression>()) {
        const auto value_of_child_expressions = expression_handler.crange() | boost::adaptors::transformed(calculate_expression_value_closure);
        const auto value = boost::accumulate(value_of_child_expressions, 1.0, std::multiplies<double>());
        return value;
    } else if (const auto& casted_expression = expression_handler.casted_target<RealFactoredExpression>()) {
        const auto factor = casted_expression.unwrap().get().factor();
        const auto value_of_child_expression = calculate_expression_value_closure(expression_handler.subexpression(0));
        return factor * value_of_child_expression;
    } else if (const auto& casted_expression = expression_handler.casted_target<UnaryFunctionExpression>()) {
        const auto value_of_child_expression = calculate_expression_value_closure(expression_handler.subexpression(0));
        return casted_expression.unwrap().get().eval(value_of_child_expression);
    }
    throw std::runtime_error("No receipt for expression value calculation for expression `" + expression_handler.str() + "`.");
}

// ******************************************************************
// ***  calculate_expression_optional_value (without substituion) ***
// ******************************************************************


inline std::optional<double> calculate_expression_optional_value(const ExpressionHandler& expression_handler) {
    if (const auto& casted_expression = expression_handler.casted_target<ConstantExpression>()) {
        return casted_expression.unwrap().get().value();
    } else if (const auto& casted_expression = expression_handler.casted_target<VariableExpression>()) {
        return std::nullopt;
    } else if (const auto& casted_expression = expression_handler.casted_target<SumExpression>()) {
        const auto value_of_child_expressions = expression_handler.crange() | boost::adaptors::transformed(calculate_expression_optional_value);
        const auto value = boost::accumulate(value_of_child_expressions, std::optional<double>(0.0), PlusOptional<double>());
        return value;
    } else if (const auto& casted_expression = expression_handler.casted_target<ProductExpression>()) {
        const auto value_of_child_expressions = expression_handler.crange() | boost::adaptors::transformed(calculate_expression_optional_value);
        const auto value = boost::accumulate(value_of_child_expressions, std::optional<double>(1.0), MultipliesOptional<double>());
        return value;
    } else if (const auto& casted_expression = expression_handler.casted_target<RealFactoredExpression>()) {
        if (const auto value_of_child_expression_optional = calculate_expression_optional_value(expression_handler.subexpression(0))) {
            const auto value_of_child_expression = *value_of_child_expression_optional;
            const auto factor = casted_expression.unwrap().get().factor();
            return factor * value_of_child_expression;
        } else {
            return std::nullopt;
        }
    } else if (const auto& casted_expression = expression_handler.casted_target<UnaryFunctionExpression>()) {
        if (const auto value_of_child_expression_optional = calculate_expression_optional_value(expression_handler.subexpression(0))) {
            const auto value_of_child_expression = *value_of_child_expression_optional;
            return casted_expression.unwrap().get().eval(value_of_child_expression);
        } else {
            return std::nullopt;
        }
    }
    throw std::runtime_error("No receipt for expression value calculation for expression `" + expression_handler.str() + "`.");
}

// ******************************************************************
// ***  calculate_expression_optional_value (with substituion)    ***
// ******************************************************************

inline std::optional<double> calculate_expression_optional_value(const ExpressionHandler& expression_handler, const arma::vec& x) {
    const auto calculate_expression_optional_value_closure = [&x](const ExpressionHandler& expression_handler) {
        return calculate_expression_optional_value(expression_handler, x);
    };
    if (const auto& casted_expression = expression_handler.casted_target<ConstantExpression>()) {
        return casted_expression.unwrap().get().value();
    } else if (const auto& casted_expression = expression_handler.casted_target<VariableExpression>()) {
        const auto index = casted_expression.unwrap().get().index();
        assert(index <= x.n_rows);
        return x(index);
    } else if (const auto& casted_expression = expression_handler.casted_target<SumExpression>()) {
        const auto value_of_child_expressions = expression_handler.crange() | boost::adaptors::transformed(calculate_expression_optional_value_closure);
        const auto value = boost::accumulate(value_of_child_expressions, std::optional<double>(0.0), PlusOptional<double>());
        return value;
    } else if (const auto& casted_expression = expression_handler.casted_target<ProductExpression>()) {
        const auto value_of_child_expressions = expression_handler.crange() | boost::adaptors::transformed(calculate_expression_optional_value_closure);
        const auto value = boost::accumulate(value_of_child_expressions, std::optional<double>(1.0), MultipliesOptional<double>());
        return value;
    } else if (const auto& casted_expression = expression_handler.casted_target<RealFactoredExpression>()) {
        if (const auto value_of_child_expression_optional = calculate_expression_optional_value_closure(expression_handler.subexpression(0))) {
            const auto value_of_child_expression = *value_of_child_expression_optional;
            const auto factor = casted_expression.unwrap().get().factor();
            return factor * value_of_child_expression;
        } else {
            return std::nullopt;
        }
    } else if (const auto& casted_expression = expression_handler.casted_target<UnaryFunctionExpression>()) {
        if (const auto value_of_child_expression_optional = calculate_expression_optional_value_closure(expression_handler.subexpression(0))) {
            const auto value_of_child_expression = *value_of_child_expression_optional;
            return casted_expression.unwrap().get().eval(value_of_child_expression);
        } else {
            return std::nullopt;
        }
    }
    throw std::runtime_error("No receipt for expression value calculation for expression `" + expression_handler.str() + "`.");
}

}

#endif
