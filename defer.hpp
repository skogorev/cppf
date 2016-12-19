#ifndef CPPF_DEFER_H
#define CPPF_DEFER_H
#include <functional>

namespace cppf {

#ifdef __COUNTER__
#define __DEFER_SALT __COUNTER__
#else
#define __DEFER_SALT __LINE__
#endif

class __Defer {
public:
  __Defer(const std::function<void()>& defer_function)
    : f_(defer_function) {
  }

  __Defer(const __Defer&) = delete;
  __Defer& operator=(const __Defer&) = delete;

  template<class FN, class... ARGS>
  __Defer(const FN& f, ARGS... args)
    : __Defer(std::function<void()>(std::bind(f, args...))) {
  }

  ~__Defer() {
    f_();
  }

private:
  std::function<void()> f_;
};

#define CPPF_DEFER(...) cppf::__Defer defer_obj_##__DEFER_SALT(__VA_ARGS__)

} // namespace cppf

#endif // CPPF_DEFER_H
