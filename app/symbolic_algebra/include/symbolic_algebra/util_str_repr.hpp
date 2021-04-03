#ifndef SYMBOLIC_ALGEBRA_UTIL_STR_REPR_HPP
#define SYMBOLIC_ALGEBRA_UTIL_STR_REPR_HPP

#include <string>

// **********************************************************
// ***  StrRepr                                           ***
// **********************************************************

namespace symbolic_algebra {
namespace util {

class StrRepr {
   public:
    virtual std::string str() const = 0;
    virtual std::string repr() const = 0;
    virtual ~StrRepr() = default;
};

}  // namespace util
}  // namespace symbolic_algebra

#endif