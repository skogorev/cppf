# cppf
C++ fun library

## Defer `include "cppf/defer.hpp"`
Golang defer analog for C++.

Usage example #1:
```
int main() {
  FILE* f = fopen("/tmp/test", "w+");
  if (f == nullptr) {
    return -1;
  }

  CPPF_DEFER(fclose, f); // The fclose function will be called when the block is closed

  // ... some works

  return 0;
}
```

Usage example #2 with lambda syntax:
```
  std::ofstream out("/tmp/test", std::ios::out);
  CPPF_DEFER(([&out] () {  // Attention: lambda should be framed brackets
    out << '\n';
    out.close();
  }));
  
  out << "hello world";
  ...
```