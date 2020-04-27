// 역반복자를 사용하는 것은 매우 중요합니다. 아래와 같은 코드를 살펴볼까요.
// 오류코드!!!!

#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  // 끝에서 부터 출력하기
  for (std::vector<int>::size_type i = vec.size() - 1; i >= 0; i--) {
    std::cout << vec[i] << std::endl;
  }

  return 0;
}

// 오류가 발생하게 됩니다. 맨 뒤의 원소 부터 제대로 출력하는 코드 같은데 왜 이런 문제가 발생하였을까요? 
// 그 이유는 vector 의 index 를 담당하는 타입이 부호 없는 정수 이기 때문입니다. 
// 따라서 i 가 0 일 때 i -- 를 하게 된다면 -1 이 되는 것이 아니라, 해당 타입에서 가장 큰 정수가 되버리게 됩니다.

// 따라서 for 문이 영원히 종료할 수 없게 되죠.

// 이 문제를 해결하기 위해서는 부호 있는 정수로 선언해야 하는데, 이 경우 vector 의 index 타입과 일치하지 않아서 타입 캐스팅을 해야 한다는 문제가 발생하게 됩니다.

// 따라서 가장 현명한 선택으로는 역으로 원소를 참조하고 싶다면, 역반복자를 사용하는 것입니다.