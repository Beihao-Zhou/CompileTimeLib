#pragma once

#include <stddef.h>

namespace ct_lib {

template <typename T, size_t N> constexpr void sort(T (&arr)[N]) {
  bool swapped(false);
  do {
    swapped = false;
    for (size_t i = 1; i < N; i++) {
      if (arr[i - 1] > arr[i]) {
        T temp = arr[i - 1];
        arr[i - 1] = arr[i];
        arr[i] = temp;
        swapped = true;
      }
    }
  } while (swapped);
}

} // namespace ct_lib
