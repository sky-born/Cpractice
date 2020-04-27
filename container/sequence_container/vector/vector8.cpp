// 위와 같이 컨테이너의 원소를 for 문 으로 접근하는 패턴은 매우 많이 등장하는데, 
// C++ 11 에서 부터는 이와 같은 패턴을 매우 간단하게 나타낼 수 있는 방식을 제공하고 있습니다. 
// 바로 범위 기반(range-based) for 문 이라 불리는 것입니다.
#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  // range-based for 문
  // else
//   for(auto elem : vec) {
  for (int elem : vec) {
    std::cout << "원소 : " << elem << std::endl;
  }

  return 0;
}

// 만약에 복사 하기 보다는 레퍼런스를 받고 싶다면 어떨까요? 매우 간단합니다. 
// 단순히 레퍼런스 타입으로 바꿔버리면 되죠. 
// 예를 들어서 기존의 print_vec 함수를 범위 기반 for 문을 사용해서 어떻게 바꿀 수 있는지 살펴봅시다.