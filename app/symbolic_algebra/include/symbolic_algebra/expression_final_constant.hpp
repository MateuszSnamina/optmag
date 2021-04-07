#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_CONCRETE_CONSTANT_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_CONCRETE_CONSTANT_HPP

#include <symbolic_algebra/expression_abstract_common.hpp>

#include<sstream>

// **********************************************************
// ***  ConstatnExpression                                ***
// **********************************************************

namespace symbolic_algebra {

class ConstantExpression final : public LeafExpression {
public:
    // copy semantic:
    ConstantExpression(const ConstantExpression&) = delete;
    ConstantExpression& operator=(const ConstantExpression&) = delete;
    // move semantic:
    ConstantExpression(ConstantExpression&&) = delete;
    ConstantExpression& operator=(ConstantExpression&&) = default;
    // creation model:
    static ExpressionHandler make(double value);
    static ExpressionHandler make_zero();
    static ExpressionHandler make_one();
    // other member functions:
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    double value() const;
    bool is_zero() const;
    bool is_one() const;
private:
    // ctor:
    explicit ConstantExpression(double) noexcept;
private:
    std::unique_ptr<ConstantExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);
private:
    double _value;
};

inline ConstantExpression::ConstantExpression(double value) noexcept
    : _value(value) {
}

inline double ConstantExpression::value() const {
    return _value;
}

inline ExpressionHandler ConstantExpression::make(double value) {
    return ExpressionHandler::make<ConstantExpression>(value);
}

inline ExpressionHandler ConstantExpression::make_zero() {
    return ExpressionHandler::make<ConstantExpression>(0.0);
}

inline ExpressionHandler ConstantExpression::make_one() {
    return ExpressionHandler::make<ConstantExpression>(1.0);
}

inline std::unique_ptr<ConstantExpression> ConstantExpression::casted_clone() const {
    return std::unique_ptr<ConstantExpression>(new ConstantExpression(value()));
}

inline ExpressionHandler ConstantExpression::clone() const {
    return ExpressionHandler::make<ConstantExpression>(value());
}

inline bool ConstantExpression::equals(const Expression& other) const {
    const auto casted_other = dynamic_cast<const ConstantExpression*>(&other);
    return casted_other && (value() == casted_other->value());
}

inline std::string ConstantExpression::str() const {
    std::ostringstream out;
    out << value();
    return out.str();
    //return std::to_string(value());
}

inline std::string ConstantExpression::repr() const {
    return "ConstantExpression(" + std::to_string(value()) + ")";
}

inline bool  ConstantExpression::is_zero() const {
    return value() == 0.0;
}

inline bool  ConstantExpression::is_one() const {
    return value() == 1.0;
}

}  // namespace symbolic_algebra

#endif
