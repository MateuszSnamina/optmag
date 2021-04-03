#ifndef SYMBOLIC_ALGEBRA_EXPRESSION_ABSTRACT_HPP
#define SYMBOLIC_ALGEBRA_EXPRESSION_ABSTRACT_HPP

// SELF:
#include <symbolic_algebra/util_result.hpp>
#include <symbolic_algebra/util_str_repr.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/range/any_range.hpp>
// STD STL:
#include <array>
#include <list>
#include <map>
#include <string>
#include <vector>
// STD NOT-STL:
//#include <iostream>//DEBUG
#include <functional>
#include <memory>
#include <type_traits>
// STC C:
#include <cassert>

#define UNUSED(x) (void)x;

// ##########################################################
// ###  Expression + ExpressionHandler                    ###
// ##########################################################

/*
 *
 * Expression is an abstract describing for describing compound many bosons operators.
 * In particular, the following is an expression:
 * - any “primitive boson operaotr”, like:
 * -- a boson creation operator,
 * -- a boson annihilation operator,
 * -- a boson number operator,
 * - any “structural block” of expressions, like:
 * -- a sum of expressions,
 * -- a product of expressions (“operator domain product”),
 * -- a factored expressions (“scalar times operator product”).
 * Scalars are not considered as Expressions.
 * 
 * Expressions are AST (abstract syntax tree) nodes.
 * To acount this Expressions offer the standard tree node functionalities:
 * - suppression accessors, supporting both “indexing schematics” and “range semantics”,
 * - deep copy,
 * - equality rest.
 * See the following pure abstract member functions:
 * ```
 *   Expression::n_subexpressions() const = 0;
 *   Expression::subexpression(unsigned n_subexpression) = 0;
 *   Expression::subexpression(unsigned n_subexpression) const = 0;
 *   Expression::range() = 0;
 *   Expression::range() const = 0;
 *   Expression::crange() const = 0;
 *   clone() const;
 *   equals(const ExpressionHandler&) const;
 * ```
 * 
 * Note on equality rest: this tests the AST semantic equivalence.
 * This is not the instances identity equality test, nor mathematical equality.
 * Example1: two different instances of creation operator defined for a boson
 *           are considered AST semantic equivalent
 *           (despite their identity is different).
 * Example2: two different trees -- the first representing a product
 *           of creation operator and annitilation operator for a boson,
 *           and the second representing the number operator for the boson
 *           are not considered AST semantic equivalent
 *           (despite the trees represent operators being mathematically equivalent).
 * Following the standard OOP consideration `equals` member function
 * should be overridden only in final concrete subclasses.
 * (The not-final concrete subclasses are not compatible with the equivalence semantics).
 * The two instances should be considered equal only if they are
 * of the same final concrete subclass type.
 * 
 * Expressions implement “python-style” string representation. See the following member functions:
 * ```
 *   std::string str() const;
 *   std::string repr() const;
 * ```
 * 
 * Expressions are designed to be referenced by means of ExpressionsHandler.
 * Every concrete subclass should have all constructors private, forcing usage of static factory methods.
 * The naming of the factory methods should be like this: `make(...)`, `make_from_XXX(...)`, `make_somethins(...)`.
 * The factory methods should return ExpressionsHandler.
 * Both Expressions and ExpressionsHandler supports move semantic with copy semantic explicitly deleted.
 * 
 * ExpressionsHandler represents ownership of the wrapped Expression.
 * All expressions reference their subexpressions by means of ExpressionsHandlers.
 * 
 * ExpressionsHandler has numerous “fast acceess” member functions defined do make the wrapper as easy to use as possible:
 * ```
 *   ExpressionHandler::n_subexpressions() const;
 *   ExpressionHandler::subexpression(unsigned n_subexpression);
 *   subexpression(unsigned n_subexpression) const;
 *   ExpressionHandler::range();
 *   ExpressionHandler::range() const;
 *   ExpressionHandler::crange() const;
 *   ExpressionHandler::str() const override;
 *   ExpressionHandler::repr() const override;
 *   ExpressionHandler::ExpressionHandler clone() const;
 *   ExpressionHandler::equals(const ExpressionHandler&) const;
 * ```
 * Wrapper deference may be accomplished by one of the following  methods:
 * ```
 *   ExpressionHandler::target();
 *   ExpressionHandler::target() const;
 *   template <class ExpressionDerrivedClass>ExpressionHandler::ExpressionDerrivedClass& casted_target();
 *   template <class ExpressionDerrivedClass>ExpressionHandler::const ExpressionDerrivedClass& casted_target() const;
 *   template <class ExpressionDerrivedClass> ExpressionHandler::is_of_type() const;
 * ```
 * 
 * Expressions -- known implementations:
 * ┏[Expression]                         [abstract]       [expression_abstract.hpp]
 * ┣┳[LeafExpression]                    [abstract]       [expression_common.hpp]
 * ┃┣┳[BosonPrimitiveOperators]          [abstract]       [expression_boson_primitive_operators.hpp.hpp]
 * ┃┃┣┳[BosonCreationAnnihilationBase]   [abstract]       [expression_boson_primitive_operators.hpp.hpp]
 * ┃┃┃┣━BosonCreationOperator            [final concrete] [expression_boson_primitive_operators.hpp]
 * ┃┃┃┣━BosonAnnihilationOperator        [final concrete] [expression_boson_primitive_operators.hpp]
 * ┃┃┣━BosonNumberOperator               [final concrete] [expression_boson_primitive_operators.hpp]
 * ┣┳[BridgeExpression]                  [abstract]       [expression_common.hpp]
 * ┃┣━IntegerFactoredExpression          [final concrete] [expression_structural_blocks.hpp]
 * ┣┳[VectorNumerousExpression]          [abstract]       [expression_common.hpp]
 * ┃┣━ProductExpression                  [final concrete] [expression_structural_blocks.hpp]
 * ┃┣━SumExpression                      [final concrete] [expression_structural_blocks.hpp]
 * 
 */

