// 마지막으로 짚고 넘어갈 점은 맵 역시 셋 처럼 중복된 원소를 허락하지 않는다는 점입니다. 
// 이미, 같은 키가 원소로 들어 있다면 나중에 오는 insert 는 무시됩니다.

#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(const std::map<K, V>& m) {
  // kv 에는 맵의 key 와 value 가 std::pair 로 들어갑니다.
  for (const auto& kv : m) {
    std::cout << kv.first << " " << kv.second << std::endl;
  }
}

int main() {
  std::map<std::string, double> pitcher_list;

  // 맵의 insert 함수는 std::pair 객체를 인자로 받습니다.
  pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.23));
  pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.93));

  print_map(pitcher_list);

  // 2.23 이 나올까 2.93 이 나올까?
  std::cout << "박세웅 방어율은? :: " << pitcher_list["박세웅"] << std::endl;
}