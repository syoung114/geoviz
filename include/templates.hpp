#pragma once

#include <type_traits>
#include <tuple>

namespace geoviz {
    template<typename T>
    struct is_tuple : std::false_type {};

    template<typename... Args>
    struct is_tuple<std::tuple<Args...>> : std::true_type {};

    template<typename T>
    inline constexpr bool is_tuple_v = is_tuple<T>::value;

    template<typename T>
    concept IsTuple = is_tuple_v<T>;

    template <typename Base, typename Derived>
    concept IsCRTP = requires(Derived d) {
        static_cast<Base*>(std::addressof(d));
    };
}
