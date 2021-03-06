#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_FINAL_UNARY_FUNCTIONS_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_FINAL_UNARY_FUNCTIONS_HPP

#include <symbolic_algebra/expression_abstract_common.hpp>

#include<string>

// **********************************************************
// ***  UnaryFunctionExpression                           ***
// **********************************************************

namespace symbolic_algebra {

class UnaryFunctionExpression : public BridgeExpression {
public:
    // copy semantic:
    UnaryFunctionExpression(const UnaryFunctionExpression&) = delete;
    UnaryFunctionExpression& operator=(const UnaryFunctionExpression&) = delete;
    // move semantic:
    UnaryFunctionExpression(UnaryFunctionExpression&&) = delete;
    UnaryFunctionExpression& operator=(UnaryFunctionExpression&&) = default;
    // other member functions:
    virtual double eval(double) const = 0;
protected:
    UnaryFunctionExpression(ExpressionHandler&& expr_hdl) noexcept;
};

inline UnaryFunctionExpression::UnaryFunctionExpression(ExpressionHandler&& expr_hdl) noexcept
    : BridgeExpression(std::move(expr_hdl)) {
}

}  // namespace symbolic_algebra

// **********************************************************
// ***  FunctionObjectComparator                          ***
// **********************************************************

namespace symbolic_algebra {

template<class T>
struct FunctionObjectComparator {
    bool compare(const T&, const T&) const {
        // std::cout << "Generic comparator => return false" << std::endl;
        return false;
    }
};

template<>
struct FunctionObjectComparator<double(*)(double)> {
    using FunctionPointer = double(*)(double);
    bool compare(const FunctionPointer& lhs, const FunctionPointer& rhs) const {
        // std::cout << "lhs : " << lhs << std::endl;
        // std::cout << "rhs : " << rhs << std::endl;
        // std::cout << "Specialized comparator => return " << (lhs == rhs) << std::endl;
        return lhs == rhs;
    }
};

}  // namespace symbolic_algebra

// **********************************************************
// ***  UnaryFunctionExpressionDynamic                    ***
// **********************************************************

namespace symbolic_algebra {

// For using string as template param, ref here:
// https://stackoverflow.com/questions/1826464/c-style-strings-as-template-arguments

/*
 * UnaryFunctionT may be:
 * - `doube(*)(doube)`,
 * - `<lambda type>` for `double(double)` function,
 * - `std::function<double(double)>`,
 * - any custom callable object, with `double CustomType::operator()(double) const` defined.
 *
 * Note: the UnaryFunctionExpressionDynamic comparison
 * `UnaryFunctionExpressionDynamic<...>::equals(const Expression& other)`
 * is defined as follow:
 * - `UnaryFunctionExpressionDynamic<...>` with `UnaryFunctionT := doube(*)(doube)`
 *   compares the underlying pointers,
 * - with other `UnaryFunctionT` the comparson always returns `false`.
 * The function name is not taken into account in comparison.
 *
 * The comparison logic may be perceived as a flaw.
 * Do not be suprrised that an UnaryFunctionT instance
 * is not equal to its clone.
 *
 * The UnaryFunctionT works really good with `UnaryFunctionT := doube(*)(doube)`.
 *
 */

template<const char** name, class UnaryFunctionT>
class UnaryFunctionExpressionDynamic final : public UnaryFunctionExpression {
    using UnaryFunction = UnaryFunctionT;
public:
    // copy semantic:
    UnaryFunctionExpressionDynamic(const UnaryFunctionExpressionDynamic&) = delete;
    UnaryFunctionExpressionDynamic& operator=(const UnaryFunctionExpressionDynamic&) = delete;
    // move semantic:
    UnaryFunctionExpressionDynamic(UnaryFunctionExpressionDynamic&&) = delete;
    UnaryFunctionExpressionDynamic& operator=(UnaryFunctionExpressionDynamic&&) = default;
    // creation model:
    static ExpressionHandler make(UnaryFunctionT function, ExpressionHandler&& expr_hdl);
    // other member functions:
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    double eval(double) const override;
    const UnaryFunction& function() const;
    std::string function_name() const;
private:
    UnaryFunctionExpressionDynamic(UnaryFunctionT function, ExpressionHandler&& expr_hdl) noexcept;
    std::unique_ptr<UnaryFunctionExpressionDynamic<name, UnaryFunctionT>> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);
private:
    const UnaryFunctionT _function;
};

