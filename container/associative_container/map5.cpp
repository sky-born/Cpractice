// 위 처럼 find 함수를 사용했을 때 무엇을 리턴할까요? 일단 해당하는 키가 없으면 m.end() 를 리턴합니다. 
// 그렇다면 위 경우 1 이라는 키에 3 개의 문자열이 대응되어 있는데 어떤거를 리턴해야 할까요? 
// 제일 먼저 insert 한것? 아니면 문자열 중에서 사전 순으로 가장 먼저 오는 것?

// 사실 C++ 표준을 읽어보면 무엇을 리턴하라고 정해놓지 않았습니다.
//  즉, 해당되는 값들 중 아무 거나 리턴해도 상관 없다는 뜻입니다. 
//  위 경우 hello 가 나왔지만, 다른 라이브러리를 쓰는 경우 hi 가 나올 수 도 있고, ahihi 가 나올 수 도 있습니다.

// 그렇다면 1 에 대응되는 값들이 뭐가 있는지 어떻게 알까요? 이를 위해 멀티맵은 다음과 같은 함수를 제공하고 있습니다.
#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(const std::multimap<K, V>& m) {
  // 맵의 모든 원소들을 출력하기
  for (const auto& kv : m) {
    std::cout << kv.first << " " << kv.second << std::endl;
  }
}

int main() {
  std::multimap<int, std::string> m;
  m.insert(std::make_pair(1, "hello"));
  m.insert(std::make_pair(1, "hi"));
  m.insert(std::make_pair(1, "ahihi"));
  m.insert(std::make_pair(2, "bye"));
  m.insert(std::make_pair(2, "baba"));

  print_map(m);

  std::cout << "--------------------" << std::endl;

  // 1 을 키로 가지는 반복자들의 시작과 끝을
  // std::pair 로 만들어서 리턴한다.
  auto range = m.equal_range(1);
  for (auto itr = range.first; itr != range.second; ++itr) {
    std::cout << itr->first << " : " << itr->second << " " << std::endl;
  }
}

// auto range = m.equal_range(1);
// equal_range 함수의 경우 인자로 멀티맵의 키를 받은 뒤에, 
// 이 키에 대응되는 원소들의 반복자들 중에서시작과 끝 바로 다음을 가리키는 반복자를 std::pair 객체로 만들어서 리턴합니다. 
// 즉, begin() 과 end() 를 std::pair 로 만들어서 세트로 리턴한다고 볼 수 있겠지요. 
// 다만, first 로 시작점을, second 로 끝점 바로 뒤를 알 수 있습니다.
//  왜 끝점 바로 뒤를 가리키는 반복자를 리턴하는지는 굳이 설명 안해도 알겠죠?

