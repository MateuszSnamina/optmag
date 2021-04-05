#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_CONCRETE_VARIALBE_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_CONCRETE_VARIALBE_HPP

#include <symbolic_algebra/expression_abstract_common.hpp>

// **********************************************************
// ***  VariableExpression                                ***
// **********************************************************

namespace symbolic_algebra {

class VariableExpression final : public LeafExpression {
public:
    // copy semantic:
    VariableExpression(const VariableExpression&) = delete;
    VariableExpression& operator=(const VariableExpression&) = delete;
    // move semantic:
    VariableExpression(VariableExpression&&) = delete;
    VariableExpression& operator=(VariableExpression&&) = default;
    // creation model:
    static ExpressionHandler make(unsigned index);
    // other member functions:
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    unsigned index() const;
private:
    // ctor:
    explicit VariableExpression(unsigned) noexcept;
private:
    std::unique_ptr<VariableExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);
private:
    unsigned _index;
};

inline VariableExpression::VariableExpression(unsigned index) noexcept
    : _index(index) {
}

inline unsigned VariableExpression::index() const {
    return _index;
}

inline ExpressionHandler VariableExpression::make(unsigned index) {
    return ExpressionHandler::make<VariableExpression>(index);
}

inline std::unique_ptr<VariableExpression> VariableExpression::casted_clone() const {
    return std::unique_ptr<VariableExpression>(new VariableExpression(index()));
}

inline ExpressionHandler VariableExpression::clone() const {
    return ExpressionHandler::make<VariableExpression>(index());
}

inline bool VariableExpression::equals(const Expression& other) const {
    const auto casted_other = dynamic_cast<const VariableExpression*>(&other);
    return casted_other && (index() == casted_other->index());
}

inline std::string VariableExpression::str() const {
    return "x_" + std::to_string(index());
}

inline std::string VariableExpression::repr() const {
    return "VariableExpression(" + std::to_string(index()) + ")";
}

}  // namespace symbolic_algebra

#endif
