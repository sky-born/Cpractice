#include <iostream>

template <typename T>
void print(T arg) {
  std::cout << arg << std::endl;
}

template <typename T, typename... Types>
void print(T arg, Types... args) {
  std::cout << arg << ", ";
  print(args...);
}

int main() {
  print(1, 3.1, "abc");
  print(1, 2, 3, 4, 5, 6, 7);
}

// 먼저 위와 같이 typename 뒤에 ... 으로 오는 것을 템플릿 파리미터 팩(parameter pack) 이라고 부릅니다. 
// 템플릿 파라미터 팩의 경우 0 개 이상의 템플릿 인자들을 나타냅니다.

// 마찬가지로 함수에 인자로 ... 로 오는 것을 함수 파라미터 팩 이라고 부르며, 0 개 이상의 함수 인자를 나타냅니다.
//  템플릿 파라미터 팩과 함수 파라미터 팩의 차이점은 템플릿의 경우 타입 앞 에 ... 이 오고, 함수의 경우 타입 뒤 에 ... 가 온다는 점입니다.

// 파라미터 팩은 추론된 인자를 제외한 나머지 인자들을 나타내게 됩니다. 예를 들어서
// print(1, 3.1, "abc");
// 위와 같은 print 함수 호출을 살펴보도록 합시다. C++ 컴파일러는 이 두 개의 print 함수 정의를 살펴보면서 어느 것을 택해야 할지 정해야 합니다. 
// 첫 번째 print 의 경우 인자로 단 1 개만 받기 때문에 후보에서 제외되고 두 번째 print 가 택해집니다.