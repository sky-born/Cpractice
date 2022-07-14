#include <iostream>
#include <string>

int main() {
  int t;
  while (true) {
    std::cin >> t;
    std::cout << "입력 :: " << t << std::endl;
    if (std::cin.fail()) {
      std::cout << "제대로 입력해주세요" << std::endl;
      std::cin.clear();            // 플래그들을 초기화 하고
      std::cin.ignore(100, '\n');  // 개행문자가 나올 때 까지 무시한다
    }
    if (t == 0) break;
  }
}

// 먼저 fail 함수는 ios 에 정의되어 있으며, failbit 가 true 거나 badbit 가 true 면 true 를 리턴합니다. 
// 만일 숫자가 아닌 것을 입력한다면 failbit 가 true 이므로, std::cin.fail() 은 true 가 되어 조건문을 실행하게 됩니다.
// 그리고 clear() 역시 ios 에 정의되어 있으며, 인자를 주지 않을 경우 플래그를 goodbit 으로 초기화 시켜 버립니다. 따라서 fail 상태를 지울 수 있게 되지요. 그 다음에 ignore 함수는 istream 에 정의되어 있는데, 최대 첫번째 인자 만큼 (100), 두 번째 인자가 나올 때 까지 ('\n'), 버퍼에서 무시합니다 (두 번째 인자를 포함).

// 따라서, 만일 제가 this is a very bad input 을 입력하였다면 버퍼에는

// this is a very bad input\n
// 이렇게 들어가 있고, ignore 함수를 통해 (최대 100 자 까지) 개행문자가 나올 때 까지 무시할 수 있게 됩니다.

// 만일 버퍼에 100자 이상을 집어 넣는다면 위와 같이 ignore 함수가 총 3번 호출됨을 알 수 있습니다. (버퍼에 남아 있는 문자들이 다 지워질때 까지)
