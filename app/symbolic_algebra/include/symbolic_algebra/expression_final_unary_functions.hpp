#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_FINAL_UNARY_FUNCTIONS_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_FINAL_UNARY_FUNCTIONS_HPP

#include <symbolic_algebra/expression_abstract_common.hpp>

#include<string>

// **********************************************************
// ***  UnaryFunctionExpression                           ***
// **********************************************************

namespace symbolic_algebra {

// For using string as template param, ref here:
// https://stackoverflow.com/questions/1826464/c-style-strings-as-template-arguments

template<const char** name, class UnaryFunctionT>
class UnaryFunctionExpression final : public BridgeExpression {
    using UnaryFunction = UnaryFunctionT;
public:
    // copy semantic:
    UnaryFunctionExpression(const UnaryFunctionExpression&) = delete;
    UnaryFunctionExpression& operator=(const UnaryFunctionExpression&) = delete;
    // move semantic:
    UnaryFunctionExpression(UnaryFunctionExpression&&) = delete;
    UnaryFunctionExpression& operator=(UnaryFunctionExpression&&) = default;
    // creation model:
    static ExpressionHandler make(UnaryFunctionT function, ExpressionHandler&& expr_hdl);
    // other member functions:
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    const UnaryFunction& function() const;
    std::string function_name() const;

private:
    UnaryFunctionExpression(UnaryFunctionT function, ExpressionHandler&& expr_hdl) noexcept;
    std::unique_ptr<UnaryFunctionExpression<name, UnaryFunctionT>> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);

private:
    UnaryFunctionT _function;
};

template<const char** name, class UnaryFunctionT>
UnaryFunctionExpression<name, UnaryFunctionT>::UnaryFunctionExpression(UnaryFunctionT function, ExpressionHandler&& expr_hdl) noexcept
    : BridgeExpression(std::move(expr_hdl)), _function(function) {
}

template<const char** name, class UnaryFunctionT>
ExpressionHandler UnaryFunctionExpression<name, UnaryFunctionT>::make(UnaryFunctionT function, ExpressionHandler&& expr_hdl) {
    return ExpressionHandler::make<UnaryFunctionExpression>(function, std::move(expr_hdl));
}

template<const char** name, class UnaryFunctionT>
std::unique_ptr<UnaryFunctionExpression<name, UnaryFunctionT>> UnaryFunctionExpression<name, UnaryFunctionT>::casted_clone() const {
    using SelfT = UnaryFunctionExpression<name, UnaryFunctionT>;
    return std::unique_ptr<SelfT>(new SelfT(_function, subexpression(0).clone()));
}

template<const char** name, class UnaryFunctionT>
ExpressionHandler UnaryFunctionExpression<name, UnaryFunctionT>::clone() const {
    using SelfT = UnaryFunctionExpression<name, UnaryFunctionT>;
    return ExpressionHandler::make<SelfT>(_function, subexpression(0).clone());
}

template<const char** name, class UnaryFunctionT>
bool UnaryFunctionExpression<name, UnaryFunctionT>::equals(const Expression& other) const {
    using SelfT = UnaryFunctionExpression<name, UnaryFunctionT>;
    const auto casted_other_ptr = dynamic_cast<const SelfT*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    if (std::addressof(_function) != std::addressof(casted_other._function)) {
        return false;
    }
    if (!subexpression(0).equals(other.subexpression(0))) {
        return false;
    }
    return true;
}

template<const char** name, class UnaryFunctionT>
std::string UnaryFunctionExpression<name, UnaryFunctionT>::str() const {
    return function_name() + "⦗" + subexpression(0).target().str() + "⦘";
}

template<const char** name, class UnaryFunctionT>
std::string UnaryFunctionExpression<name, UnaryFunctionT>::repr() const {
    return "UnaryFunction(" + function_name() + ";" + subexpression(0).target().repr() + ")";
}

template<const char** name, class UnaryFunctionT>
const UnaryFunctionT& UnaryFunctionExpression<name, UnaryFunctionT>::function() const {
    return _function;
}

template<const char** name, class UnaryFunctionT>
std::string UnaryFunctionExpression<name, UnaryFunctionT>::function_name() const {
    return std::string(*name);
}

}  // namespace symbolic_algebra


// **********************************************************
// ***  UnaryFunctionStaticExpression                     ***
// **********************************************************

namespace symbolic_algebra {

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
class UnaryFunctionStaticExpression final : public BridgeExpression {
    using UnaryFunction = UnaryFunctionT;
public:
    // copy semantic:
    UnaryFunctionStaticExpression(const UnaryFunctionStaticExpression&) = delete;
    UnaryFunctionStaticExpression& operator=(const UnaryFunctionStaticExpression&) = delete;
    // move semantic:
    UnaryFunctionStaticExpression(UnaryFunctionStaticExpression&&) = delete;
    UnaryFunctionStaticExpression& operator=(UnaryFunctionStaticExpression&&) = default;
    // creation model:
    static ExpressionHandler make(ExpressionHandler&& expr_hdl);
    // other member functions:
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    const UnaryFunction& function() const;
    std::string function_name() const;

private:
    UnaryFunctionStaticExpression(ExpressionHandler&& expr_hdl) noexcept;
    std::unique_ptr<UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);
};

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::UnaryFunctionStaticExpression(ExpressionHandler&& expr_hdl) noexcept
    : BridgeExpression(std::move(expr_hdl)) {
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
ExpressionHandler UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::make(ExpressionHandler&& expr_hdl) {
    using SelfT = UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>;
    return ExpressionHandler::make<SelfT>(std::move(expr_hdl));
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
std::unique_ptr<UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>>
UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::casted_clone() const {
    using SelfT = UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>;
    return std::unique_ptr<SelfT>(new SelfT(subexpression(0).clone()));
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
ExpressionHandler UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::clone() const {
    using SelfT = UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>;
    return ExpressionHandler::make<SelfT>(subexpression(0).clone());
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
bool UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::equals(const Expression& other) const {
    using SelfT = UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>;
    if (!dynamic_cast<const SelfT*>(&other)) {
        return false;
    }
    if (!subexpression(0).equals(other.subexpression(0))) {
        return false;
    }
    return true;
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
std::string UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::str() const {
    return function_name() + "⦗" + subexpression(0).target().str() + "⦘";
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
std::string UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::repr() const {
    return "UnaryFunction(" + function_name() + ";" + subexpression(0).target().repr() + ")";
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
const UnaryFunctionT& UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::function() const {
    return function;
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
std::string UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::function_name() const {
    return std::string(*name);
}

}  // namespace symbolic_algebra

#endif
