// 반복자를 이용하면 아래와 같이 insert 와 erase 함수도 사용할 수 있습니다.

#include <iostream>
#include <vector>


template <typename T>
void print_vector(std::vector<T>& vec) {
  // 전체 벡터를 출력하기
  for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
       ++itr) {
    std::cout << *itr << std::endl;
  }
}
int main() {
  std::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);
  vec.push_back(40);

  std::cout << "처음 벡터 상태" << std::endl;
  print_vector(vec);
  std::cout << "----------------------------" << std::endl;

  // vec[2] 앞에 15 추가
  vec.insert(vec.begin() + 2, 15);
  print_vector(vec);

  std::cout << "----------------------------" << std::endl;
  // vec[3] 제거
  vec.erase(vec.begin() + 3);
  print_vector(vec);
}

// for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
//      ++itr) 
// 와 같이 앞에 typename 을 추가해줘야만 합니다. 그 이유는, iterator 가 std::vector<T> 의 의존 타입이기 때문입니다.

// vec[2] 앞에 15 추가
// vec.insert(vec.begin() + 2, 15);
// 앞서 insert 함수를 소개하였는데, 위 처럼 인자로 반복자를 받고, 그 반복자 앞에 원소를 추가해줍니다. 
// 위 경우 vec.begin() + 2 앞에 15 를 추가하므로 10, 20, 30, 40 에서 10, 20, 15, 30, 40 이 됩니다.

// vec.erase(vec.begin() + 3);
// print_vector(vec);
// 또 아까전에 언급하였던 erase 도 인자로 반복자를 받고, 그 반복자가 가리키는 원소를 제거합니다. 
// 위 경우 4 번째 원소인 30 이 지워지겠지요. 물론 insert 과 erase 함수 모두 O(n) 으로 느린편입니다.