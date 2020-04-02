#include <iostream>
#include <string>
using std::string;
class Vector {
  string* data;
  int capacity;
  int length;

 public:
  // 생성자
  Vector(int n = 1);

  // 맨 뒤에 새로운 원소를 추가한다.
  void push_back(string s);

  // 임의의 위치의 원소에 접근한다.
  string operator[](int i);

  // x 번째 위치한 원소를 제거한다.
  void remove(int x);

  // 현재 벡터의 크기를 구한다.
  int size();

  ~Vector();
};

Vector::Vector(int n) : data(new string[n]), capacity(n), length(0) {}

// Vector 의 생성자를 살펴보면 위와 같습니다. 한 가지 흥미로운 점은 여기서는 디폴트 인자가 명시되지 않은 점입니다.
//  이는 C++ 규칙이기도 한데, 클래스 내부 함수 선언에서 디폴드 인자를 명시하였다면 함수 본체에서 명시하면 안되고,
//   반대로 함수 본체에서 명시하였다면 클래스 내부 함수 선언에 명시하면 안됩니다. 즉, 둘 중 한 곳에서만 표시해야 합니다.

void Vector::push_back(string s) {
  if (capacity <= length) {
    string* temp = new string[capacity * 2];
    for (int i = 0; i < length; i++) {
      temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    capacity *= 2;
  }

  data[length] = s;
  length++;
}
// 우리 Vector 클래스의 push_back 함수는 배열 맨 끝에 원소를 집어넣는 클래스 입니다. 
// 위 방법은 기존에 문자열 클래스에서 썼던 방법으로, 만일 배열이 다 차게 되면 1 칸을 더 늘리는 것이 아니라 현재 크기의 두 배 만큼을 새로 할당하고 새로 할당단 공간에 복사하는 것입니다. 
// 이렇게 된다면 가장 효율적으로 공간과 시간을 활용할 수 있습니다.

string Vector::operator[](int i) { return data[i]; }

void Vector::remove(int x) {
  for (int i = x + 1; i < length; i++) {
    data[i - 1] = data[i];
  }
  length--;
}

int Vector::size() { return length; }

Vector::~Vector() {
  if (data) {
    delete[] data;
  }
}