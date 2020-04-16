
// operator++();
// operator--();
// 은 전위 증감 연산자 (++x, --x) 를 오버로딩 하게 됩니다. 그렇다면 후위 증감 연산자 (x++, x--) 는 어떨까요. 바로
// operator++(int x);
// operator--(int x);
// 로 구현하게 됩니다. 물론 인자 x 는 아무런 의미가 없습니다. 단순히 컴파일러 상에서 전위와 후위를 구별하기 위해 int 인자를 넣어주는 것이지요.

// 실제로 ++ 을 구현하면서 인자로 들어가는 값을 사용하는 경우는 없습니다. 따라서 그냥
// operator++(int);
// operator--(int);
// 와 같이 해도 무방합니다.

// 한 가지 중요한 점은, 전위 증감 연산의 경우 값이 바뀐 자기 자신 을 리턴해야 하고, 후위 증감의 경우 값이 바뀌기 이전의 객체 를 리턴해야 된다는 점입니다.

#include <iostream>


class Test {
  int x;

 public:
  Test(int x) : x(x) {}
  Test(const Test& t) : x(t.x) {}

  Test& operator++() {
    x++;
    std::cout << "전위 증감 연산자" << std::endl;
    return *this;
  }

  // 전위 증감과 후위 증감에 차이를 두기 위해 후위 증감의 경우 인자로 int 를
  // 받지만 실제로는 아무것도 전달되지 않는다.
  Test operator++(int) {
    Test temp(*this);
    x++;
    std::cout << "후위 증감 연산자" << std::endl;
    return temp;
  }

  int get_x() const {
    return x;
  }
};

void func(const Test& t) {
  std::cout << "x : " << t.get_x() << std::endl;
}

int main() {
  Test t(3);

  func(++t); // 4
  func(t++); // 4 가 출력됨
  std::cout << "x : " << t.get_x() << std::endl;
}

// 연산자 오버로딩에 대해 다루면서 몇 가지 중요한 포인트 들만 따로 정리해보자면;

// 두 개의 동등한 객체 사이에서의 이항 연산자는 멤버 함수가 아닌 외부 함수로 오버로딩 하는 것이 좋습니다. (예를 들어 Complex 의 operator+(const Complex&, const Complex&) 와 같이 말입니다.)

// 두 개의 객체 사이의 이항 연산자 이지만 한 객체만 값이 바뀐다던지 등의 동등하지 않는 이항 연산자는 멤버 함수로 오버로딩 하는 것이 좋습니다. (예를 들어서 operator+= 는 이항 연산자 이지만 operator+=(const Complex&) 가 낫다)

// 단항 연산자는 멤버 함수로 오버로딩 하는 것이 좋습니다 (예를 들어 operator++ 의 경우 멤버 함수로 오버로딩 합니다)

// 일부 연산자들은 반드시 멤버 함수로만 오버로딩 해야 합니다