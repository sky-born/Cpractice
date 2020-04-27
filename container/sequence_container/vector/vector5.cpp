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

  // itr 은 vec[2] 를 가리킨다.
  std::vector<int>::iterator itr = vec.begin() + 2;

  // vec[2] 의 값을 50으로 바꾼다.
  *itr = 50;

  std::cout << "---------------" << std::endl;
  print_vector(vec);

  // 상수 iterator 이다. 값을 바꿀수 없음
  // 위치를 저장하여 vector가 변할때마다 iterator 는 쓸수 없지만 const iterator는 쓸수 있음
  // const iterator를 정한후 값을 바꾸면 그에 따라 맞게 값이 봐낌
  std::vector<int>::const_iterator citr = vec.cbegin() + 2;


  vec.erase(itr);

  std::cout<<*citr<<std::endl;
}


// cbegin() 과 cend() 함수를 이용하여 처음과 끝을 얻을 수 있습니다. 
// 많은 경우 반복자의 값을 바꾸지 않고 참조만 하는 경우가 많으므로, const iterator 를 적절히 이용하는 것이 좋습니다.

