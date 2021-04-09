#ifndef CONSTRAINED_OPTIMIZER_OPTIMIZER_HPP
#define CONSTRAINED_OPTIMIZER_OPTIMIZER_HPP

// SYMBOLIC_ALGEBRA:
#include <symbolic_algebra/expression_abstract.hpp>
// STL:
#include <vector>
// ARMA:
#include<armadillo>
// STD:
#include <optional>
#include <variant>
#include <stdexcept>
#include <iterator>
#include <algorithm>

// **********************************************************
// ***  OptimizationProblemDefinitionBuilder              ***
// **********************************************************

namespace constrained_optimizer {

class OptimizationProblemDefinition;

class OptimizationProblemDefinitionBuilder {
public:
    OptimizationProblemDefinitionBuilder& set_n_variables(unsigned n_variables){
        assert(!_n_variables);
        _n_variables = n_variables;
        _variables_scale = arma::vec(n_variables, arma::fill::ones);
        return *this;
    }
    OptimizationProblemDefinitionBuilder& set_variables_scale(arma::vec variables_scale){
        assert(variables_scale.n_rows == _n_variables);
        _variables_scale = variables_scale;
        return *this;
    }
    OptimizationProblemDefinitionBuilder& set_loss_function(symbolic_algebra::ExpressionHandler loss_function) {
        _loss_function = std::move(loss_function);
        return *this;
    }
    OptimizationProblemDefinitionBuilder& set_loss_function_deivatives(symbolic_algebra::ExpressionHandlerVector& loss_function_deivatives) {
        assert(loss_function_deivatives.size() == _n_variables);
        _loss_function_deivatives = symbolic_algebra::ExpressionHandlerVector{};
        std::move(std::begin(loss_function_deivatives),
                  std::end(loss_function_deivatives),
                  std::back_insert_iterator<symbolic_algebra::ExpressionHandlerVector>(*_loss_function_deivatives));
        return *this;
    }
    OptimizationProblemDefinitionBuilder& set_constraint_function(symbolic_algebra::ExpressionHandler constraint_function) {
        _constraint_function = std::move(constraint_function);
        return *this;
    }
    OptimizationProblemDefinitionBuilder& set_constraint_function_deivatives(symbolic_algebra::ExpressionHandlerVector& constraint_function_deivatives) {
        assert(constraint_function_deivatives.size() == _n_variables);
        _constraint_function_deivatives = symbolic_algebra::ExpressionHandlerVector{};
        std::move(std::begin(constraint_function_deivatives),
                  std::end(constraint_function_deivatives),
                  std::back_insert_iterator<symbolic_algebra::ExpressionHandlerVector>(*_constraint_function_deivatives));
        return *this;
    }
    OptimizationProblemDefinition build();
private:
    std::optional<unsigned> _n_variables;
    std::optional<arma::vec> _variables_scale;
    std::optional<symbolic_algebra::ExpressionHandler> _loss_function;
    std::optional<symbolic_algebra::ExpressionHandlerVector> _loss_function_deivatives;
    std::optional<symbolic_algebra::ExpressionHandler> _constraint_function;
    std::optional<symbolic_algebra::ExpressionHandlerVector> _constraint_function_deivatives;
};

class OptimizationProblemDefinition {
public:
    const unsigned _n_variables;
    const arma::vec _variables_scale;
    const symbolic_algebra::ExpressionHandler _loss_function;
    symbolic_algebra::ExpressionHandlerVector _loss_function_deivatives;
    const symbolic_algebra::ExpressionHandler _constraint_function;
    symbolic_algebra::ExpressionHandlerVector _constraint_function_deivatives;
private:
    OptimizationProblemDefinition(unsigned n_variables,
                                  const arma::vec& variables_scale,
                                  symbolic_algebra::ExpressionHandler loss_function,
                                  symbolic_algebra::ExpressionHandlerVector& loss_function_deivatives,
                                  symbolic_algebra::ExpressionHandler constraint_function,
                                  symbolic_algebra::ExpressionHandlerVector& constraint_function_deivatives) :
        _n_variables(n_variables),
        _variables_scale(variables_scale),
        _loss_function(std::move(loss_function)),
        _constraint_function(std::move(constraint_function)) {
        assert(variables_scale.n_rows == n_variables);
        assert(loss_function_deivatives.size() == n_variables);
        assert(constraint_function_deivatives.size() == n_variables);
        std::move(std::begin(loss_function_deivatives),
                  std::end(loss_function_deivatives),
                  std::back_insert_iterator<symbolic_algebra::ExpressionHandlerVector>(_loss_function_deivatives));
        std::move(std::begin(constraint_function_deivatives),
                  std::end(constraint_function_deivatives),
                  std::back_insert_iterator<symbolic_algebra::ExpressionHandlerVector>(_constraint_function_deivatives));
    }
    friend OptimizationProblemDefinition OptimizationProblemDefinitionBuilder::build();
};

inline OptimizationProblemDefinition OptimizationProblemDefinitionBuilder::build() {
    if (!_n_variables) {
        throw std::runtime_error("Can not build OptimizationProblemDefinition as `n_variables` is not set.");
    }
    if (!_variables_scale) {
        throw std::runtime_error("Can not build OptimizationProblemDefinition as `_variables_scale` is not set.");
    }
    if (!_loss_function) {
        throw std::runtime_error("Can not build OptimizationProblemDefinition as `_loss_function` is not set.");
    }
    if (!_loss_function_deivatives) {
        throw std::runtime_error("Can not build OptimizationProblemDefinition as `_loss_function_deivatives` is not set.");
    }
    if (!_constraint_function) {
        throw std::runtime_error("Can not build OptimizationProblemDefinition as `_constraint_function` is not set.");
    }
    if (!_constraint_function_deivatives) {
        throw std::runtime_error("Can not build OptimizationProblemDefinition as `_constraint_function_deivatives` is not set.");
    }

    return OptimizationProblemDefinition(*_n_variables,
                                         *_variables_scale,
                                         std::move(*_loss_function),
                                         *_loss_function_deivatives ,
                                         std::move(*_constraint_function),
                                         *_constraint_function_deivatives);
}

}  // namespace constrained_optimizer

