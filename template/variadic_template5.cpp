#include <iostream>

class A {
 public:
  void do_something(int x) const {
    std::cout << "Do something with " << x << std::endl;
  }
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums) {
  // 각각의 인자들에 대해 do_something 함수들을 호출한다.
  (t.do_something(nums), ...);
}
int main() {
  A a;
  do_many_things(a, 1, 3, 2, 4);
}

// (t.do_something(nums), ...);
// 위는 사실상 모든 인자들에 대해서 각각 t.do_something(arg) 를 실행한 것과 같습니다. 즉 실제 컴파일 되는 코드는
// t.do_something(1);
// t.do_something(3);
// t.do_something(2);
// t.do_something(4);
// 가 되겠지요.