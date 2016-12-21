# cppf
C++ fun library

## Defer
`#include "cppf/defer.hpp"` [declaration](https://github.com/skogorev/cppf/blob/master/include/cppf/defer.hpp)

[Golang defer](https://tour.golang.org/flowcontrol/12) analog for C++.
A defer statement defers the call of a function until end of block.

Example:
```
int main() {
  FILE* f = fopen("/tmp/test", "w+");
  if (f == nullptr) {
    return -1;
  }

  CPPF_DEFER(fclose, f); // The fclose function will be called when the block (main in this case) is closed

  // ... some works

  return 0;
}
```

Usage syntax examples:
```
void foo() {
  ...
}

void bar(int a, int b) {
  ...
}

class B {
public:
  void set(int a) {
    ...
  }
}

int a = 3;
B b_obj;

// deferred function without arguments
CPPF_DEFER(foo);

// deferred function with arguments '2' and 'a'
CPPF_DEFER(bar, 2, a);

// deferred method of class object with argument 'a'
CPPF_DEFER(&B::set, &b_obj, a);

// lambda syntax
CPPF_DEFER([](){
  foo();
});

// lambda with some capture params [should be framed brackets](http://stackoverflow.com/a/33016577/4402730)
CPPF_DEFER(([a, &b_obj] () {
  b_obj.set(2, a);
}));
```
