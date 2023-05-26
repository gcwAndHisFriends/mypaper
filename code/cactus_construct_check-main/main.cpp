#include <iostream>
 #include <vector>
 struct magic {
  static const int number = 42;
 };
 int main()
 {
  std::vector<int> v;
  // 调用 push_back(const T&)
  v.push_back(magic::number);
  std::cout << v[0] << std::endl;
 }