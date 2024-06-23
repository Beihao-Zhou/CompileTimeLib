#include <type_traits>
#include <utility>

namespace ct_functional {

template <typename Func> class static_function; // Forward declaration

template <typename Ret, typename... Args> class static_function<Ret(Args...)> {
private:
  static constexpr size_t BUFFER_SIZE = 64;
  using StorageType =
      typename std::aligned_storage_t<BUFFER_SIZE, alignof(max_align_t)>;

  StorageType storage;
  Ret (*invoker)(void *, Args...);

  template <typename F> static Ret invoke(void *ptr, Args... args) {
    return (*reinterpret_cast<F *>(ptr))(std::forward<Args>(args)...);
  }

public:
  template <typename F> static_function(F &&f) {
    static_assert(sizeof(F) <= BUFFER_SIZE,
                  "Function object too large for the buffer");
    new (&storage) F(std::forward<F>(f));
    invoker = &invoke<std::decay_t<F>>;
  }

  ~static_function() {
    using CallableType = typename std::decay_t<Ret(Args...)>;
    auto callable = reinterpret_cast<CallableType *>(&storage);
    callable->~CallableType();
  }

  static_function(const static_function &) = delete;
  static_function &operator=(const static_function &) = delete;

  Ret operator()(Args... args) {
    return invoker(&storage, std::forward<Args>(args)...);
  }
};

} // namespace ct_functional
