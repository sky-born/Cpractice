// 앞서 셋과 맵 모두 중복된 원소를 허락하지 않습니다.
//  만일, 이미 원소가 존재하고 있는데 insert 를 하였으면 무시가 되었지요.
//   하지만 멀티셋과 멀티맵은 중복된 원소를 허락합니다.

#include <iostream>
#include <set>
#include <string>

template <typename K>
void print_set(const std::multiset<K>& s) {
  // 셋의 모든 원소들을 출력하기
  for (const auto& elem : s) {
    std::cout << elem << std::endl;
  }
}

int main() {
  std::multiset<std::string> s;

  s.insert("a");
  s.insert("b");
  s.insert("a");
  s.insert("c");
  s.insert("d");
  s.insert("c");

  print_set(s);
}

// 일단 맵 과는 다르게, 한 개의 키에 여러개의 값이 대응될 수 있다는 것은 알 수 있습니다. 
// 하지만 이 때문에 [] 연산자를 멀티맵의 경우 사용할 수 없습니다.