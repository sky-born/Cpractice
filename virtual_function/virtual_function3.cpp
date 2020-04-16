#include <iostream>

class Parent {
 public:
  Parent() { std::cout << "Parent 생성자 호출" << std::endl; }
  virtual ~Parent() { std::cout << "Parent 소멸자 호출" << std::endl; }
};
class Child : public Parent {
 public:
  Child() : Parent() { std::cout << "Child 생성자 호출" << std::endl; }
  ~Child() { std::cout << "Child 소멸자 호출" << std::endl; }
};
int main() {
  std::cout << "--- 평범한 Child 만들었을 때 ---" << std::endl;
  { 
    // 이 {} 를 빠져나가면 c 가 소멸된다.
    Child c; 
  }
  std::cout << "--- Parent 포인터로 Child 가리켰을 때 ---" << std::endl;
  {
    Parent *p = new Child();
    delete p;
  }
}

// 여기서 한 가지 질문을 하자면, 그렇다면 왜 Parent 소멸자는 호출이 되었는가 인데, 이는 Child 소멸자를 호출하면서, Child 소멸자가 '알아서' Parent 의 소멸자도 호출해주기 때문입니다 (Child 는 자신이 Parent 를 상속받는다는 것을 알고 있습니다).

// 반면에 Parent 소멸자를 먼저 호출하게 되면, Parent 는 Child 가 있는지 없는지 모르므로, Child 소멸자를 호출해줄 수 없습니다 (Parent 는 자신이 누구에서 상속해주는지 알 수 없지요).

// 이와 같은 연유로,상속될 여지가 있는 Base 클래스들은 (위 경우 Parent) 반드시 소멸자를 virtual 로 만들어주어야 나중에 문제가 발생할 여지가 없게 됩니다.

// #include <iostream>

// class A {
//  public:
//   virtual void show() { std::cout << "Parent !" << std::endl; }
// };
// class B : public A {
//  public:
//   void show() override { std::cout << "Child!" << std::endl; }
// };

// void test(A& a) { a.show(); }
// int main() {
//   A a;
//   B b;
//   test(a);
//   test(b);

//   return 0;
// }

// 사실 기반 클래스의 레퍼런스여도 문제 없이 작동합니다. 