// **********************************************************
// ***  Forward declarations                              ***
// **********************************************************

namespace symbolic_algebra {

class Expression;
class ExpressionHandler;

}  // namespace symbolic_algebra

// **********************************************************
// ***  Typedefs for ExpressionHandler -- part 1          ***
// **********************************************************

namespace symbolic_algebra {

// typedefs ExpressionHandler optional:
using ExpressionHandlerOptional = std::optional<ExpressionHandler>;
// typedefs ExpressionHandler containers:
using ExpressionHandlerVector = std::vector<ExpressionHandler>;
using ExpressionHandlerList = std::list<ExpressionHandler>;
template <std::size_t N>
using ExpressionHandlerArray = std::array<ExpressionHandler, N>;
template <class KeyT>
using ExpressionHandlerMap = std::map<KeyT, ExpressionHandler>;
// typedefs ExpressionHandler ranges (not const flavour):
using ExpressionHandlerSinglePassRange = boost::any_range<ExpressionHandler, boost::single_pass_traversal_tag>;
using ExpressionHandlerForwardRange = boost::any_range<ExpressionHandler, boost::forward_traversal_tag>;
using ExpressionHandlerBidirectionalRange = boost::any_range<ExpressionHandler, boost::bidirectional_traversal_tag>;
using ExpressionHandlerRandomAccessRange = boost::any_range<ExpressionHandler, boost::random_access_traversal_tag>;
// typedefs ExpressionHandler ranges (const flavour):
using ConstExpressionHandlerSinglePassRange = boost::any_range<const ExpressionHandler, boost::single_pass_traversal_tag>;
using ConstExpressionHandlerForwardRange = boost::any_range<const ExpressionHandler, boost::forward_traversal_tag>;
using ConstExpressionHandlerBidirectionalRange = boost::any_range<const ExpressionHandler, boost::bidirectional_traversal_tag>;
using ConstExpressionHandlerRandomAccessRange = boost::any_range<const ExpressionHandler, boost::random_access_traversal_tag>;

}  // namespace symbolic_algebra

// **********************************************************
// ***  ExpressionHandler                                 ***
// **********************************************************

namespace symbolic_algebra {

class ExpressionHandler final : public util::StrRepr {
   public:
    // copy semantic:
    ExpressionHandler(const ExpressionHandler&) = delete;
    ExpressionHandler& operator=(const ExpressionHandler&) = delete;
    // move semantic:
    ExpressionHandler(ExpressionHandler&&);
    ExpressionHandler& operator=(ExpressionHandler&&);
    // drained checker (drained = after move => invalid):
    bool is_shallow_drained() const;
    bool is_deep_drained() const;
    // creation model:
    template <class ExpressionDerrivedClass, class... Args>
    static ExpressionHandler make(Args&&... expression_class_ctor_args);
    // accessors:
    Expression& target();
    const Expression& target() const;
    template <class ExpressionDerrivedClass>
    util::SymbolicAlgebraResult<std::reference_wrapper<ExpressionDerrivedClass>> casted_target();
    template <class ExpressionDerrivedClass>
    util::SymbolicAlgebraResult<std::reference_wrapper<const ExpressionDerrivedClass>> casted_target() const;
    template <class ExpressionDerrivedClass>
    const bool is_of_type() const;
    // quick access for the underying expression -- tree structure accessos:
    unsigned n_subexpressions() const;
    ExpressionHandler& subexpression(unsigned n_subexpression);
    const ExpressionHandler& subexpression(unsigned n_subexpression) const;
    ExpressionHandlerRandomAccessRange range();
    ConstExpressionHandlerRandomAccessRange range() const;
    ConstExpressionHandlerRandomAccessRange crange() const;
    // quick access for the underying expression -- string representation:
    std::string str() const override;
    std::string repr() const override;
    // other methods:
    ExpressionHandler clone() const;
    bool equals(const ExpressionHandler&) const;

