#ifndef SYMBOLIC_ALGEBRA_UTIL_ID_HPP
#define SYMBOLIC_ALGEBRA_UTIL_ID_HPP

namespace symbolic_algebra {

// **********************************************************
// ***  IdClass                                           ***
// **********************************************************

using IdIntegralType = unsigned long;

class IdClass {
   public:
    IdIntegralType id() const;
    virtual ~IdClass() = default;

   protected:
    IdClass();

   private:
    IdIntegralType _id;
    static IdIntegralType _pool_id;
};

inline IdClass::IdClass() : _id(_pool_id++) {
}

inline IdIntegralType IdClass::id() const {
    return _id;
}

}  // namespace symbolic_algebra

#endif