// **********************************************************
// ***  SqpParams                                         ***
// **********************************************************

namespace constrained_optimizer {

class SqpParams;

class SqpParamsBuilder {
public:
    SqpParams build() const;
private:
};

class SqpParams {
private:
    SqpParams();
    friend SqpParams SqpParamsBuilder::build() const;
};

inline SqpParams::SqpParams() {
}

inline SqpParams SqpParamsBuilder::build() const {
    return SqpParams{};
}

}  // namespace constrained_optimizer

// **********************************************************
// ***  AulParams                                         ***
// **********************************************************

namespace constrained_optimizer {

class AulParams;

class AulParamsBuilder {
public:
    AulParams build() const;
private:
};

class AulParams {
public:

private:
    AulParams();
    friend AulParams AulParamsBuilder::build() const;
};

inline AulParams::AulParams() {
}

inline AulParams AulParamsBuilder::build() const {
    return AulParams{};
}

}  // namespace constrained_optimizer

// **********************************************************
// ***  SlpParams                                         ***
// **********************************************************

namespace constrained_optimizer {

class SlpParams;

class SlpParamsBuilder {
public:
    SlpParams build() const;
private:
};

class SlpParams {
private:
    SlpParams();
    friend SlpParams SlpParamsBuilder::build() const;
};

inline SlpParams::SlpParams() {
}

inline SlpParams SlpParamsBuilder::build() const {
    return SlpParams{};
}

}  // namespace constrained_optimizer

// **********************************************************
// ***  OptimizationProblemDefinitionBuilder              ***
// **********************************************************

namespace constrained_optimizer {

using OptimizationMethodParams = std::variant<SqpParams, AulParams, SlpParams>;

arma::vec optimize(
        const OptimizationProblemDefinition&,
        const arma::vec& x0,
        const OptimizationMethodParams&,
        bool optguard = true);

}  // namespace constrained_optimizer

#endif