   private:
    ExpressionHandler(std::unique_ptr<Expression>) noexcept;
    std::unique_ptr<Expression> substitute(std::unique_ptr<Expression>);
    friend void swap(ExpressionHandler& expr_1, ExpressionHandler& expr_2);

   private:
    std::unique_ptr<Expression> _expr;
    bool _is_drained;
};

}  // namespace symbolic_algebra

// **********************************************************
// ***  Typedefs for ExpressionHandler -- part 2          ***
// **********************************************************

namespace symbolic_algebra {

// typedefs ExpressionHandlerranges iterators (not const flavour):
using ExpressionHandlerSinglePassRangeIterator = boost::range_iterator<ExpressionHandlerSinglePassRange>::type;
using ExpressionHandlerForwardRangeIterator = boost::range_iterator<ExpressionHandlerForwardRange>::type;
using ExpressionHandlerBidirectionalRangeIterator = boost::range_iterator<ExpressionHandlerBidirectionalRange>::type;
using ExpressionHandlerRandomAccessRangeIterator = boost::range_iterator<ExpressionHandlerRandomAccessRange>::type;
// typedefs ExpressionHandlerranges iterators (const flavour):
using ConstExpressionHandlerSinglePassRangeIterator = boost::range_iterator<ConstExpressionHandlerSinglePassRange>::type;
using ConstExpressionHandlerForwardRangeIterator = boost::range_iterator<ConstExpressionHandlerForwardRange>::type;
using ConstExpressionHandlerBidirectionalRangeIterator = boost::range_iterator<ConstExpressionHandlerBidirectionalRange>::type;
using ConstExpressionHandlerRandomAccessRangeIterator = boost::range_iterator<ConstExpressionHandlerRandomAccessRange>::type;

}  // namespace symbolic_algebra

// **********************************************************
// ***  Expression                                        ***
// **********************************************************

namespace symbolic_algebra {

class Expression : public util::StrRepr {
   public:
    // copy semantic:
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
    // move semantic:
    Expression(Expression&&) = default;
    Expression& operator=(Expression&&) = default;
    // tree structure accessos:
    virtual unsigned n_subexpressions() const = 0;
    virtual ExpressionHandler& subexpression(unsigned n_subexpression) = 0;
    virtual const ExpressionHandler& subexpression(unsigned n_subexpression) const = 0;
    virtual ExpressionHandlerRandomAccessRange range() = 0;
    virtual ConstExpressionHandlerRandomAccessRange range() const = 0;
    virtual ConstExpressionHandlerRandomAccessRange crange() const = 0;
    // tree structure operations:
    virtual ExpressionHandler clone() const = 0;
    virtual bool equals(const Expression&) const = 0;
    // dctor:
    virtual ~Expression() = default;

   protected:
    Expression() = default;
};

}  // namespace symbolic_algebra

// **********************************************************
// ***  ExpressionHandler                                 ***
// ***  (member functions implementation)                 ***
// **********************************************************

