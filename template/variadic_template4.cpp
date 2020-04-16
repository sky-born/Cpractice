#include <iostream>

template <typename... Ints>
int sum_all(Ints... nums) {
  return (... + nums);
}

int main() {
  // 1 + 4 + 2 + 3 + 10
  std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;
}

// return (... + nums);
// 위 문장이 바로 C++ 17 에 추가된 Fold 형식으로, 위는 아래와 같이 컴파일러에서 해석됩니다.
// return ((((1 + 4) + 2) + 3) + 10);

// 한 가지 중요한 점은 Fold 식을 쓸 때 꼭 () 로 감싸줘야 한다는 점입니다. 위 경우
// return (... + nums);
// 대신에
// return ... + nums;
// 로 컴파일 하게 된다면 오류 발생