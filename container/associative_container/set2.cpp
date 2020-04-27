// 또한 셋의 중요한 특징으로 바로 셋 안에는 중복된 원소들이 없다는 점이 있습니다.
#include <iostream>
#include <set>

template <typename T>
void print_set(std::set<T>& s) {
  // 셋의 모든 원소들을 출력하기
  std::cout << "[ ";
  for (const auto& elem : s) {
    std::cout << elem << " ";
  }
  std::cout << " ] " << std::endl;
}

int main() {
  std::set<int> s;
  s.insert(10);
  s.insert(20);
  s.insert(30);
  s.insert(20);
  s.insert(10);

  print_set(s);
}