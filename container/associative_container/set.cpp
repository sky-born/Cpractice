// 하지만 맵의 경우 셋 보다 사용하는 메모리가 크기 때문에 키의 존재 유무 만 궁금하다면 셋을 사용하는 것이 좋습니다.
//  그렇다면 셋 부터 어떻게 사용하는지 살펴보겠습니다.

#include <iostream>
#include <set>

template <typename T>
void print_set(std::set<T>& s) {
  // 셋의 모든 원소들을 출력하기
  std::cout << "[ ";
  for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) {
    std::cout << *itr << " ";
  }
  std::cout << " ] " << std::endl;
}
int main() {
  std::set<int> s;
  s.insert(10);
  s.insert(50);
  s.insert(20);
  s.insert(40);
  s.insert(30);

  std::cout << "순서대로 정렬되서 나온다" << std::endl;
  print_set(s);

  std::cout << "20 이 s 의 원소인가요? :: ";
  auto itr = s.find(20);
  if (itr != s.end()) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }

  std::cout << "25 가 s 의 원소인가요? :: ";
  itr = s.find(25);
  if (itr != s.end()) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
}

// 셋에 원소를 추가하기 위해서는 시퀀스 컨테이너 처럼 insert 함수를 사용하면 됩니다. 한 가지 다른점은, 시퀀스 컨테이너 처럼 '어디에' 추가할지에 대한 정보가 없다는 점입니다. 시퀀스 컨테이너가 상자 하나에 원소를 한 개 씩 담고, 각 상자에 번호를 매긴 것이라면, 셋은 그냥 큰 상자 안에 모든 원소들을 쑤셔 넣은 것이라 보면 됩니다. 그 상자 안에 원소가 어디에 있는지는 중요한게 아니고,그 상자 안에 원소가 '있냐/없냐' 만이 중요한 정보입니다.

// 셋에 원소를 추가하거나 지우는 작업은 O(log N) 에 처리됩니다. 시퀀스 컨테이너의 경우 임의의 원소를 지우는 작업이 O(N) 으로 수행되었다는 점을 생각하면 훨씬 빠르다고 볼 수 있습니다.

// 셋 역시 셋에 저장되어 있는 원소들에 접근하기 위해 반복자를 제공하며, 이 반복자는 BidirectionalIterator 입니다. 
// 즉, 시퀀스 컨테이너의 리스트 처럼 임의의 위치에 있는 원소에 접근하는 것은 불가능 하고 순차적으로 하나 씩 접근하는 것 밖에 불가능 합니다.

