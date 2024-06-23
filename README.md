# CompileTimeLib
A compile-time C++ library

## Features
- **Static Set**: A compile-time set container that ensures unique elements.
- **Static Vector**: A compile-time vector container. 

## Next
- **Compile-Time Algorithms**: Functions that perform operations such as sorting and searching during compilation.
- **Compile-Time Serialization**: Techniques for serializing data at compile time.


## Getting Started

### Prerequisites
- C++17 compiler (e.g., GCC, Clang, MSVC)
- CMake 3.10 or higher (for building the project)

### Installation
Commands to format, build and test can be found in `manage.py`. 

## Usage
Here is an example of how to use the `static_set` in your C++ code:
```cpp
int main() {
    using MySet = ct_container::static_set<int>::insert<1>::insert<2>::insert<3>;
    static_assert(MySet::contains<2>(), "Set should contain 2");
    return 0;
}
```

## License
Distributed under the MIT License. See `LICENSE` for more information.
