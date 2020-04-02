// std::string 에 정의된 getline 사용
#include <fstream>
#include <iostream>
#include <string>

int main() {
  // 파일 읽기 준비
  std::ifstream in("test.txt");

  if (!in.is_open()) {
    std::cout << "파일을 찾을 수 없습니다!" << std::endl;
    return 0;
  }

  std::string s;
  while (in) {
    getline(in, s);
    std::cout << s << std::endl;
  }

  return 0;
}

// 한 가지 주의할 사항으로 while 문 조건으로 절대 in.eof() 를 사용하면 안됩니다. 
// 이러한 코드를 사용했다면 99 퍼센트의 확률로 잘못된 코드 입니다. 왜냐하면 eof 함수는 파일 위치 지시자가 파일에 끝에 도달한 이후 에 true 를 리턴하기 때문입니다.

// 예를 들어서 while 문 안에서 파일을 쭈르륵 읽다가 파일 끝(EOF) 바로 직전까지 읽었다고 해봅시다. 그렇다면 아직 EOF 를 읽지 않았으므로 in.eof() 는 참인 상태일 것입니다. 
// 그 상태에서 예컨대 in >> data 를 하게 된다면 data 에는 아무것도 들어가지 않게 됩니다. 즉 초기화가 되지 않은 상태로 남아있는 것입니다!

// 다시 말해 in.eof() 는 while 문 안에서 파일 읽기가 안전하다 라는 것을 보장하지 않습니다. 정확한 사용법은 그냥 while(in) 처럼 스트림 객체 자체를 전달하는 것입니다. 
// 앞에서도 말했듯이 istream 객체는 다음 읽기가 안전할 때만 true 로 캐스팅됩니다.