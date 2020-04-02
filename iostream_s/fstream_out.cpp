#include <fstream>
#include <iostream>
#include <string>

int main() {
  // 파일 쓰기준비
  //   std::ofstream out("test.txt"); 이건 새로 만들거나 원래 있던거 지우고 만듬.
  std::ofstream out("test.txt", std::ios::app);//덧붙이기

  std::string s;
  if (out.is_open()) {
    out << "덧붙이기";
  }

  return 0;
}

// ios::ate : 자동으로 파일 끝에서 부터 읽기와 쓰기를 실시합니다. (즉 파일을 열 때 위치 지정자가 파일 끝을 가리키고 있게 됩니다)

// ios::trunc : 파일 스트림을 열면 기존에 있던 내용들이 모두 지워집니다. 기본적으로 ofstream 객체를 생성할 때 이와 같은 설정으로 만들어집니다.

// ios::in, std::ios::out : 파일에 입력을 할 지 출력을 할 지 지정하며, ifstream 과 ofstream 객체를 생성할 때 각각은 이미 설정되어 있습니다.

// 참고로 ios::ate 와 ios::app 은 비슷해 보이지만 차이가 있다면 ios::app 의 경우 원본 파일의 내용을 무조건 적으로 보장하지만, ate 는 위치 지정자를 그 이전으로 옮길 수 있습니다.
// 즉 app 의 경우 파일 위치 지정자가 기존 파일의 끝이 시작점이라 생각하여 움직이며 ate 의 경우 기존 파일을 포함해서 움직입니다 (사실 ate 의 경우 사용할 일이 거의 없을 것입니다).

// 그렇다고 해서 ate 를 이용해서 기존에 있는 파일 데이터 한 가운데에 무언가를 끼워 넣을 수 있는 것은 아닙니다.
// (ate 는 기존 파일의 내용을 보존하지 않습니다)

