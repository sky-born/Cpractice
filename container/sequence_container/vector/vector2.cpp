// 반복자 사용 예시
#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);
  vec.push_back(40);

  // 전체 벡터를 출력하기
  for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
    std::cout << *itr << std::endl;
  }

  // int arr[4] = {10, 20, 30, 40}
  // *(arr + 2) == arr[2] == 30;
  // *(itr + 2) == vec[2] == 30;

  std::vector<int>::iterator itr = vec.begin() + 2;
  std::cout << "3 번째 원소 :: " << *itr << std::endl;
}
// 앞서 반복자를 마치 포인터 처럼 사용한다고 하였는데, 실제로 현재 반복자가 가리키는 원소의 값을 보고 싶다면;
// std::cout << *itr << std::endl;
// 포인터로 * 를 해서 가리키는 주소값의 값을 보았던 것처럼, * 연산자를 이용해서 itr 이 가리키는 원소를 볼 수 있습니다. 
// 물론 itr 은 실제 포인터가 아니고 * 연산자를 오버로딩해서 마치 포인터 처럼 동작하게 만든 것입니다. * 연산자는 itr 이 가리키는 원소의 레퍼런스를 리턴합니다.

// std::vector<int>::iterator itr = vec.begin() + 2;
// std::cout << "3 번째 원소 :: " << *itr << std::endl;
// 또한 반복자 역시 + 연산자를 통해서 그 만큼 떨어져 있는 원소를 가리키게 할 수 도 있습니다. (그냥 배열을 가리키는 포인터와 정확히 똑같이 동작한다고 생각하시면 됩니다!)