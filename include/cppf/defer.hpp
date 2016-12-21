#ifndef CPPF_DEFER_H
#define CPPF_DEFER_H
#include <functional>

//  https://github.com/skogorev/cppf#defer

namespace cppf {
  namespace aux {
    class __Defer {
    public:
      __Defer(const std::function<void()>& defer_function)
        : f_(defer_function) {
      }
      __Defer(std::function<void()>&& defer_function)
        : f_(std::forward<std::function<void()>>(defer_function)) {
      }
      template<class FN, class... ARGS>
      __Defer(FN&& f, ARGS&&... args)
        : f_(std::bind(std::forward<FN>(f), std::forward<ARGS>(args)...)) {
      }

      __Defer(const __Defer&) = delete;
      __Defer& operator=(const __Defer&) = delete;

      ~__Defer() {
        f_();
      }

    private:
      std::function<void()> f_;
    };
  } // namespace aux
} // namespace cppf

#ifdef __COUNTER__
#define __CPPF_DEFER_SALT __COUNTER__
#else
#define __CPPF_DEFER_SALT __LINE__
#endif

#define __CPPF_DEFER_CONCAT(x,y) x##y
#define __CPPF_DEFER_VARIABLE_NAME(x,y) __CPPF_DEFER_CONCAT(x,y)

#define CPPF_DEFER(...) cppf::aux::__Defer __CPPF_DEFER_VARIABLE_NAME(defer_obj_, __CPPF_DEFER_SALT)(__VA_ARGS__)

#endif // CPPF_DEFER_H
