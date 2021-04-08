#ifndef CONSTRAINED_OPTIMIZER_OPTIMIZER_HPP
#define CONSTRAINED_OPTIMIZER_OPTIMIZER_HPP

// SYMBOLIC_ALGEBRA:
#include <symbolic_algebra/expression_abstract.hpp>
// STL:
#include <vector>
// STD:
#include <optional>
#include <variant>
#include <stdexcept>
#include <iterator>
#include <algorithm>

namespace constrained_optimizer {

class OptimizationProblemDefinition;

// **********************************************************
// ***  OptimizationProblemDefinitionBuilder              ***
// **********************************************************

class OptimizationProblemDefinitionBuilder {
public:
    void set_n_variables(unsigned n_variables){
        _n_variables = n_variables;
    }
    void set_loss_function(symbolic_algebra::ExpressionHandler loss_function) {
        _loss_function = std::move(loss_function);
    }
    void set_loss_function_deivatives(symbolic_algebra::ExpressionHandlerVector& loss_function_deivatives) {
        _loss_function_deivatives = symbolic_algebra::ExpressionHandlerVector{};
        std::move(std::begin(loss_function_deivatives),
                  std::end(loss_function_deivatives),
                  std::back_insert_iterator<symbolic_algebra::ExpressionHandlerVector>(*_loss_function_deivatives));
    }
    //    void set_constraint_function(symbolic_algebra::ExpressionHandler constraint_function) {
    //        _constraint_function = std::move(constraint_function);
    //    }
    //    void set_constraint_function_deivatives(symbolic_algebra::ExpressionHandlerVector& constraint_function_deivatives) {
    //        _constraint_function_deivatives = constraint_function_deivatives;
    //    }
    OptimizationProblemDefinition build();
private:
    std::optional<unsigned> _n_variables;
    std::optional<symbolic_algebra::ExpressionHandler> _loss_function;
    std::optional<symbolic_algebra::ExpressionHandlerVector> _loss_function_deivatives;
    std::optional<symbolic_algebra::ExpressionHandler> _constraint_function;
    std::optional<symbolic_algebra::ExpressionHandlerVector> _constraint_function_deivatives;
};

class OptimizationProblemDefinition {
public:
    const unsigned _n_variables;
    const symbolic_algebra::ExpressionHandler _loss_function;
    symbolic_algebra::ExpressionHandlerVector _loss_function_deivatives;
    const symbolic_algebra::ExpressionHandler _constraint_function;
    symbolic_algebra::ExpressionHandlerVector _constraint_function_deivatives;
private:
    OptimizationProblemDefinition(unsigned n_variables,
                                  symbolic_algebra::ExpressionHandler loss_function,
                                  symbolic_algebra::ExpressionHandlerVector& loss_function_deivatives ,
                                  symbolic_algebra::ExpressionHandler constraint_function,
                                  symbolic_algebra::ExpressionHandlerVector& constraint_function_deivatives) :
        _n_variables(n_variables),
        _loss_function(std::move(loss_function)),
        _constraint_function(std::move(constraint_function)) {
        std::move(std::begin(loss_function_deivatives),
                  std::end(loss_function_deivatives),
                  std::back_insert_iterator<symbolic_algebra::ExpressionHandlerVector>(_loss_function_deivatives));
        std::move(std::begin(constraint_function_deivatives),
                  std::end(constraint_function_deivatives),
                  std::back_insert_iterator<symbolic_algebra::ExpressionHandlerVector>(_constraint_function_deivatives));
    }
    friend OptimizationProblemDefinition OptimizationProblemDefinitionBuilder::build();
};

OptimizationProblemDefinition OptimizationProblemDefinitionBuilder::build() {
    if (!_n_variables) {
        throw std::runtime_error("Can not build OptimizationProblemDefinition as `n_variables` is not set.");
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
                                         std::move(*_loss_function),
                                         *_loss_function_deivatives ,
                                         std::move(*_constraint_function),
                                         *_constraint_function_deivatives);
}




// **********************************************************
// ***  SqpParams                                         ***
// **********************************************************

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

// **********************************************************
// ***  AulParams                                         ***
// **********************************************************

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


// **********************************************************
// ***  SlpParams                                         ***
// **********************************************************

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

// **********************************************************
// ***  OptimizationProblemDefinitionBuilder              ***
// **********************************************************

using OptimizationMethodParams = std::variant<SqpParams, AulParams, SlpParams>;

void optimize(OptimizationProblemDefinition, OptimizationMethodParams, bool optguard = true);

}  // namespace constrained_optimizer

#endif
