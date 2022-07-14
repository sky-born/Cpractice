// 대망의 Array 배열
#include <iostream>

namespace MyArray {
class Array;
class Int;

class Array {
  friend Int;

  const int dim;  // 몇 차원 배열 인지
  int* size;  // size[0] * size[1] * ... * size[dim - 1] 짜리 배열이다.

  struct Address {
    int level;
    // 맨 마지막 레벨(dim - 1 레벨) 은 데이터 배열을 가리키고, 그 위 상위
    // 레벨에서는 다음 Address 배열을 가리킨다.
    void* next;
  };

  Address* top;

 public:
  Array(int dim, int* array_size) : dim(dim) {
    size = new int[dim];
    for (int i = 0; i < dim; i++) size[i] = array_size[i];

    top = new Address;
    top->level = 0;

    initialize_address(top);
  }
  Array(const Array& arr) : dim(arr.dim) {
    size = new int[dim];
    for (int i = 0; i < dim; i++) size[i] = arr.size[i];

    top = new Address;
    top->level = 0;

    initialize_address(top);
  }
  // address 를 초기화 하는 함수이다. 재귀 호출로 구성되어 있다.
  void initialize_address(Address* current) {
    if (!current) return;
    if (current->level == dim - 1) {
      current->next = new int[size[current->level]];
      return;
    }
    current->next = new Address[size[current->level]];
    for (int i = 0; i != size[current->level]; i++) {
      (static_cast<Address*>(current->next) + i)->level = current->level + 1;
      initialize_address(static_cast<Address*>(current->next) + i);
    }
  }
  void delete_address(Address* current) {
    if (!current) return;
    for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++) {
      delete_address(static_cast<Address*>(current->next) + i);
    }

    delete[] current->next;
  }
  Int operator[](const int index);
  ~Array() {
    delete_address(top);
    delete[] size;
  }
};
class Int {
  void* data;

  int level;
  Array* array;

 public:
  Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL)
      : level(_level), data(_data), array(_array) {
    if (_level < 1 || index >= array->size[_level - 1]) {
      data = NULL;
      return;
    }
    if (level == array->dim) {
      // 이제 data 에 우리의 int 자료형을 저장하도록 해야 한다.
      data = static_cast<void*>((
          static_cast<int*>(static_cast<Array::Address*>(data)->next) + index));
    } else {
      // 그렇지 않을 경우 data 에 그냥 다음 addr 을 넣어준다.
      data = static_cast<void*>(static_cast<Array::Address*>(
                                    static_cast<Array::Address*>(data)->next) +
                                index);
    }
  };

  Int(const Int& i) : data(i.data), level(i.level), array(i.array) {}

  operator int() {
    if (data) return *static_cast<int*>(data);
    return 0;
  }
  Int& operator=(const int& a) {
    if (data) *static_cast<int*>(data) = a;
    return *this;
  }

  Int operator[](const int index) {
    if (!data) return 0;
    return Int(index, level + 1, data, array);
  }
};
Int Array::operator[](const int index) {
  return Int(index, 1, static_cast<void*>(top), this);
}
}  // namespace MyArray
int main() {
  int size[] = {2, 3, 4};
  MyArray::Array arr(3, size);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        arr[i][j][k] = (i + 1) * (j + 1) * (k + 1);
      }
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
                  << std::endl;
      }
    }
  }
}
// 한 가지 중요하게 살펴볼 점은, 전체 클래스를 MyArray 라는 이름 공간으로 감쌌다는 점입니다. 이를 통해 혹여라도 다른 라이브러리에서 Array 라는 클래스를 정의하더라도 문제 없을 것입니다.
// 또한 주목할 점은, 두 개의 클래스를 한 파일에서 사용하기 때문에 클래스의 정의 순서가 매우 중요하다는 점입니다. 소스 상단에
// class Array;
// class Int;
// 와 같이 클래스를 '선언' 하였습니다. 클래스를 선언하지 않는다면, 아래 Array 클래스에서
// friend Int;
// 를 할 수 없게 됩니다. 왜냐하면 컴파일러 입장에서 Int 가 뭔지 알 턱이 없기 때문입니다. 따라서 friend 선언을 하기 전에,
//  이와 같이 class Int 를 먼저 맨 위에 선언해서 사용할 수 있도록 해야 합니다. 그럼에도 불구하고, 맨 밑에
// Int Array::operator[](const int index) {
//   return Int(index, 1, static_cast<void *>(top), this);
// }
// 를 Array 클래스 안에 넣지 않고 따로 빼 놓은 이유는 Int 를 실제로 '이용' 하기 위해서는 클래스 선언 만으로 충분하지 않기 때문입니다.
//  클래스 선언을 통해서는 클래스의 내부 정보가 필요가 없는 것들, 예컨대 friend 선언이나 클래스의 포인터를 정의하는 등의 행동만 가능하지,
//   위 Array 처럼 구체적으로 Int 클래스의 내부 정보 (생성자) 를 사용하는 경우에는 반드시 Int 클래스의 정의가 선행 되어야만 합니다. 
//   따라서 어쩔 수 없이 Array 클래스의 operator[] 만 따로 빼 놓았습니다.