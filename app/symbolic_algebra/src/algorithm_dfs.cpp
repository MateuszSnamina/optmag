// MY_HEADER:
#include <symbolic_algebra/algorithm_dfs.hpp>

//*************************************************************************
//***  ModificationResult                                               ***
//*************************************************************************

namespace symbolic_algebra {

ModificationResult::ModificationResult(ModificationMode mode, ExpressionHandler&& result) noexcept
    : _mode(mode),
      _result(std::move(result)) {
}

ModificationResult ModificationResult::make_passed_through_result(ExpressionHandler&& result) {
    return ModificationResult(ModificationMode::PassedThroughResult, std::move(result));
}

ModificationResult ModificationResult::make_generated_result(ExpressionHandler&& result) {
    return ModificationResult(ModificationMode::GeneratedResult, std::move(result));
}

ModificationMode ModificationResult::mode() const {
    return _mode;
}

bool ModificationResult::is_passed_through_result() const {
    return _mode == ModificationMode::PassedThroughResult;
}

bool ModificationResult::is_generated_result() const {
    return _mode == ModificationMode::GeneratedResult;
}

ModificationResult::operator bool() const {
    return is_generated_result();
}

const ExpressionHandler& ModificationResult::result() const {
    return _result;
}

ExpressionHandler ModificationResult::result() {
    return std::move(_result);
}

const ExpressionHandler& ModificationResult::operator*() const {
    return result();
}

ExpressionHandler ModificationResult::operator*() {
    return result();
}

}  // namespace symbolic_algebra

//*************************************************************************
//***  modify_in_place                                                  ***
//*************************************************************************

namespace symbolic_algebra {

bool modify_in_place(ExpressionHandler& expression, ModyficationFunctionT fun) {
    auto result = fun(std::move(expression));
    expression = std::move(*result);
    return result.is_generated_result();
}

}  // namespace symbolic_algebra

//*************************************************************************
//***  dfs_transform                                                    ***
//*************************************************************************

namespace symbolic_algebra {

unsigned dfs_transform(
    ExpressionHandler& expression,
    const ModyficationFunctionT& fun,
    GreedinessLevel greediness) {
    assert(!expression.is_shallow_drained());
    unsigned replacement_counter = 0;
    for (auto& subexpression : expression.range()) {
        replacement_counter += dfs_transform(subexpression, fun, greediness);
    }
    switch (greediness) {
        case GreedinessLevel::DoNotTouchReplacedExpressions:
            if (modify_in_place(expression, fun)) {
                replacement_counter++;
            }
            break;
        case GreedinessLevel::RepeatForReplacedExpressions:
            while (modify_in_place(expression, fun)) {
                replacement_counter++;
            }
            break;
        case GreedinessLevel::DoDfsForReplacedExpressions:
            if (modify_in_place(expression, fun)) {
                replacement_counter++;
                replacement_counter += dfs_transform(expression, fun, greediness);
            }
            break;
        default:
            assert(false);
    }
    return replacement_counter;
}

}  // namespace symbolic_algebra