namespace symbolic_algebra {

inline ExpressionHandler::ExpressionHandler(std::unique_ptr<Expression> expr) noexcept
    : _expr(nullptr),
      _is_drained(true) {
    assert(expr);
    _expr = std::move(expr);
    _is_drained = false;
}

inline ExpressionHandler::ExpressionHandler(ExpressionHandler&& other)
    : _expr(nullptr),
      _is_drained(true) {
    assert(!other.is_shallow_drained());
    assert(other._expr);
    other._is_drained = true;
    _expr = std::move(other._expr);
    _is_drained = false;
}

inline ExpressionHandler& ExpressionHandler::operator=(ExpressionHandler&& other) {
    assert(!other.is_shallow_drained());
    assert(other._expr);
    other._is_drained = true;
    _expr = std::move(other._expr);
    _is_drained = false;
    return *this;
}

inline bool ExpressionHandler::is_shallow_drained() const {
    return _is_drained;
}

inline bool ExpressionHandler::is_deep_drained() const {
    if (_is_drained) {
        return true;
    }
    return boost::algorithm::any_of(crange(), [](const auto& _) { return _.is_deep_drained(); });
}

template <class ExpressionDerrivedClass, class... Args>
ExpressionHandler ExpressionHandler::make(Args&&... expression_class_ctor_args) {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    return ExpressionHandler(std::unique_ptr<ExpressionDerrivedClass>(new ExpressionDerrivedClass(std::forward<Args>(expression_class_ctor_args)...)));
}

inline Expression& ExpressionHandler::target() {
    assert(!is_shallow_drained());
    assert(_expr);
    return *_expr;
}

inline const Expression& ExpressionHandler::target() const {
    assert(!is_shallow_drained());
    assert(_expr);
    return *_expr;
}

inline std::string ExpressionHandler::str() const {
    assert(!is_shallow_drained());
    return target().str();
}

inline std::string ExpressionHandler::repr() const {
    assert(!is_shallow_drained());
    return target().repr();
}

inline unsigned ExpressionHandler::n_subexpressions() const {
    assert(!is_shallow_drained());
    return target().n_subexpressions();
}

inline ExpressionHandler& ExpressionHandler::subexpression(unsigned n_subexpression) {
    assert(!is_shallow_drained());
    return target().subexpression(n_subexpression);
}

inline const ExpressionHandler& ExpressionHandler::subexpression(unsigned n_subexpression) const {
    assert(!is_shallow_drained());
    return target().subexpression(n_subexpression);
}

inline ExpressionHandlerRandomAccessRange ExpressionHandler::range() {
    assert(!is_shallow_drained());
    return target().range();
}

inline ConstExpressionHandlerRandomAccessRange ExpressionHandler::range() const {
    assert(!is_shallow_drained());
    return target().range();
}

inline ConstExpressionHandlerRandomAccessRange ExpressionHandler::crange() const {
    assert(!is_shallow_drained());
    return target().crange();
}

inline ExpressionHandler ExpressionHandler::clone() const {
    assert(!is_shallow_drained());
    return ExpressionHandler(target().clone());
}

inline bool ExpressionHandler::equals(const ExpressionHandler& other) const {
    assert(!other.is_shallow_drained());
    assert(!is_shallow_drained());
    return target().equals(other.target());
}

template <class ExpressionDerrivedClass>
inline util::SymbolicAlgebraResult<std::reference_wrapper<ExpressionDerrivedClass>> ExpressionHandler::casted_target() {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    assert(!is_shallow_drained());
    using ResultT = util::SymbolicAlgebraResult<std::reference_wrapper<ExpressionDerrivedClass>>;
    const auto ptr = dynamic_cast<ExpressionDerrivedClass*>(&target());
    if (!ptr) {
        const util::SymbolicAlgebraRuntimeException exception{"dynamic cast error", std::any{}};
        return ResultT::Err(exception);
    }
    return ResultT::Ok(std::ref(*ptr));
}

template <class ExpressionDerrivedClass>
inline util::SymbolicAlgebraResult<std::reference_wrapper<const ExpressionDerrivedClass>> ExpressionHandler::casted_target() const {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    assert(!is_shallow_drained());
    using ResultT = util::SymbolicAlgebraResult<std::reference_wrapper<const ExpressionDerrivedClass>>;
    const auto ptr = dynamic_cast<const ExpressionDerrivedClass*>(&target());
    if (!ptr) {
        const util::SymbolicAlgebraRuntimeException exception{"dynamic cast error", std::any{}};
        return ResultT::Err(exception);
    }
    return ResultT::Ok(std::cref(*ptr));
}

template <class ExpressionDerrivedClass>
const bool ExpressionHandler::is_of_type() const {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    assert(!is_shallow_drained());
    return bool(dynamic_cast<const ExpressionDerrivedClass*>(&target()));
}

inline std::unique_ptr<Expression>
ExpressionHandler::substitute(std::unique_ptr<Expression> expr) {
    assert(expr);
    std::swap(_expr, expr);
    _is_drained = false;
    return expr;
}

inline void swap(ExpressionHandler& expr_1, ExpressionHandler& expr_2) {
    std::swap(expr_1._expr, expr_2._expr);
    std::swap(expr_1._is_drained, expr_2._is_drained);
}

}  // namespace symbolic_algebra

#endif
