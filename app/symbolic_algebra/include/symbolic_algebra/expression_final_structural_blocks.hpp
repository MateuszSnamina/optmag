#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_STRUCTURAL_BLOCKS_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_STRUCTURAL_BLOCKS_HPP

#include <symbolic_algebra/expression_abstract_common.hpp>

// References:
// (1) list-of-all-unicodes-open-close-brackets:
// https://stackoverflow.com/questions/13535172/list-of-all-unicodes-open-close-brackets

// ##########################################################
// ###########  StructuralBlockExpressions   ################
// ##########################################################

// **********************************************************
// ***  IntegerFactoredExpression                         ***
// **********************************************************

namespace symbolic_algebra {

class RealFactoredExpression final : public BridgeExpression {
   public:
    // copy semantic:
    RealFactoredExpression(const RealFactoredExpression&) = delete;
    RealFactoredExpression& operator=(const RealFactoredExpression&) = delete;
    // move semantic:
    RealFactoredExpression(RealFactoredExpression&&) = delete;
    RealFactoredExpression& operator=(RealFactoredExpression&&) = default;
    // creation model:
    static ExpressionHandler make(double factor, ExpressionHandler&& expr_hdl);
    // other member functions:
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    double factor() const;

   private:
    RealFactoredExpression(double factor, ExpressionHandler&& expr_hdl) noexcept;
    std::unique_ptr<RealFactoredExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);

   private:
    double _factor;
};

inline RealFactoredExpression::RealFactoredExpression(double factor, ExpressionHandler&& expr_hdl) noexcept
    : BridgeExpression(std::move(expr_hdl)), _factor(factor) {
}

inline ExpressionHandler RealFactoredExpression::make(double factor, ExpressionHandler&& expr_hdl) {
    return ExpressionHandler::make<RealFactoredExpression>(factor, std::move(expr_hdl));
}

inline std::unique_ptr<RealFactoredExpression> RealFactoredExpression::casted_clone() const {
    return std::unique_ptr<RealFactoredExpression>(new RealFactoredExpression(_factor, subexpression(0).clone()));
}

inline ExpressionHandler RealFactoredExpression::clone() const {
    return ExpressionHandler::make<RealFactoredExpression>(_factor, subexpression(0).clone());
}

inline bool RealFactoredExpression::equals(const Expression& other) const {
    const auto casted_other_ptr = dynamic_cast<const RealFactoredExpression*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    if (_factor != casted_other._factor) {
        return false;
    }
    if (!subexpression(0).equals(other.subexpression(0))) {
        return false;
    }
    return true;
}

inline std::string RealFactoredExpression::str() const {
    auto fancy_to_string = [](auto _) -> std::string {
        if (_ == +1.0) {
            return "+";
        }
        if (_ == -1.0) {
            return "-";
        }
        return std::to_string(_);
    };
    return "❪" + fancy_to_string(_factor) + subexpression(0).target().str() + "❫"; // TODO consider: "•"
}

inline std::string RealFactoredExpression::repr() const {
    return "RealFactor(" + std::to_string(_factor) + "," + subexpression(0).target().repr() + ")";
}

inline double RealFactoredExpression::factor() const {
    return _factor;
}

}  // namespace symbolic_algebra

// **********************************************************
// ***  ProductExpression                                 ***
// **********************************************************

namespace symbolic_algebra {

class ProductExpression final : public VectorNumerousExpression {
   public:
    // copy semantic:
    ProductExpression(const ProductExpression&) = delete;
    ProductExpression& operator=(const ProductExpression&) = delete;
    // move semantic:
    ProductExpression(ProductExpression&&) = delete;
    ProductExpression& operator=(ProductExpression&&) = default;
    // creation model:
    static ExpressionHandler make_from_buffer(ExpressionHandlerVector&& expr_hdls);
    template <class... Args>
    static ExpressionHandler make(Args&&... expr_hdls);
    static ExpressionHandler make_identity();
    // other member functions:
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    bool is_identity() const;  // an instance represents the identity operator if it is a product with no factors.

   private:
    ProductExpression(FromBufferTag, ExpressionHandlerVector&& expr_hdls) noexcept;
    template <class... Args>
    ProductExpression(VariadicTag, Args&&... expr_hdls) noexcept;
    std::unique_ptr<ProductExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);
};

inline ProductExpression::ProductExpression(FromBufferTag, ExpressionHandlerVector&& expr_hdls) noexcept
    : VectorNumerousExpression(FromBufferTag{}, std::move(expr_hdls)) {
}

template <class... Args>
inline ProductExpression::ProductExpression(VariadicTag, Args&&... expr_hdls) noexcept
    : VectorNumerousExpression(VariadicTag{}, std::forward<Args>(expr_hdls)...) {
}