template<const char** name, class UnaryFunctionT>
UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::UnaryFunctionExpressionDynamic(UnaryFunctionT function, ExpressionHandler&& expr_hdl) noexcept
    : UnaryFunctionExpression(std::move(expr_hdl)), _function(function) {
}

template<const char** name, class UnaryFunctionT>
ExpressionHandler UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::make(UnaryFunctionT function, ExpressionHandler&& expr_hdl) {
    return ExpressionHandler::make<UnaryFunctionExpressionDynamic>(function, std::move(expr_hdl));
}

template<const char** name, class UnaryFunctionT>
std::unique_ptr<UnaryFunctionExpressionDynamic<name, UnaryFunctionT>> UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::casted_clone() const {
    using SelfT = UnaryFunctionExpressionDynamic<name, UnaryFunctionT>;
    return std::unique_ptr<SelfT>(new SelfT(_function, subexpression(0).clone()));
}

template<const char** name, class UnaryFunctionT>
ExpressionHandler UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::clone() const {
    using SelfT = UnaryFunctionExpressionDynamic<name, UnaryFunctionT>;
    return ExpressionHandler::make<SelfT>(_function, subexpression(0).clone());
}

template<const char** name, class UnaryFunctionT>
bool UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::equals(const Expression& other) const {
    using SelfT = UnaryFunctionExpressionDynamic<name, UnaryFunctionT>;
    const auto casted_other_ptr = dynamic_cast<const SelfT*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    if (!FunctionObjectComparator<UnaryFunctionT>{}.compare(_function, casted_other._function)) {
        return false;
    }
    if (!subexpression(0).equals(other.subexpression(0))) {
        return false;
    }
    return true;
}

template<const char** name, class UnaryFunctionT>
std::string UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::str() const {
    return function_name() + "???" + subexpression(0).target().str() + "???";
}

template<const char** name, class UnaryFunctionT>
std::string UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::repr() const {
    return "UnaryFunction(" + function_name() + ";" + subexpression(0).target().repr() + ")";
}

template<const char** name, class UnaryFunctionT>
double UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::eval(double x) const {
    return _function(x);
}

template<const char** name, class UnaryFunctionT>
const UnaryFunctionT& UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::function() const {
    return _function;
}

template<const char** name, class UnaryFunctionT>
std::string UnaryFunctionExpressionDynamic<name, UnaryFunctionT>::function_name() const {
    return std::string(*name);
}

}  // namespace symbolic_algebra


// **********************************************************
// ***  UnaryFunctionStaticExpression                     ***
// **********************************************************

namespace symbolic_algebra {

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
class UnaryFunctionStaticExpression final : public UnaryFunctionExpression {
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
    double eval(double) const override;
    const UnaryFunction function() const;
    std::string function_name() const;

private:
    UnaryFunctionStaticExpression(ExpressionHandler&& expr_hdl) noexcept;
    std::unique_ptr<UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);
};

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::UnaryFunctionStaticExpression(ExpressionHandler&& expr_hdl) noexcept
    : UnaryFunctionExpression(std::move(expr_hdl)) {
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
    return function_name() + "???" + subexpression(0).target().str() + "???";
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
std::string UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::repr() const {
    return "UnaryFunction(" + function_name() + ";" + subexpression(0).target().repr() + ")";
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
double UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::eval(double x) const {
    return functionStatic(x);
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
const UnaryFunctionT UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::function() const {
    return functionStatic;
}

template<const char** name, class UnaryFunctionT, UnaryFunctionT functionStatic>
std::string UnaryFunctionStaticExpression<name, UnaryFunctionT, functionStatic>::function_name() const {
    return std::string(*name);
}

}  // namespace symbolic_algebra

#endif
