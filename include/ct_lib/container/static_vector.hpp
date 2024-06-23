#pragma once

#include <array>
#include <iostream>

namespace ct_container {

template <typename T, T... Elements> struct static_vector {
  static constexpr std::size_t size = sizeof...(Elements);

  template <std::size_t N> static constexpr T get() {
    static_assert(N < size, "Index out of bound");
    constexpr T array[] = {Elements...};
    return array[N];
  }

  template <T NewElement>
  using push_back = static_vector<T, Elements..., NewElement>;

  template <typename Vector, T... NewElements> struct emplace_back_helper;

  template <typename Vector, T First, T... Rest>
  struct emplace_back_helper<Vector, First, Rest...> {
    using type =
        typename emplace_back_helper<typename Vector::template push_back<First>,
                                     Rest...>::type;
  };

  template <typename Vector> struct emplace_back_helper<Vector> {
    using type = Vector;
  };

  template <T... Args>
  using emplace_back =
      typename emplace_back_helper<static_vector<T, Elements...>,
                                   Args...>::type;

  template <std::size_t... Idx> static void print(std::index_sequence<Idx...>) {
    ((std::cout << get<Idx>() << " "), ...);
    std::cout << std::endl;
  }

  static void print() { print(std::make_index_sequence<size>{}); }
};

} // namespace ct_container
