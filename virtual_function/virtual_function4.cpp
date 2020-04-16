#include <iostream>

class Animal {
 public:
  Animal() {}
  virtual ~Animal() {}
  virtual void speak() = 0;
};

class Dog : public Animal {
 public:
  Dog() : Animal() {}
  void speak() override { std::cout << "왈왈" << std::endl; }
};

class Cat : public Animal {
 public:
  Cat() : Animal() {}
  void speak() override { std::cout << "야옹야옹" << std::endl; }
};

int main() {
  Animal* dog = new Dog();
  Animal* cat = new Cat();

  dog->speak();
  cat->speak();
}



// class Animal {
//  public:
//   Animal() {}
//   virtual ~Animal() {}
//   virtual void speak() = 0;
// };

// Animal 클래스의 speak 함수를 살펴봅시다. 다른 함수들과는 달리, 함수의 몸통이 정의되어 있지 않고 단순히 = 0; 으로 처리되어 있는 가상 함수 입니다.

// 그렇다면 이 함수는 무엇을 하는 함수 일까요? 그 답은, "무엇을 하는지 정의되어 있지 않는 함수" 입니다. 다시 말해 이 함수는 반드시 오버라이딩 되어야만 하는 함수 이지요.

// 이렇게, 가상 함수에 = 0; 을 붙여서, 반드시 오버라이딩 되도록 만든 함수를 완전한 가상 함수라 해서, 순수 가상 함수(pure virtual function)라고 부릅니다.

// 당연하게도, 순수 가상 함수는 본체가 없기 때문에, 이 함수를 호출하는 것은 불가능합니다. 그렇기 때문에, Animal 객체를 생성하는것 또한 불가능입니다.