#include <iostream>
#include <string>

class Base {
  std::string s;

 public:
  Base() : s("기반") { std::cout << "기반 클래스" << std::endl; }

  void what() { std::cout << s << std::endl; }
};
class Derived : public Base {
  std::string s;

 public:
  Derived() : s("파생"), Base() { std::cout << "파생 클래스" << std::endl; }

  void what() { std::cout << s << std::endl; }
};
int main() {
  Base p;
  Derived c;

  std::cout << "=== 포인터 버전 ===" << std::endl;
  Base* p_c = &c;//p_c는 c의 Base를 가르킴(c 의 Base관련 정보만을 가르킴)
  p_c->what();

  return 0;
}
// 이러한 형태의 캐스팅을 (즉 파생 클래스에서 기반 클래스로 캐스팅 하는 것) 을 업 캐스팅 이라고 부릅니다.

//다운 캐스팅을 오류가 남

//업 캐스팅 이후 다운캐스팅 해도 오류가 남
// 이러한 캐스팅에 따른 오류를 미연에 방지하기 위해서, C++ 에서는 상속 관계에 있는 두 포인터들 간에 캐스팅을 해주는 dynamic_cast 라는 것을 지원합니다. 이를 사용하는 방법은 static_cast 와 거의 동일합니다.
//하지만 반드시 필요한 경우 아니면 이런 짓은 하지 말것