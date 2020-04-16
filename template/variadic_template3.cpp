// sizeof 연산자는 인자의 크기를 리턴하지만 파라미터 팩에 sizeof... 을 사용할 경우 전체 인자의 개수를 리턴하게 됩니다. 
// 예를 들어서 원소들의 평균을 구하는 함수를 생각해봅시다.

#include <iostream>

// 재귀 호출 종료를 위한 베이스 케이스
int sum_all() { return 0; }

template <typename... Ints>
int sum_all(int num, Ints... nums) {
  return num + sum_all(nums...);
}

template <typename... Ints>
double average(Ints... nums) {
  return static_cast<double>(sum_all(nums...)) / sizeof...(nums);
}

int main() {
  // (1 + 4 + 2 + 3 + 10) / 5
  std::cout << average(1, 4, 2, 3, 10) << std::endl;
}