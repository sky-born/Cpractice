#include <iostream>
#include <list>

int main() {
  std::list<int> lst;

  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);
  lst.push_back(40);

  for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
    std::cout << *itr << std::endl;
  }
}

// 한 가지 재미있는점은 리스트의 반복자의 경우 다음과 같은 연산밖에 수행할 수 없습니다.

//  itr++    // itr ++
//   itr--  // --itr 도 됩니다.

// itr + 5  // 불가능!
// 와 같이 임의의 위치에 있는 원소를 가리킬 수 없다는 것입니다. 반복자는 오직 한 칸 씩 밖에 움직일 수 없습니다.