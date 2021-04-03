#ifndef  SYMBOLIC_ALGEBRA_UTIL_MAKE_HPP
#define  SYMBOLIC_ALGEBRA_UTIL_MAKE_HPP

#include <algorithm>
#include <array>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>
#include <optional>

// The code here is a simple solution copied from:
// https://stackoverflow.com/questions/8193102/initializer-list-and-move-semantics

namespace symbolic_algebra {
namespace util {

template <class Array>
struct maker;

// a maker which makes a std::vector
template <class T, class A>
struct maker<std::vector<T, A>> {
    using result_type = std::vector<T, A>;

    template <class... Ts>
    auto operator()(Ts&&... ts) const -> result_type {
        result_type result;
        result.reserve(sizeof...(Ts));
        using rebuild_prod_sum_into_sum_prod = int[];
        void(rebuild_prod_sum_into_sum_prod{
            0,
            (result.push_back(std::forward<Ts>(ts)), 0)...});

        return result;
    }
};

// a maker which makes std::array
template <class T, std::size_t N>
struct maker<std::array<T, N>> {
    using result_type = std::array<T, N>;

    template <class... Ts>
    auto operator()(Ts&&... ts) const {
        return result_type{std::forward<Ts>(ts)...};
    }
};

// delegation function which selects the correct maker
template <class Array, class... Ts>
inline auto make(Ts&&... ts) {
    auto m = maker<Array>();
    return m(std::forward<Ts>(ts)...);
}

// EXAMPLE:
// using vt = std::vector<std::unique_ptr<int>>;
// using at = std::array<std::unique_ptr<int>, 2>;
// auto a = make<at>(std::make_unique<int>(10), std::make_unique<int>(20));
// auto v = make<vt>(std::make_unique<int>(10), std::make_unique<int>(20));


}  // namespace util
}  // namespace symbolic_algebra

#endif