inline ExpressionHandler ProductExpression::make_from_buffer(ExpressionHandlerVector&& expr_hdls) {
    return ExpressionHandler::make<ProductExpression>(FromBufferTag{}, std::move(expr_hdls));
}

template <class... Args>
ExpressionHandler ProductExpression::make(Args&&... expr_hdls) {
    return ExpressionHandler::make<ProductExpression>(VariadicTag{}, std::forward<Args>(expr_hdls)...);
}

inline ExpressionHandler ProductExpression::make_identity() {
    return make();
}

inline std::unique_ptr<ProductExpression> ProductExpression::casted_clone() const {
    auto v = clone_expr_hdls_vector();
    return std::unique_ptr<ProductExpression>(new ProductExpression(FromBufferTag{}, std::move(v)));
}

inline ExpressionHandler ProductExpression::clone() const {
    auto v = clone_expr_hdls_vector();
    return ExpressionHandler::make<ProductExpression>(FromBufferTag{}, std::move(v));
}

inline bool ProductExpression::equals(const Expression& other) const {
    const auto casted_other_ptr = dynamic_cast<const ProductExpression*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    return equals_helper_function(casted_other);
}

inline std::string ProductExpression::str() const {
    return str_helper_function("𝕀", "◦", {"❪", "❫"});
}

inline std::string ProductExpression::repr() const {
    return repr_helper_function("Product");
}

inline bool ProductExpression::is_identity() const {
    return n_subexpressions() == 0;
}

}  // namespace symbolic_algebra

// **********************************************************
// ***  SumExpression                                     ***
// **********************************************************

namespace symbolic_algebra {
class SumExpression final : public VectorNumerousExpression {
   public:
    // copy semantic:
    SumExpression(const SumExpression&) = delete;
    SumExpression& operator=(const SumExpression&) = delete;
    // move semantic:
    SumExpression(SumExpression&&) = delete;
    SumExpression& operator=(SumExpression&&) = default;
    // creation model:
    static ExpressionHandler make_from_buffer(ExpressionHandlerVector&& expr_hdls);
    template <class... Args>
    static ExpressionHandler make(Args&&... expr_hdls);
    static ExpressionHandler make_zero();
    // other member functions:
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    bool is_zero() const;  //  an instance represents the zero operator if it is a sum of no elements.
   private:
    SumExpression(FromBufferTag, ExpressionHandlerVector&& expr_hdls) noexcept;
    template <class... Args>
    SumExpression(VariadicTag, Args&&... expr_hdls) noexcept;
    std::unique_ptr<SumExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend symbolic_algebra::ExpressionHandler symbolic_algebra::ExpressionHandler::make(Args&&...);
};

inline SumExpression::SumExpression(FromBufferTag, std::vector<ExpressionHandler>&& expr_hdls) noexcept
    : VectorNumerousExpression(FromBufferTag{}, std::move(expr_hdls)) {
}

template <class... Args>
inline SumExpression::SumExpression(VariadicTag, Args&&... expr_hdls) noexcept
    : VectorNumerousExpression(VariadicTag{}, std::forward<Args>(expr_hdls)...) {
}

inline ExpressionHandler SumExpression::make_from_buffer(ExpressionHandlerVector&& expr_hdls) {
    return ExpressionHandler::make<SumExpression>(FromBufferTag{}, std::move(expr_hdls));
}

template <class... Args>
ExpressionHandler SumExpression::make(Args&&... expr_hdls) {
    return ExpressionHandler::make<SumExpression>(VariadicTag{}, std::forward<Args>(expr_hdls)...);
}

inline ExpressionHandler SumExpression::make_zero() {
    return make();
}

inline std::unique_ptr<SumExpression> SumExpression::casted_clone() const {
    auto v = clone_expr_hdls_vector();
    return std::unique_ptr<SumExpression>(new SumExpression(FromBufferTag{}, std::move(v)));
}

inline ExpressionHandler SumExpression::clone() const {
    auto v = clone_expr_hdls_vector();
    return ExpressionHandler::make<SumExpression>(FromBufferTag{}, std::move(v));
}

inline bool SumExpression::equals(const Expression& other) const {
    const auto casted_other_ptr = dynamic_cast<const SumExpression*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    return equals_helper_function(casted_other);
}

inline std::string SumExpression::str() const {
    return str_helper_function("𝟘", "+", {"❴", "❵"});
}

inline std::string SumExpression::repr() const {
    return repr_helper_function("Sum");
}

inline bool SumExpression::is_zero() const {
    return n_subexpressions() == 0;
}

}  // namespace symbolic_algebra

#endif
