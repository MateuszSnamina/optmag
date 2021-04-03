#ifndef SYMBOLIC_ALGEBRA_ALGORITHM_HPP
#define SYMBOLIC_ALGEBRA_ALGORITHM_HPP

// SELF:
#include <symbolic_algebra/expression_abstract.hpp>

//*************************************************************************
//***  ModificationMode, ModificationResult                             ***
//*************************************************************************

namespace symbolic_algebra {

enum class ModificationMode {
    PassedThroughResult,
    GeneratedResult
};

class ModificationResult {
   public:
    // copy semantic:
    ModificationResult(const ModificationResult&) = delete;
    ModificationResult& operator=(const ModificationResult&) = delete;
    // move semantic:
    ModificationResult(ModificationResult&&) = delete;
    ModificationResult& operator=(ModificationResult&&) = delete;
    // creational model:
    static ModificationResult make_passed_through_result(ExpressionHandler&&);
    static ModificationResult make_generated_result(ExpressionHandler&&);
    // accessors is_passed_through/is_generated_result:
    ModificationMode mode() const;
    bool is_passed_through_result() const;
    bool is_generated_result() const;
    operator bool() const;  // returns true if is_generated_result().
    // move the result:
    const ExpressionHandler& result() const;
    ExpressionHandler result();
    const ExpressionHandler& operator*() const;
    ExpressionHandler operator*();

   private:
    ModificationResult(ModificationMode mode, ExpressionHandler&&) noexcept;
    bool _is_passed_through;
    ModificationMode _mode;
    ExpressionHandler _result;
};

}  // namespace symbolic_algebra

//*************************************************************************
//***  ModyficationFunctionT, modify_in_place                           ***
//*************************************************************************

namespace symbolic_algebra {

using ModyficationFunctionT = std::function<ModificationResult(ExpressionHandler&&)>;
bool modify_in_place(ExpressionHandler& expression, ModyficationFunctionT fun);

}  // namespace symbolic_algebra

//*************************************************************************
//***  GreedinessLevel, dfs_transform                                   ***
//*************************************************************************

namespace symbolic_algebra {

enum class GreedinessLevel {
    DoNotTouchReplacedExpressions,
    RepeatForReplacedExpressions,
    DoDfsForReplacedExpressions,
};

unsigned dfs_transform(
    ExpressionHandler& expression,
    const ModyficationFunctionT& fun,
    GreedinessLevel greediness = GreedinessLevel::DoNotTouchReplacedExpressions);

}  // namespace symbolic_algebra

#endif
