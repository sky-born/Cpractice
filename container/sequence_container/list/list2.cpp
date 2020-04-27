#include <iostream>
#include <list>

template <typename T>
void print_list(std::list<T>& lst) {
  std::cout << "[ ";
  // 전체 리스트를 출력하기 (이 역시 범위 기반 for 문을 쓸 수 있습니다)
  for (const auto& elem : lst) {
    std::cout << elem << " ";
  }
  std::cout << "]" << std::endl;
}
int main() {
  std::list<int> lst;

  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);
  lst.push_back(40);

  std::cout << "처음 리스트의 상태 " << std::endl;
  print_list(lst);

  for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
    // 만일 현재 원소가 20 이라면
    // 그 앞에 50 을 집어넣는다.
    if (*itr == 20) {
      lst.insert(itr, 50);
    }
  }

  std::cout << "값이 20 인 원소 앞에 50 을 추가 " << std::endl;
  print_list(lst);

  for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
    // 값이 30 인 원소를 삭제한다.
    if (*itr == 30) {
      lst.erase(itr);
      break;
    }
  }

  std::cout << "값이 30 인 원소를 제거한다" << std::endl;
  print_list(lst);
}

// 마찬가지로 erase 함수를 이용하여 원하는 위치에 있는 원소를 지울 수 도 있습니다.
//  리스트의 경우는 벡터와는 다르게, 원소를 지워도 반복자가 무효화 되지 않습니다. 왜냐하면, 각 원소들의 주소값들은 바뀌지 않기 때문이죠!