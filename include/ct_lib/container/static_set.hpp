#include <cstddef>
#include <type_traits>

namespace ct_container {

template <typename T, T... Elements> struct static_set;

template <typename T, T NewElement, T... Elements> struct sorted_insert;

template <typename T, T NewElement> struct sorted_insert<T, NewElement> {
  using type = static_set<T, NewElement>;
};

template <typename T, T NewElement, T Head, T... Tail>
struct sorted_insert<T, NewElement, Head, Tail...> {
  using type = typename std::conditional_t < NewElement == Head,
        static_set<T, Head, Tail...>,
        typename std::conditional_t<NewElement<
            Head, static_set<T, NewElement, Head, Tail...>,
            typename sorted_insert<T, NewElement,
                                   Tail...>::type::template prepend<Head>>>;
};

template <typename T, T Head, T... Tail> struct static_set<T, Head, Tail...> {
  static constexpr T head = Head;
  static constexpr T tail[] = {Tail...};

  template <T NewHead> using prepend = static_set<T, NewHead, Head, Tail...>;

  template <T NewElement>
  using insert = typename sorted_insert<T, NewElement, Head, Tail...>::type;

  template <T Query, std::size_t Index = 0> static constexpr bool contains() {
    if constexpr (Index == sizeof...(Tail) + 1) {
      return false;
    } else {
      constexpr T current_element = (Index == 0 ? Head : tail[Index - 1]);
      if constexpr (current_element == Query) {
        return true;
      } else if constexpr (current_element > Query) {
        return false;
      } else {
        return contains<Query, Index + 1>();
      }
    }
  }
};

template <typename T> struct static_set<T> {
  template <T NewElement> using insert = static_set<T, NewElement>;

  template <T Query> static constexpr bool contains() { return false; }
};

} // namespace ct_container
