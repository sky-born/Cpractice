// 위 처럼 류현진의 방어율을 맵에서 검색하였을 때, 0 이라는 값이 나왔습니다. 
// 없는 값을 참조하였으니 오류가 발생해야 정상인데 오히려 값을 돌려주었네요.
// 이는 [] 연산자가, 맵에 없는 키를 참조하게 되면, 자동으로 값의 디폴트 생성자를 호출해서 원소를 추가해버리기 때문입니다.

// double 의 디폴트 생성자의 경우 그냥 변수를 0 으로 초기화 해버립니다. 
// 따라서 되도록이면 find 함수로 원소가 키가 존재하는지 먼저 확인 후에, 값을 참조하는 것이 좋습니다. 
// 아래는 find 함수를 이용해서 안전한게 키에 대응되는 값을 찾는 방법입니다.

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

template <typename K, typename V>
void search_and_print(std::map<K, V>& m, K key) {
  auto itr = m.find(key);
  if (itr != m.end()) {
    std::cout << key << " --> " << itr->second << std::endl;
  } else {
    std::cout << key << "은(는) 목록에 없습니다" << std::endl;
  }
}

int main() {
  std::map<std::string, double> pitcher_list;

  pitcher_list["오승환"] = 3.58;

  print_map(pitcher_list);
  std::cout << "-----------------" << std::endl;

  search_and_print(pitcher_list, std::string("오승환"));
  search_and_print(pitcher_list, std::string("류현진"));
}