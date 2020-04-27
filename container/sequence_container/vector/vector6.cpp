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

  std::cout << "초기 vec 상태" << std::endl;
  print_vector(vec);

  std::cout << "역으로 vec 출력하기!" << std::endl;
  // itr 은 vec[2] 를 가리킨다.
  std::vector<int>::reverse_iterator r_iter = vec.rbegin();
  for (; r_iter != vec.rend(); r_iter++) {
    std::cout << *r_iter << std::endl;
  }
}

// 역으로 벡터의 원소들을 출력할 수 있습니다.

// 이전에 반복자의 end() 가 맨 마지막 원소의 바로 뒤를 가리켰던 것처럼, 역반복자의 rend() 역시 맨 앞 원소의 바로 앞을 가리키게 됩니다. 
// 또한 반복자의 경우 값이 증가하면 뒤쪽 원소로 가는 것처럼, 역반복자의 경우 값이 증가하면 앞쪽 원소로 가게 됩니다.

// 또 반복자가 상수 반복자가 있는 것 처럼 역반복자 역시 상수 역반복자가 있습니다. 
// 그 타입은 const_reverse_iterator 타입이고, crbegin(), crend() 로 얻을 수 있습니다.