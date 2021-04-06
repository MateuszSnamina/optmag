#ifndef SYMBOLIC_ALGEBRA_CALCULATE_EXPRESSION_DERIVATIVE_HPP
#define SYMBOLIC_ALGEBRA_CALCULATE_EXPRESSION_DERIVATIVE_HPP

#include<symbolic_algebra/expression_abstract.hpp>

#include<symbolic_algebra/expression_final_constant.hpp>
#include<symbolic_algebra/expression_final_variable.hpp>
#include<symbolic_algebra/expression_final_structural_blocks.hpp>
#include<symbolic_algebra/expression_final_math_functions.hpp>

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/indexed.hpp>

#include <boost/range.hpp>
#include <boost/range/irange.hpp>

#include <cassert>

namespace symbolic_algebra::derivatives_table {

/*
 * derivatives_tabl is produce expression
 *
 * ∂/∂a_index f(a_1, a_2, ... , a_n) |_{a_1 = formal_argument_1, a_2 = formal_argument_2}
 *
 *
 * For gixen `index`, `formal_argument_*` and `f(.,.,...,.)`.
 *
 * Each supported `f(.,.,...,.)` has its exclusive C++-class,
 * `index`, `formal_argument_*` are passed as the a member function arguments.
 *
 */

/*
 * For f(a_1, a_2, ... , a_n) =  a_1 * a_2 * ... * a_n
 */
struct ProductDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(index < n_formal_arguments);
        ExpressionHandlerVector new_subexpressions;
        for (const auto& formal_argument_with_index : formal_arguments | boost::adaptors::indexed(0) ) {
            if (formal_argument_with_index.index() != index) {
                new_subexpressions.push_back(formal_argument_with_index.value().clone());
            }
        }
        return ProductExpression::make_from_buffer(std::move(new_subexpressions));
    }
};

/*
 * For f(a_1, a_2, ... , a_n) =  a_1 + a_2 + ... + a_n
 */
struct SumDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(index < n_formal_arguments);
        return ConstantExpression::make(1.0);
    }
};

//---------------------

struct AbsDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct InvDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return ProductExpression::make(ConstantExpression::make(-1.0), InvExpression::make(SqExpression::make(formal_argument.clone())));
    }
};

struct SqDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return ProductExpression::make(ConstantExpression::make(2.0), formal_argument.clone());
    }
};

struct CbDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return ProductExpression::make(ConstantExpression::make(3.0), SqExpression::make(formal_argument.clone()));
    }
};

//---------------------

struct SinDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return CosExpression::make(formal_argument.clone());
    }
};

struct CosDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return ProductExpression::make(ConstantExpression::make(-1.0), SinExpression::make(formal_argument.clone()));
    }
};

struct TanDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return InvExpression::make(SqExpression::make(CosExpression::make(formal_argument.clone())));
    }
};

struct AsinDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return InvExpression::make(SqrtExpression::make(SumExpression::make(ConstantExpression::make(1.0), ProductExpression::make(ConstantExpression::make(-1.0), SqExpression::make(formal_argument.clone())))));
    }
};

struct AcosDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        ExpressionHandler asin_derivative = AsinDerivativeExpressionMaker{}.make(0u, formal_arguments);
        return ProductExpression::make(ConstantExpression::make(-1.0), asin_derivative);
    }
};

struct AtanDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return InvExpression::make(SumExpression::make(ConstantExpression::make(1.0), SqExpression::make(formal_argument.clone())));
    }
};

//---------------------

struct SinhDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct CoshDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct TanhDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct AsinhDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct AcoshDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct AtanhDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

//---------------------

struct ExpDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        return ExpExpression::make(formal_argument.clone());
    }
};

struct LogDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct Log10DerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct Exp2DerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct Expm1DerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct Log1pDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct Log2DerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

//---------------------

struct SqrtDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

struct CbrtDerivativeExpressionMaker {
    template<class FomalArgumentExpressionsRange>
    ExpressionHandler make(const unsigned index, const FomalArgumentExpressionsRange& formal_arguments) {
        const auto n_formal_arguments = boost::size(formal_arguments);
        assert(n_formal_arguments == 1);
        assert(index == 0);
        //const ExpressionHandler& formal_argument = *std::begin(formal_arguments);
        throw std::runtime_error("NOT IMPLEMENTED.");
    }
};

}

namespace symbolic_algebra {

template<class SubExpressionsRange, class DerivativeExpressionMaker>
ExpressionHandler apply_chain_rule_helper(const unsigned index, const SubExpressionsRange& subexpressions, DerivativeExpressionMaker derivative_expression_maker) {
    // const auto n_subexpressions = boost::size(subexpressions);
    // TODO: one-subexpresion optimization.
    ExpressionHandlerVector new_subexpressions;
    for (const auto& outer_function_subexpression_indexed : subexpressions | boost::adaptors::indexed(0)) {
        ExpressionHandler outer_function_derrivative = derivative_expression_maker.make(outer_function_subexpression_indexed.index(), subexpressions);
        ExpressionHandler inner_function_derrivative = calculate_derivative_expression(outer_function_subexpression_indexed.value(), index);
        new_subexpressions.push_back(ProductExpression::make(std::move(outer_function_derrivative), std::move(inner_function_derrivative)));
    }
    return SumExpression::make_from_buffer(std::move(new_subexpressions));
}


inline ExpressionHandler calculate_derivative_expression(const ExpressionHandler& expression_handler, const unsigned index) {
    if (const auto& casted_expression = expression_handler.casted_target<ConstantExpression>()) {
        return ConstantExpression::make(0.0); //or: SumExpression::make_zero();
    } else if (const auto& casted_expression = expression_handler.casted_target<VariableExpression>()) {
        const auto var_index = casted_expression.unwrap().get().index();
        return (var_index == index ? ConstantExpression::make(1.0) : ConstantExpression::make(0.0));
    } else if (const auto& casted_expression = expression_handler.casted_target<RealFactoredExpression>()) {
        const auto factor = casted_expression.unwrap().get().factor();
        auto subexpression_derivative = calculate_derivative_expression(expression_handler.subexpression(0), index);
        return RealFactoredExpression::make(factor, std::move(subexpression_derivative));
    } else if (const auto& casted_expression = expression_handler.casted_target<SumExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::SumDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<ProductExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::ProductDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<AbsExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::AbsDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<InvExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::InvDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<SqExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::SqDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<CbExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::CbDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<SinExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::SinDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<CosExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::CosDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<TanExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::TanDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<AsinExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::AsinDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<AcosExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::AcosDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<AtanExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::AtanDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<SinhExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::SinhDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<CoshExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::CoshDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<TanhExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::TanhDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<AsinhExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::AsinhDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<AcoshExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::AcoshDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<AtanhExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::AtanhDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<ExpExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::ExpDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<LogExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::LogDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<Log10Expression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::Log10DerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<Exp2Expression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::Exp2DerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<LogExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::Expm1DerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<Log1pExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::Log1pDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<Log2Expression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::Log2DerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<SqrtExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::SqrtDerivativeExpressionMaker{});
    } else if (const auto& casted_expression = expression_handler.casted_target<CbrtExpression>()) {
        return apply_chain_rule_helper(index, expression_handler.crange(), derivatives_table::CbrtDerivativeExpressionMaker{});
    }

    throw std::runtime_error("No receipt for expression derivative calculation for expression `" + expression_handler.str() + "`.");
}

}

#endif
