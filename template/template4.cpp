#include <iostream>

template <typename T>
class Vector {
  T* data;
  int capacity;
  int length;

 public:
  // 어떤 타입을 보관하는지
  typedef T value_type;

  // 생성자
  Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

  // 맨 뒤에 새로운 원소를 추가한다.
  void push_back(int s) {
    if (capacity <= length) {
      int* temp = new T[capacity * 2];
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

  // 임의의 위치의 원소에 접근한다.
  T operator[](int i) { return data[i]; }

  // x 번째 위치한 원소를 제거한다.
  void remove(int x) {
    for (int i = x + 1; i < length; i++) {
      data[i - 1] = data[i];
    }
    length--;
  }

  // 현재 벡터의 크기를 구한다.
  int size() { return length; }

  // i 번째 원소와 j 번째 원소 위치를 바꾼다.
  void swap(int i, int j) {
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }

  ~Vector() {
    if (data) {
      delete[] data;
    }
  }
};

template <typename Cont>
void bubble_sort(Cont& cont) {
  for (int i = 0; i < cont.size(); i++) {
    for (int j = i + 1; j < cont.size(); j++) {
      if (cont[i] > cont[j]) {
        cont.swap(i, j);
      }
    }
  }
}

template <typename Cont, typename Comp>
void bubble_sort(Cont& cont, Comp& comp) {
  for (int i = 0; i < cont.size(); i++) {
    for (int j = i + 1; j < cont.size(); j++) {
      if (!comp(cont[i], cont[j])) {
        cont.swap(i, j);
      }
    }
  }
}

// 이 if 문에서 마치 함수를 호출하는 것 처럼 사용되는데, cont[i] 와 cont[j] 를 받아서 
// 내부적으로 크기 비교를 수행한 뒤에 그 결과를 리턴하고 있습니다.

// 한 가지 중요한 사실은 comp 는 함수가 아니라 객체 이고, Comp 클래스에서 () 연산자를 오버로딩한 버전입니다.

// 마치 함수인양 사용되지요. 이렇게, 함수는 아니지만 함수 인 척을 하는 객체를 함수 객체 (Function Object), 
// 혹은 줄여서 Functor 라고 부릅니다. 이 Functor 덕분에, bubble_sort 함수 내에서 두 객체간의 비교를 사용자가 원하는 대로 할 수 있게 되지요.



struct Comp1 {
  bool operator()(int a, int b) { return a > b; }
};

struct Comp2 {
  bool operator()(int a, int b) { return a < b; }
};

int main() {
  Vector<int> int_vec;
  int_vec.push_back(3);
  int_vec.push_back(1);
  int_vec.push_back(2);
  int_vec.push_back(8);
  int_vec.push_back(5);
  int_vec.push_back(3);

  std::cout << "정렬 이전 ---- " << std::endl;
  for (int i = 0; i < int_vec.size(); i++) {
    std::cout << int_vec[i] << " ";
  }

  Comp1 comp1;
  bubble_sort(int_vec, comp1);

  std::cout << std::endl << std::endl << "내림차순 정렬 이후 ---- " << std::endl;
  for (int i = 0; i < int_vec.size(); i++) {
    std::cout << int_vec[i] << " ";
  }
  std::cout << std::endl;

  Comp2 comp2;
  bubble_sort(int_vec, comp2);

  std::cout << std::endl << "오름차순 정렬 이후 ---- " << std::endl;
  for (int i = 0; i < int_vec.size(); i++) {
    std::cout << int_vec[i] << " ";
  }
  std::cout << std::endl;
}