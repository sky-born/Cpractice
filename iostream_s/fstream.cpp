// 파일 스트림은 기본적인 istream 이나 ostream 클래스 보다 더 지원하는 기능이 더 많기 때문에 이를 상속 받아서 작성되었으며, 
// 각각을 상속 받은 것이 ifstream 과 ofstream 입니다. 이들 클래스를 모두 포함하는 라이브러리로 fstream 을 사용하면 됩니다.

// 파일에서의 입출력
#include <fstream>
#include <iostream>
#include <string>

int main() {
  // 파일 읽기 준비
  std::ifstream in("test.txt");
  std::string s;

  if (in.is_open()) {
    in >> s;
    std::cout << "입력 받은 문자열 :: " << s << std::endl;
  } else {
    std::cout << "파일을 찾을 수 없습니다!" << std::endl;
  }
  return 0;
}

// in 객체를 이용해서 파일로 부터 읽을 수 있습니다. (cin 에서 >> 로 읽을 때 공백 문자가 나올 까지 읽었던 것처럼 여기도 동일합니다)

// 여기서 한 가지 흥미로운 점이 있습니다. C 언어에서 기억을 되돌려 보자면 파일 입출력을 한 후에 꼭 fclose 를 해주어야 했었습니다. 
// 그런데 여기서하는 신기하게도 그러한 작업을 하지 않습니다. 왜 그렇냐면, 이미 ifstream 객체의 소멸자에서 자동적으로 close 를 해주기 때문입니다.